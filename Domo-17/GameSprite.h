#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Level.h"

using namespace sf;

class GameSprite
{
protected:
	Vector2f WhereIam; // ������� �� ����
	Sprite ObjSprite; // ������ ��'����
	int Health; // ������'�
	bool Life; // �����
	int Direction; // ��������
	float CurrentFrame;// �������� ���� �������
	bool OnGround; // �� �� ���� ����������� ��'���
	enum { left, right, up, down, jump, stay } State; // ���� � �������
	std::vector<Object> ObjectsInMap; //������ ��'���� ��� ������ � ������
public:
	virtual void DrawObj(RenderWindow &Show) = 0;
	virtual void Update(float& time) = 0;
	virtual void Movment(float& time) = 0;
	virtual FloatRect GetRect() = 0;
};  

