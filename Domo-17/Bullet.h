#pragma once
#include "GameSprite.h"

using namespace sf;

Texture BulletTexture;

class Bullet : public GameSprite
{
protected:
	bool Life;
	float Speed, Dx, Dy;
	Vector2f WhereIam;
	Sprite ObjSprite;
	float MyWingth;
	float MyHeigth;
	std::vector<Object> ObjectsInMap;
	int Dir;
	int CurrentFrame;
public:
	Bullet (Level& lvl, float X, float Y, int _Dir)
	{
		BulletTexture.loadFromFile("SPRITES\\misc\\shot\\shot-1.png");
		ObjSprite.setTexture(BulletTexture);
		ObjectsInMap = lvl.GetAllObjects();
		WhereIam.x = X;
		WhereIam.y = Y;
		ObjSprite.setPosition(WhereIam);
		Dir = _Dir;
		CurrentFrame = 0;
		MyWingth = 15;
		MyHeigth = 11;
		Life = true;
	}
	void MyAnim(float& time)
	{
		CurrentFrame += 0.0001 * time;
		if (CurrentFrame > 3)
			CurrentFrame = 0;
		switch(Dir)
		{
		case 0:
			if (CurrentFrame <= 1)
			{
				BulletTexture.loadFromFile("SPRITES\\misc\\shot\\shot-1.png");
				ObjSprite.setTexture(BulletTexture);
				ObjSprite.setTextureRect(IntRect(15,0,-15,11));
			}
			else if (CurrentFrame > 1 && CurrentFrame <= 2)
			{
				BulletTexture.loadFromFile("SPRITES\\misc\\shot\\shot-1.png");
				ObjSprite.setTexture(BulletTexture);
				ObjSprite.setTextureRect(IntRect(15, 0, -15, 11));
			}
			else if (CurrentFrame > 2 && CurrentFrame <= 3)
			{
				BulletTexture.loadFromFile("SPRITES\\misc\\shot\\shot-1.png");
				ObjSprite.setTexture(BulletTexture);
				ObjSprite.setTextureRect(IntRect(15, 0, -15, 11));
			}
			break;
		case 1:
			if (CurrentFrame <= 1)
			{
				BulletTexture.loadFromFile("SPRITES\\misc\\shot\\shot-1.png");
				ObjSprite.setTexture(BulletTexture);
			}
			else if (CurrentFrame > 1 && CurrentFrame <= 2)
			{
				BulletTexture.loadFromFile("SPRITES\\misc\\shot\\shot-1.png");
				ObjSprite.setTexture(BulletTexture);
			}
			else if (CurrentFrame > 2 && CurrentFrame <= 3)
			{
				BulletTexture.loadFromFile("SPRITES\\misc\\shot\\shot-1.png");
				ObjSprite.setTexture(BulletTexture);
			}
			break;
		}
	}
	void Update(float &time) override
	{
		Movment(time);
		WhereIam = ObjSprite.getPosition();
		Colision(Dx);
	}
	void DrawObj(RenderWindow& Show) override
	{
		Show.draw(ObjSprite);
	}
	void Movment(float& time) override
	{
		switch (Dir)
		{
		case 0:
			ObjSprite.move(-0.3 * time, 0);
			MyAnim(time);
			break;
		case 1:
			ObjSprite.move(0.3 * time, 0);
			MyAnim(time);
			break;
		default:
			Life = false;
			break;
		}
	}
	void Colision(float Dx)
	{
		for (int i = 0; i < ObjectsInMap.size(); i++)
		{
			if (GetRect().intersects(ObjectsInMap[i].rect))
			{
				if (ObjectsInMap[i].name == "Solid")
				{
					Life = false;
				}
			}
		}
	}
	FloatRect GetRect() override
	{
		return FloatRect(WhereIam.x, WhereIam.y, MyWingth, MyHeigth);
	}
	bool IamLive()
	{
		return Life;
	}
};