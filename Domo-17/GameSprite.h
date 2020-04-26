#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Level.h"

using namespace sf;

class GameSprite
{
protected:
	Vector2f WhereIam; // позиція на карті
	Sprite ObjSprite; // спрайт об'єкта
	int Health; // здоров'я
	bool Life; // життя
	int Direction; // напрямок
	float CurrentFrame;// теперішній кадр анімації
	bool OnGround; // чи на землі знаходиться об'єкт
	enum { left, right, up, down, jump, stay } State; // стан у просторі
	std::vector<Object> ObjectsInMap; //вектор об'єктів для взаємоді з картою
public:
	virtual void DrawObj(RenderWindow &Show) = 0;
	virtual void Update(float& time) = 0;
	virtual void Movment(float& time) = 0;
	virtual FloatRect GetRect() = 0;
};  

