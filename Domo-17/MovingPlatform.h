#pragma once
#pragma once
#include "GameSprite.h"
#include "View.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"

class MovingPlatform : public GameSprite
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
public:
	MovingPlatform(Texture& NewSprite, Level& lvl, float X, float Y)
	{
		ObjSprite.setTexture(NewSprite);
		ObjSprite.setTextureRect(IntRect(384, 352, 96, 32));
		ObjectsInMap = lvl.GetAllObjects();
		MyWingth = 96;
		MyHeigth = 32;
		WhereIam.x = X;
		WhereIam.y = Y;
		ObjSprite.setPosition(WhereIam);
		State = left;
	}
	void Movment(float& time)override
	{
		if (State == left)
			ObjSprite.move(-0.04 * time, 0);
		if (State == right)
			ObjSprite.move(0.04 * time, 0);
	}
	void Update(float& time)override
	{
		Movment(time);
		WhereIam = ObjSprite.getPosition();
		Colision(WhereIam.x);
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
					if (State == right && MoveSwapSide) { WhereIam.x = ObjectsInMap[i].rect.left - MyWingth; State = left; MoveSwapSide = false;}
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
	
};