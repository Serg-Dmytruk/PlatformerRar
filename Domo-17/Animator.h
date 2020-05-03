#ifndef ANIM_H 
#define ANIM_H 


#include "GameSprite.h"
#include "View.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"
#include <list>

using namespace sf;

class Animator
{
protected:
	std::vector<IntRect> Frames, FramesFlip;
	float CurrentFrame, Speed;
	Sprite CurrentSprite;
	bool Flip, IsPlaying;
public:
	Animator(Texture & _Tex, int _X, int _Y, int _Windth, int _Height, int _Count, int _Speed)
	{
		Speed = _Speed;
		CurrentSprite.setTexture(_Tex);
		CurrentFrame = 0;
		Flip = false;
		IsPlaying = true;
		
		for (int i = 0; i < _Count; i++)
		{
			Frames.push_back(IntRect(_X + i, _Y, _Windth, _Height));
		}
	}
};

#endif ANIM_H 