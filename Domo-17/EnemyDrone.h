#pragma once
#include "GameSprite.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"

class EnemyDrone : public GameSprite
{
protected:
	Vector2f WhereIam;
	Sprite ObjSprite;
	IntRect BoxColider;
	enum {left, right} State;
	bool Life;
	int Direction;
	float Speed;
	float Dx;
	float Dy;
	float CurrentFrame;
public:
	EnemyDrone()
	{
		WhereIam.x = 355;
		WhereIam.y = 320;
		Life = true;
		Speed = 0.15;
		Dx = 0;
		Dy = 0;
		CurrentFrame = 0;
		BoxColider = { };
	}
	
	void DrawObj(RenderWindow& Show) override
	{
		Show.draw(ObjSprite);
	}
	void Movment(float& time) override
	{
		
		CurrentFrame += 0.01 * time;

		if (CurrentFrame > 50)
			CurrentFrame = 0;

		if (CurrentFrame <= 25)
		{
			Speed = -0.11 * time;
			State = left;
			ObjSprite.setTextureRect(IntRect(0, 0, 55, 52));
	
		}
		if (CurrentFrame > 25 && CurrentFrame <= 50)
		{
			Speed = 0.11 * time;
			State = right;
			ObjSprite.setTextureRect(IntRect(55, 0, -55, 52));
		}		
	}
	void Update(float& time) override
	{
		if (Life)
		{
			Movment(time);
			switch (State)
			{
			case right: Dx = Speed; break;
			case left: Dx = Speed; break;
			}
			WhereIam.x += Dx;
			ObjSprite.setPosition(WhereIam.x, WhereIam.y);
		}
	}
};