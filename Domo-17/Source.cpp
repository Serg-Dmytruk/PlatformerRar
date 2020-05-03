#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameSprite.h" // абстрактний клас для ігрових об'єктів
#include "Player.h" // головний герой
#include "View.h"
#include "EnemyDrone.h"
#include "Level.h"
#include "MovingPlatform.h"
#include <list>
#include <iterator>
#include "Bullet.h"

#define Wingth 800
#define Heigth 600
/// НЕ ЗАБУТИ ПЕРЕРОБИТИ НА ШАБЛОННІ
template <typename T, typename U, typename I>
void ObjectInteraction(T &Iterator, U &MyMovingPlatforms, I &_Luci);// взаємодія між об'єктами (герой рухомі платформи та вороги)

template <typename T, typename U, typename I>
void ObjectUpdate(T& Iterator, U& MyObject, I& Time); // оновлення об'єктів

template <typename T, typename U, typename I>
void ObjectDraw(T& Iterator, U& MyObject, I& Window); // малює об'єкти

void BulletInteraction(std::list<Bullet*>::iterator& Iterator, std::list<Bullet*>& AllMyBullets, std::list<EnemyDrone*>::iterator& DroneIterator, std::list<EnemyDrone*>& AllMyDrones, float & time);
void BulletCleaner(std::list<Bullet*>::iterator& Iterator, std::list<Bullet*>& AllMyBullets); // видаляємо не жві кулі

void PlayerInterction(Player &_Luci, std::list<EnemyDrone*>::iterator& DroneIterator, std::list<EnemyDrone*>& AllMyDrones);

int main()
{
	//Ігрове вікно
	RenderWindow window(VideoMode(Wingth, Heigth), "Domo-17");
	Texture texture; // Перша текстурка для головного героя
	texture.loadFromFile("SPRITES\\player\\idle\\idle-1.png");

	Texture MovPlatform; // Текстура для рухомої платформи
	MovPlatform.loadFromFile("ENVIRONMENT\\tileset1.png");

	Clock TimeLeft; // час від початку
	view.reset(FloatRect(0, 0, 800, 600)); // камера

	Clock Reload; // для заборони спамити кулями
	bool CanIShoot = true;

	Level LVL; // ігровий рівень
	LVL.LoadFromFile("lvl1.tmx");

	Object Resp = LVL.GetObject("Spawn"); // стартова координати для спавна гравця
	Player Luci(texture, LVL, Resp.rect.left, Resp.rect.top); // отримання координат

	std::vector<Object> Enemy = LVL.GetObjects("Enemy"); // шукаємо всіх воргів дронів на мапі
	std::list<EnemyDrone*> AllMyDrones; // список ворогів дронів
	std::list<EnemyDrone*>::iterator DroneIterator;
	for (int i = 0; i < Enemy.size(); i++) // заповнюэмо список опираючись на кількість зчитаних платформ
		AllMyDrones.push_back(new EnemyDrone (LVL, Enemy.at(i).rect.left, Enemy.at(i).rect.top));
	
	//Рухливі платформи на рівні
	std::vector<Object> AllMovePlatforms = LVL.GetObjects("MSolid"); // шукаэмо всы платформи на мапы та записуэмо
	std::list<MovingPlatform*> AllMyMovingPlatforms; // список платформ
	std::list<MovingPlatform*> ::iterator PlatformIterator;
	for (int i = 0; i < AllMovePlatforms.size(); i++) // заповнюэмо список опираючись на кількість зчитаних платформ
		AllMyMovingPlatforms.push_back(new MovingPlatform(MovPlatform, LVL, AllMovePlatforms.at(i).rect.left, AllMovePlatforms.at(i).rect.top));

	//Кулі
	std::list<Bullet*> AllMyBullets;
	std::list<Bullet*>::iterator BulletIterator;


	while (window.isOpen())
	{
		float Time = TimeLeft.getElapsedTime().asMicroseconds();
		TimeLeft.restart();
		Time /= 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		
			Luci.Update(Time);
			if (Luci.GetShoot() && CanIShoot) // якщо нажата кнопка пострілу то створюємо кулю
			{
				CanIShoot = false;
				if (Luci.GetDir() == 0)
					AllMyBullets.push_back(new Bullet(LVL, Luci.GetMyWhereIam().x, Luci.GetMyWhereIam().y + 20, Luci.GetDir()));
				if (Luci.GetDir() == 1)
					AllMyBullets.push_back(new Bullet(LVL, Luci.GetMyWhereIam().x + 50, Luci.GetMyWhereIam().y + 20, Luci.GetDir()));
			}
			else
			{
				float TimeLeftForShoot = Reload.getElapsedTime().asSeconds();
				if (TimeLeftForShoot >= 0.5) { Reload.restart(); CanIShoot = true; }
			}
			//Оновлюємо усі об'єкти що існують на мапі
			ObjectUpdate(PlatformIterator, AllMyMovingPlatforms, Time);
			ObjectUpdate(BulletIterator, AllMyBullets, Time);
			ObjectUpdate(DroneIterator, AllMyDrones, Time);
			BulletCleaner(BulletIterator, AllMyBullets);
			//Взаємодія об'єктів
			ObjectInteraction(PlatformIterator, AllMyMovingPlatforms, Luci);
			BulletInteraction(BulletIterator, AllMyBullets, DroneIterator, AllMyDrones, Time);
			PlayerInterction(Luci, DroneIterator, AllMyDrones);
		

		window.setView(view);
		window.clear(Color(217,123,122));

		LVL.Draw(window);
		ObjectDraw(PlatformIterator, AllMyMovingPlatforms,window);
		ObjectDraw(BulletIterator, AllMyBullets, window);
		ObjectDraw(DroneIterator, AllMyDrones, window);
		Luci.DrawObj(window);
		

		window.display();
	}	
		return 0;	
}

