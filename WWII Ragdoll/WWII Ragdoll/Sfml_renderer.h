#pragma once
#include <box2d/box2d.h>
#include <SFML\Graphics.hpp>

using namespace sf;

class SFML : public b2Draw
{
private:

	RenderWindow* _wnd;

public:

	SFML(RenderWindow* _window);
	~SFML(void);

	inline Color Box2dSFMLcolor(const b2Color& _color);
	void DrawSolidPolygon(const b2Vec2* _vertices, int32 _vertexCount, const b2Color& _color) override;
	void DrawAABB(b2AABB* _aabb, const b2Color& _color);
	void DrawPolygon(const b2Vec2* _vertices, int32 _vertexCount, const b2Color& _color) override;
	void DrawCircle(const b2Vec2& _center, float _radius, const b2Color& _color) override;
	void DrawSolidCircle(const b2Vec2& _center, float _radius, const b2Vec2& a_xis, const b2Color& _color) override;
	void DrawSegment(const b2Vec2& _p1, const b2Vec2& _p2, const b2Color& _color) override;
	void DrawTransform(const b2Transform& _xf) override;
	void DrawPoint(const b2Vec2& _p, float _size, const b2Color& _color) override;
	void DrawString(int _x, int _y, const char* _string, ...);
};