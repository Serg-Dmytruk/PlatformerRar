#pragma once
#include "GameSprite.h"
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

sf::View view;//��������� sfml ��'��� "���", ���� � � �������
void getplayercoordinateforview(float x, float y) { //������� ��� ���������� ��������� ������
	float tempX = x; float tempY = y;//������� ���������� ������ � ���������� ��, ��� �������� ����
	if (x < 400) tempX = 400;//�������� ��� �������
	if (x > 1515) tempX = 1515;//�������� ����� �������
	if (y < 300) tempY = 300;//������ �������
	if (y > 332)tempY = 332;//�����
	view.setCenter(tempX, tempY); //������� �� �������
}
