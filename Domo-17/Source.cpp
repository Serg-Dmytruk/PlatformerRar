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

#define Wingth 800
#define Heigth 600

void ObjectInteraction(std::list<MovingPlatform*>::iterator &Iterator, std::list<MovingPlatform*> &MyMovingPlatforms, Player &_Luci); // взаємодія між об'єктами (герой рухомі платформи та вороги)

int main()
{
	RenderWindow window(VideoMode(Wingth, Heigth), "Domo-17");
	Texture texture; // Перша текстурка дял головного героя
	texture.loadFromFile("SPRITES\\player\\idle\\idle-1.png");
	Texture MovPlatform;
	MovPlatform.loadFromFile("ENVIRONMENT\\tileset1.png");

	Clock TimeLeft; // час від початку
	view.reset(FloatRect(0, 0, 800, 600)); // камера

	Level LVL;
	LVL.LoadFromFile("lvl1.tmx");
	Object Resp = LVL.GetObject("Spawn");
	Player Luci(texture, LVL, Resp.rect.left, Resp.rect.top);


	//Рухливі платформи на рівні
	std::vector<Object> AllMovePlatforms = LVL.GetObjects("MSolid");
	std::list<MovingPlatform*> AllMyMovingPlatforms;
	std::list<MovingPlatform*> ::iterator PlatformIterator;
	for (int i = 0; i < AllMovePlatforms.size(); i++)
		AllMyMovingPlatforms.push_back(new MovingPlatform(MovPlatform, LVL, AllMovePlatforms.at(i).rect.left, AllMovePlatforms.at(i).rect.top));


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

		if (Luci.PLayerIsAlive())
		{
			Luci.Update(Time);

		/*	for (PlatformIterator = AllMyMovingPlatforms.begin(); PlatformIterator != AllMyMovingPlatforms.end(); PlatformIterator++);*/
			PlatformIterator = AllMyMovingPlatforms.begin();
				(*PlatformIterator)->Update(Time);

				ObjectInteraction(PlatformIterator, AllMyMovingPlatforms, Luci);
		}

		window.setView(view);
		window.clear(Color(217,123,122));

		LVL.Draw(window);
		//for (PlatformIterator = AllMyMovingPlatforms.begin(); PlatformIterator != AllMyMovingPlatforms.end(); PlatformIterator++);
		PlatformIterator = AllMyMovingPlatforms.begin();
		(*PlatformIterator)->DrawObj(window);
		Luci.DrawObj(window);
		

		window.display();
	}	
		return 0;	
}

void ObjectInteraction(std::list<MovingPlatform*>::iterator& Iterator, std::list<MovingPlatform*>& MyMovingPlatforms, Player& _Luci)
{
	for (Iterator = MyMovingPlatforms.begin(); Iterator != MyMovingPlatforms.end(); Iterator++)
	{
		if ((*Iterator)->GetRect().intersects(_Luci.GetRect()))
		{
		/*	if (Dy > 0) { WhereIam.y = ObjectsInMap[i].rect.top - (MyHeigth + 15); Dy = 0; OnGround = true; PortalJump = false; }
			if (Dy < 0) { WhereIam.y = ObjectsInMap[i].rect.top + (ObjectsInMap[i].rect.height); Dy = 0; }
			if (Dx > 0) { WhereIam.x = ObjectsInMap[i].rect.left - (MyWingth + 25); }
			if (Dx < 0) { WhereIam.x = ObjectsInMap[i].rect.left + (ObjectsInMap[i].rect.width); }*/
			if (_Luci.GetMyDy() > 0) { _Luci.SetWhereIamY((*Iterator)->GetRect().top - (_Luci.GetMyHeigth() + 15)); _Luci.SetDy(0); _Luci.SetOnGround(true); _Luci.SetPortalJump(false); }
			if (_Luci.GetMyDy() < 0) { _Luci.SetWhereIamY((*Iterator)->GetRect().top + (*Iterator)->GetRect().height); _Luci.SetDy(0);}
			//if(_Luci.GetMyDx() > 0) { _Luci.}
		}
	}
}