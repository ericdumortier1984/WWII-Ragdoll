#include "Sfml_renderer.h"

SFML::SFML(RenderWindow* _window)
{

    _wnd = _window;
}

SFML::~SFML(void)
{
}

void SFML::DrawSolidPolygon(const b2Vec2* _vertices, int32 _vertexCount, const b2Color& _color)
{
    ConvexShape polygon;
    polygon.setFillColor(Box2dSFMLcolor(_color));
    polygon.setOutlineColor(Box2dSFMLcolor(_color));

    polygon.setPointCount(_vertexCount);
    for (int i = 0; i < _vertexCount; ++i)
        polygon.setPoint(i, Vector2f(_vertices[i].x, _vertices[i].y));

    _wnd->draw(polygon);
}

void SFML::DrawPolygon(const b2Vec2* _vertices, int32 _vertexCount, const b2Color& _color)
{
    ConvexShape polygon;
    polygon.setFillColor(Color(0, 0, 0, 0));
    polygon.setOutlineColor(Box2dSFMLcolor(_color));

    polygon.setPointCount(_vertexCount);
    for (int i = 0; i < _vertexCount; ++i)

        _wnd->draw(polygon);
}

void SFML::DrawCircle(const b2Vec2& _center, float _radius, const b2Color& _color)
{
    sf::CircleShape circle(_radius);
    circle.setOrigin(_radius, _radius);
    circle.setPosition(_center.x, _center.y);
    circle.setFillColor(Color(0, 0, 0, 0));
    circle.setOutlineColor(Box2dSFMLcolor(_color));

    _wnd->draw(circle);
}

void SFML::DrawSolidCircle(const b2Vec2& _center, float _radius, const b2Vec2& _axis, const b2Color& _color)
{
    CircleShape circle(_radius);
    circle.setOrigin(_radius, _radius);
    circle.setPosition(_center.x, _center.y);
    circle.setFillColor(Box2dSFMLcolor(_color));
    circle.setOutlineColor(Box2dSFMLcolor(_color));

    _wnd->draw(circle);
}

void SFML::DrawSegment(const b2Vec2& _p1, const b2Vec2& _p2, const b2Color& _color)
{
    Vertex line[] =
    {
        Vertex(Vector2f(_p1.x, _p1.y), Box2dSFMLcolor(_color)),
        Vertex(Vector2f(_p2.x, _p2.y), Box2dSFMLcolor(_color))
    };

    _wnd->draw(line, 2, Lines);
}

void SFML::DrawTransform(const b2Transform& _xf)
{

    b2Vec2 p1 = _xf.p, p2;
    const float k_axisScale = 20.0f;
    p2 = p1 + k_axisScale * _xf.q.GetXAxis();

    Vertex line[] =
    {
        Vertex(Vector2f(p1.x, p1.y), Color::Red),
        Vertex(Vector2f(p2.x, p2.y), Color::Green)
    };
    _wnd->draw(line, 2, Lines);

    p2 = p1 + k_axisScale * _xf.q.GetYAxis();

    Vertex line2[] =
    {
        Vertex(Vector2f(p1.x, p1.y), Color::Blue),
        Vertex(Vector2f(p2.x, p2.y), Color::Yellow)
    };
    _wnd->draw(line2, 2, Lines);
}

void SFML::DrawPoint(const b2Vec2& _p, float _size, const b2Color& _color)
{
    const float radius = 0.5f;
    CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(_p.x, _p.y);
    circle.setFillColor(Box2dSFMLcolor(_color));
    circle.setOutlineColor(Box2dSFMLcolor(_color));

    _wnd->draw(circle);
}

void SFML::DrawString(int _x, int _y, const char* _string, ...)
{
    Text text;

    text.setString(_string);
    text.setPosition(_x, _y);

    _wnd->draw(text);
}


void SFML::DrawAABB(b2AABB* _aabb, const b2Color& _color)
{
    const auto halfSize = _aabb->GetExtents();
    RectangleShape rectangle(Vector2f(halfSize.x, halfSize.y) * 2.f);
    rectangle.setOrigin(halfSize.x, halfSize.y);
    const auto center = _aabb->GetCenter();
    rectangle.setPosition(center.x, center.y);
    rectangle.setFillColor(Color(0, 0, 0, 0));
    rectangle.setOutlineColor(Box2dSFMLcolor(_color));

    _wnd->draw(rectangle);
}

Color SFML::Box2dSFMLcolor(const b2Color& _color)
{

    Uint8 R, G, B;
    R = (Uint8)(_color.r * 255);
    G = (Uint8)(_color.g * 255);
    B = (Uint8)(_color.b * 255);

    return Color(R, G, B);
}