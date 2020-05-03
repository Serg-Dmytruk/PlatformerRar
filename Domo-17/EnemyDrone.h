#pragma once
#include "GameSprite.h"

Texture DroneText;

class EnemyDrone : public GameSprite
{
protected:
	Vector2f WhereIam;
	Sprite ObjSprite;
	float MyWingth;
	float MyHeigth;
	std::vector<Object> ObjectsInMap;
	enum { left, right } State;
	float Dx;
	float Speed;
	bool Life;
	float CurrentFrame;
	bool IamDaying;
public:
	EnemyDrone(Level& lvl, float X, float Y)
	{
		DroneText.loadFromFile("SPRITES\\misc\\drone\\drone-1.png");
		ObjSprite.setTexture(DroneText);
		ObjSprite.setTextureRect(IntRect(0, 0, 55, 52));
		ObjectsInMap = lvl.GetAllObjects();
		MyWingth = 40;
		MyHeigth = 48;
		WhereIam.x = X;
		WhereIam.y = Y;
		ObjSprite.setPosition(WhereIam);
		State = left;
		CurrentFrame = 0;
		Life = true;
		IamDaying = false;
	}
	void Movment(float& time)override
	{
		if (State == left)
		{
			ObjSprite.move(-0.15 * time, 0);
			ObjSprite.setTextureRect(IntRect(0, 0, 55, 52));
		}
		if (State == right)
		{
			ObjSprite.move(0.15 * time, 0);
			ObjSprite.setTextureRect(IntRect(55, 0, -55, 52));
		}
	}
	void Update(float& time)override
	{
		if (Life)
		{
			Movment(time);
			WhereIam = ObjSprite.getPosition();
			Colision(WhereIam.x);
		}
		else
			DethAnimation(time );
	}
	void Colision(float Dx)
	{
		for (int i = 0; i < ObjectsInMap.size(); i++)
		{
			if (GetRect().intersects(ObjectsInMap[i].rect))
			{
				bool MoveSwapSide = true;

				if (ObjectsInMap[i].name == "Solid")
				{
					if (State == left && MoveSwapSide) { WhereIam.x = ObjectsInMap[i].rect.left + ObjectsInMap[i].rect.width;  State = right; MoveSwapSide = false; }
					if (State == right && MoveSwapSide) { WhereIam.x = ObjectsInMap[i].rect.left - MyWingth; State = left; MoveSwapSide = false; }
				}
			}
		}
	}
	FloatRect GetRect() override
	{
		return FloatRect(WhereIam.x, WhereIam.y, MyWingth, MyHeigth);
	}
	void DrawObj(RenderWindow& Show) override
	{
		Show.draw(ObjSprite);
	}
	void DethAnimation(float & time)
	{
		CurrentFrame += 0.001 * time;
		if(CurrentFrame >= 6)
			CurrentFrame = 0; IamDaying = true;

			if (CurrentFrame <= 1)
			{
				DroneText.loadFromFile("SPRITES\\misc\\enemy-explosion\\enemy-explosion-1.png");
				ObjSprite.setTexture(DroneText);
			}
			else if (CurrentFrame > 1 && CurrentFrame <= 2)
			{
				DroneText.loadFromFile("SPRITES\\misc\\enemy-explosion\\enemy-explosion-2.png");
				ObjSprite.setTexture(DroneText);
			}
			else if (CurrentFrame > 2 && CurrentFrame <= 3)
			{
				DroneText.loadFromFile("SPRITES\\misc\\enemy-explosion\\enemy-explosion-3.png");
				ObjSprite.setTexture(DroneText);
			}
			else if (CurrentFrame > 3 && CurrentFrame <= 4)
			{
				DroneText.loadFromFile("SPRITES\\misc\\enemy-explosion\\enemy-explosion-4.png");
				ObjSprite.setTexture(DroneText);
			}
			else if (CurrentFrame > 4 && CurrentFrame <= 5)
			{
				DroneText.loadFromFile("SPRITES\\misc\\enemy-explosion\\enemy-explosion-5.png");
				ObjSprite.setTexture(DroneText);
			}
			else if (CurrentFrame > 5 && CurrentFrame <= 6)
			{
				DroneText.loadFromFile("SPRITES\\misc\\enemy-explosion\\enemy-explosion-6.png");
				ObjSprite.setTexture(DroneText);
				IamDaying = true;
			}
		
	}
	bool GetLife()
	{
		return Life;
	}
	void SetLife(bool NewValue)
	{
		Life = NewValue;
	}
	bool GetIamDying()
	{
		return IamDaying;
	}
};