template <typename T, typename U, typename I>
void ObjectInteraction(T& Iterator, U& MyMovingPlatforms, I& _Luci)
{
	for (Iterator = MyMovingPlatforms.begin(); Iterator != MyMovingPlatforms.end(); Iterator++)
	{
		if ((*Iterator)->GetRect().intersects(_Luci.GetRect()))
		{
			if (_Luci.GetMyDy() > 0) { _Luci.SetWhereIamY((*Iterator)->GetRect().top - (_Luci.GetMyHeigth() + 15)); _Luci.SetDy(0); _Luci.SetOnGround(true); _Luci.SetPortalJump(false); }
			if (_Luci.GetMyDy() < 0) { _Luci.SetWhereIamY((*Iterator)->GetRect().top + (*Iterator)->GetRect().height); _Luci.SetDy(0);}
		}
	}
}

template <typename T, typename U, typename I>
void ObjectUpdate(T& Iterator, U& MyObject, I &Time)
{
	for (Iterator = MyObject.begin(); Iterator != MyObject.end(); Iterator++)
		(*Iterator)->Update(Time);
}

template <typename T, typename U, typename I>
void ObjectDraw(T& Iterator, U& MyObject, I& Window)
{
	for (Iterator = MyObject.begin(); Iterator != MyObject.end(); Iterator++)
		(*Iterator)->DrawObj(Window);
}

void BulletCleaner(std::list<Bullet*>::iterator& Iterator, std::list<Bullet*> &AllMyBullets)
{
	for(Iterator = AllMyBullets.begin(); Iterator != AllMyBullets.end();)
	{
		Bullet* Tmp = *Iterator;
		if ((*Iterator)->IamLive() == false)
		{
			Iterator = AllMyBullets.erase(Iterator);
			delete Tmp;
		}
		else
		{
			if (Iterator != AllMyBullets.end())
				Iterator++;
		}
	}
}

void BulletInteraction(std::list<Bullet*>::iterator& BylletIterator, std::list<Bullet*>& AllMyBullets, std::list<EnemyDrone*>::iterator& DroneIterator, std::list<EnemyDrone*>& AllMyDrones, float & time)
{
	for (BylletIterator = AllMyBullets.begin(); BylletIterator != AllMyBullets.end(); BylletIterator++)
	{
		for (DroneIterator = AllMyDrones.begin(); DroneIterator != AllMyDrones.end(); DroneIterator++)
		{
			if ((*BylletIterator)->GetRect().intersects((*DroneIterator)->GetRect()))
			{
				AllMyDrones.erase(DroneIterator);
				break;
			}
		}
	}
}

void PlayerInterction(Player& _Luci, std::list<EnemyDrone*>::iterator& DroneIterator, std::list<EnemyDrone*>& AllMyDrones)
{
	for (DroneIterator = AllMyDrones.begin(); DroneIterator != AllMyDrones.end(); DroneIterator++)
	{
		if (_Luci.GetRect().intersects((*DroneIterator)->GetRect()))
		{
			_Luci.SetLife(false);
		}
	}
}