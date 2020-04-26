#pragma once
#include "GameSprite.h"
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

sf::View view;//оголосили sfml об'Їкт "вид", €кий ≥ Ї камерою
void getplayercoordinateforview(float x, float y) { //функц≥€ дл€ зчитуванн€ координат гравц€
	float tempX = x; float tempY = y;//зчитуЇмо координати гравц€ ≥ перев≥р€Їмо њх, щоб прибрати край
	if (x < 400) tempX = 400;//забираЇмо л≥ву сторону
	if (x > 1515) tempX = 1515;//забираЇмо праву сторону
	if (y < 300) tempY = 300;//верхню сторону
	if (y > 332)tempY = 332;//нижню
	view.setCenter(tempX, tempY); //сл≥дкуЇмо за гравцем
}
