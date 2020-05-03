#pragma once
#include "GameSprite.h"
#include "View.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"
#include <list>
#include "Animator.h"

using namespace sf;
//Тмп Текстури для анімації
Texture TextureIdleTmp; // персонає стоїть
Texture TextureRunRightTmp; // персонаж біжить на право
Texture TextureRunLeftTmp; // біжить на ліво

Clock TimeLeftForJump;
Clock ItsTimeToStop;

class Player : public GameSprite
{
protected:
	Vector2f WhereIam;
	Sprite ObjSprite;
	int Health;
	bool Life;
	float Speed, Dx, Dy, MyWingth, MyHeigth, CurrentFrame;
	bool OnGround, CanIJump, PortalJump, IamShoot;
	enum { left, right, jump, stay } State;
	std::vector<Object> ObjectsInMap;
public:
	Player(Texture& NewSprite, Level& lvl, float X, float Y)
	{
		ObjSprite.setTexture(NewSprite);
		ObjectsInMap = lvl.GetAllObjects();
		WhereIam.x = X;
		WhereIam.y = Y;
		ObjSprite.setPosition(WhereIam);
		OnGround = false;
		CanIJump = true;
		Health = 3;
		Life = true;
		Speed = 0;
		Dx = 0;
		Dy = 0;
		CurrentFrame = 0;
		MyHeigth = 55;
		MyWingth = 25;
		PortalJump = false;
		IamShoot = false;
	}
	void DrawObj(RenderWindow& Show) override
	{
		Show.draw(ObjSprite);
	}
	void Movment(float& time) override
	{
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{                                          // рух в ліво
			Speed = -0.15;
			State = left;
			CurrentFrame += 0.01 * time;
			if (CurrentFrame > 8)
				CurrentFrame = 0;

			if (CurrentFrame <= 1)
			{
				TextureRunLeftTmp.loadFromFile("SPRITES\\player\\run\\run-1.png");
				ObjSprite.setTexture(TextureRunLeftTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 1 && CurrentFrame <= 2)
			{
				TextureRunLeftTmp.loadFromFile("SPRITES\\player\\run\\run-2.png");
				ObjSprite.setTexture(TextureRunLeftTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 2 && CurrentFrame <= 3)
			{
				TextureRunLeftTmp.loadFromFile("SPRITES\\player\\run\\run-3.png");
				ObjSprite.setTexture(TextureRunLeftTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 3 && CurrentFrame <= 4)
			{
				TextureRunLeftTmp.loadFromFile("SPRITES\\player\\run\\run-4.png");
				ObjSprite.setTexture(TextureRunLeftTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 4 && CurrentFrame <= 5)
			{
				TextureRunLeftTmp.loadFromFile("SPRITES\\player\\run\\run-5.png");
				ObjSprite.setTexture(TextureRunLeftTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 5 && CurrentFrame <= 6)
			{
				TextureRunLeftTmp.loadFromFile("SPRITES\\player\\run\\run-6.png");
				ObjSprite.setTexture(TextureRunLeftTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 6 && CurrentFrame <= 7)
			{
				TextureRunLeftTmp.loadFromFile("SPRITES\\player\\run\\run-7.png");
				ObjSprite.setTexture(TextureRunLeftTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 7 && CurrentFrame <= 8)
			{
				TextureRunLeftTmp.loadFromFile("SPRITES\\player\\run\\run-8.png");
				ObjSprite.setTexture(TextureRunLeftTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{													// рух в право
			Speed = 0.15;
			State = right;
			CurrentFrame += 0.01 * time;
			if (CurrentFrame > 8)
				CurrentFrame = 0;
			if (CurrentFrame <= 1)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run\\run-1.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 1 && CurrentFrame <= 2)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run\\run-2.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 2 && CurrentFrame <= 3)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run\\run-3.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 3 && CurrentFrame <= 4)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run\\run-4.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 4 && CurrentFrame <= 5)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run\\run-5.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 5 && CurrentFrame <= 6)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run\\run-6.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 6 && CurrentFrame <= 7)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run\\run-7.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 7 && CurrentFrame <= 8)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run\\run-8.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
		}
		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (OnGround) && CanIJump == true)
		{														// в верх // зробити підскок
			State = jump;
			Speed = -0.1;
			OnGround = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::F) && OnGround)
		{
			Speed = 0;
			IamShoot = true;
			ShootAnimation();
		}
		else
		{
			IamShoot = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::F) && (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right)) && IamShoot)
		{
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				Speed = 0.15;
				State = right;
				ShootAndRunAnimation(time);
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				Speed = -0.15;
				State = left;
				ShootAndRunAnimation(time);
			}
		}
		float IdleTime = ItsTimeToStop.getElapsedTime().asMilliseconds();
		if (IdleTime >= 300 && !IamShoot)
		{
			ItsTimeToStop.restart();
			State = stay;
			Speed = 0;
		}
	}
	void Update(float& time) override
	{
		if (Life)
		{
			getplayercoordinateforview(WhereIam.x, WhereIam.y);
			Movment(time);
			switch (State)
			{
			case right: Dx = Speed; break;
			case left: Dx = Speed; break;
			case jump: Dy = Speed; break;
			case stay: Dx = Speed; IdleAnimation(time); break;
			}
			WhereIam.x += Dx * time;
			Colision(Dx, 0);
			WhereIam.y += Dy * time;
			Colision(0, Dy);
			ObjSprite.setPosition(WhereIam.x, WhereIam.y);
			MyGravity(time);
			if (!OnGround)
			{
				JumpAnimation(time);
				CanIJump = false;
			}
			else
			{
				float TimeLeft = TimeLeftForJump.getElapsedTime().asSeconds();
				if (TimeLeft >= 1) { TimeLeftForJump.restart(); CanIJump = true; }
			}
		}
		else
		{

		}
	}
	bool PLayerIsAlive()
	{
		return Life;
	}
	void Colision(float Dx, float Dy)
	{
		for (int i = 0; i < ObjectsInMap.size(); i++)
			if (GetRect().intersects(ObjectsInMap[i].rect))
			{
				if (ObjectsInMap[i].name == "Solid")
				{
					if (Dy > 0) { WhereIam.y = ObjectsInMap[i].rect.top - (MyHeigth + 15); Dy = 0; OnGround = true; PortalJump = false; }
					if (Dy < 0) { WhereIam.y = ObjectsInMap[i].rect.top + (ObjectsInMap[i].rect.height); Dy = 0; }
					if (Dx > 0) { WhereIam.x = ObjectsInMap[i].rect.left - (MyWingth + 25); }
					if (Dx < 0) { WhereIam.x = ObjectsInMap[i].rect.left + (ObjectsInMap[i].rect.width); }
				}
				if (ObjectsInMap[i].name == "Portal")
				{
					if (Dy > 0) { WhereIam.y = ObjectsInMap[i].rect.top - (MyHeigth + 200); Dy = 0; OnGround = false; PortalJump = true; }
					if (Dy < 0) { WhereIam.y = ObjectsInMap[i].rect.top - (MyHeigth + 200); Dy = 0; OnGround = false; PortalJump = true; }
					if (Dx > 0) { WhereIam.y = ObjectsInMap[i].rect.top - (MyHeigth + 200); Dy = 0; OnGround = false; PortalJump = true; }
					if (Dx < 0) { WhereIam.y = ObjectsInMap[i].rect.top - (MyHeigth + 200); Dy = 0; OnGround = false; PortalJump = true; }
				}
			}
	}
	void JumpAnimation(float& time)
	{
		CurrentFrame += 0.0001 * time;
		if (CurrentFrame > 3)
			CurrentFrame = 0;

		if (CurrentFrame <= 1)
		{
			TextureIdleTmp.loadFromFile("SPRITES\\player\\jump\\jump-1.png");
			ObjSprite.setTexture(TextureIdleTmp);
		}
		else if (CurrentFrame > 1 && CurrentFrame <= 2)
		{
			TextureIdleTmp.loadFromFile("SPRITES\\player\\jump\\jump-2.png");
			ObjSprite.setTexture(TextureIdleTmp);
		}
		else if (CurrentFrame > 2 && CurrentFrame <= 3)
		{
			TextureIdleTmp.loadFromFile("SPRITES\\player\\jump\\jump-3.png");
			ObjSprite.setTexture(TextureIdleTmp);
		}
	}

	void IdleAnimation(float& time)
	{
		Speed = 0;
		CurrentFrame += 0.005 * time;
		if (CurrentFrame > 4)
			CurrentFrame = 0;
		if (CurrentFrame <= 1)
		{
			TextureIdleTmp.loadFromFile("SPRITES\\player\\idle\\idle-1.png");
			ObjSprite.setTexture(TextureIdleTmp);
		}
		else if (CurrentFrame > 1 && CurrentFrame <= 2)
		{
			TextureIdleTmp.loadFromFile("SPRITES\\player\\idle\\idle-2.png");
			ObjSprite.setTexture(TextureIdleTmp);
		}
		else if (CurrentFrame > 2 && CurrentFrame <= 3)
		{
			TextureIdleTmp.loadFromFile("SPRITES\\player\\idle\\idle-3.png");
			ObjSprite.setTexture(TextureIdleTmp);
		}
		else if (CurrentFrame > 3 && CurrentFrame <= 4)
		{
			TextureIdleTmp.loadFromFile("SPRITES\\player\\idle\\idle-4.png");
			ObjSprite.setTexture(TextureIdleTmp);
		}
	}
	FloatRect GetRect() override
	{
		return FloatRect(WhereIam.x + 25, WhereIam.y + 15, MyWingth, MyHeigth);
	}
	Vector2f GetMyWhereIam()
	{
		return WhereIam;
	}
	float GetMyDx()
	{
		return Dx;
	}
	float GetMyDy()
	{
		return Dy;
	}
	float SetWhereIamX(float X)
	{
		WhereIam.x = X;
	}
	void SetWhereIamY(float Y)
	{
		WhereIam.y = Y;
	}
	float GetMyHeigth()
	{
		return MyHeigth;
	}
	float GetMyWingth()
	{
		return MyWingth;
	}
	void SetOnGround(bool NewValue)
	{
		OnGround = NewValue;
	}
	void SetDy(float NewValue)
	{
		Dy = NewValue;
	}
	void SetDx(float NewValue)
	{
		Dx = NewValue;
	}
	void SetPortalJump(bool NewValue)
	{
		PortalJump = NewValue;
	}
	void ShootAnimation()
	{
		TextureIdleTmp.loadFromFile("SPRITES\\player\\shoot\\shoot.png");
		ObjSprite.setTexture(TextureIdleTmp);
	}
	bool GetShoot()
	{
		return IamShoot;
	}
	void ShootAndRunAnimation(float time)
	{
		CurrentFrame += 0.003 * time;
		if (CurrentFrame > 8)
			CurrentFrame = 0;
		if (State == right)
		{
			if (CurrentFrame <= 1)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-1.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 1 && CurrentFrame <= 2)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-2.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 2 && CurrentFrame <= 3)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-3.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 3 && CurrentFrame <= 4)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-4.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 4 && CurrentFrame <= 5)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-5.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 5 && CurrentFrame <= 6)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-6.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 6 && CurrentFrame <= 7)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-7.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
			else if (CurrentFrame > 7 && CurrentFrame <= 8)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-8.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(0, 0, 71, 67));
			}
		}
		if(State == left)
		{
			if (CurrentFrame <= 1)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-1.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 1 && CurrentFrame <= 2)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-2.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 2 && CurrentFrame <= 3)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-3.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 3 && CurrentFrame <= 4)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-4.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 4 && CurrentFrame <= 5)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-5.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 5 && CurrentFrame <= 6)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-6.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 6 && CurrentFrame <= 7)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-7.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
			else if (CurrentFrame > 7 && CurrentFrame <= 8)
			{
				TextureRunRightTmp.loadFromFile("SPRITES\\player\\run-shoot\\run-shoot-8.png");
				ObjSprite.setTexture(TextureRunRightTmp);
				ObjSprite.setTextureRect(IntRect(71, 0, -71, 67));
			}
		}
	}
	void MyGravity(float &time)
	{
		if (!PortalJump)
			Dy += 0.0001 * time;
		else
			Dy = 0; PortalJump = false;
	}
	int GetDir()
	{
		return State;
	}
	bool GetLife()
	{
		return Life;
	}
	void SetLife(bool NewValue)
	{
		Life = NewValue;
	}
};