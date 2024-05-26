#pragma once
#include "MainHeader.h"
#include "Box2d.h"

class Avatar
{
private:

	Sprite* _s;

	b2Body* _b2d;
public:

	Avatar(b2Body* _body, Sprite* _sprite);

	void UpdateSprites();
	void DrawSprite(RenderWindow& wnd);
};