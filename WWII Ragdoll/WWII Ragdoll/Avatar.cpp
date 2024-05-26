#include "Avatar.h"

Avatar::Avatar(b2Body* _body, Sprite* _sprite) : _b2d(_body), _s(_sprite)
{

	b2AABB _aabb;
	_aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	_aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	for (b2Fixture* _fixture = _b2d->GetFixtureList(); _fixture; _fixture = _fixture->GetNext())
		_aabb.Combine(_fixture->GetAABB(0));
	float _size_x = _aabb.GetExtents().x * 2.0 / _s->getTexture()->getSize().x;
	float _size_y = _aabb.GetExtents().y * 2.0 / _s->getTexture()->getSize().y;
	_s->setScale(_size_x, _size_y);
	_s->setOrigin(Vector2f(_s->getTexture()->getSize().x / 2.0f, _s->getTexture()->getSize().y / 2.0f));
	b2Vec2 _pos = _b2d->GetPosition();
	_s->setPosition(Vector2f(_pos.x, _pos.y));
}

void Avatar::UpdateSprites()
{

	b2Vec2 _pos = _b2d->GetPosition();
	_s->setPosition(Vector2f(_pos.x, _pos.y));

	float _angle = _b2d->GetAngle();
	_s->setRotation(_angle * 180 / M_PI);
}

void Avatar::DrawSprite(RenderWindow& wnd)
{

	wnd.draw(*_s);
}