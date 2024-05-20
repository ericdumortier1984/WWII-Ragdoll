#include "Main Menu.h"
#include "Mission1.h"

Mission1::Mission1(int _width, int _height)
{

	_wnd = new RenderWindow(VideoMode(_width, _height), "Mission 1");
	_fps = 60;
	_frametime = 1.f / _fps;
	_wnd->setFramerateLimit(_fps);
	InitPhysics();
	SetZoom();
	_shot = false;
	_gameRestarted = false;
	_cannonPos = Vector2f(6.f, 92.f);
}

void Mission1::Loop()
{

	while (_wnd->isOpen())
	{
		_wnd->clear(_clearColor);
		DoEvents();
		DrawGame();
		UpdatePhysics();
		UpdateCannonPosition();
		_wnd->display();
	}
}

void Mission1::DoEvents()
{

	Event evt;
	while (_wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::KeyPressed:
			if (evt.key.code == Keyboard::Escape)
			{
				_wnd->close();
			}
			break;

		case Event::MouseMoved:
			UpdateCannonPosition();
			break;

		case Event::MouseButtonPressed:
			if (evt.mouseButton.button == Mouse::Left)
			{
				_shot = true;
				Vector2i mousePos = Mouse::getPosition(*_wnd);
				Vector2f mousePosWorld = _wnd->mapPixelToCoords(mousePos);
				float cannonAngle = CalculateCannonAngle(mousePosWorld);
				float distance = sqrt(pow(mousePosWorld.x - _cannonPos.x, 2) + pow(mousePosWorld.y - _cannonPos.y, 2));
				float force = 50.f + (distance * 2.f);
				CreateAndShootRagdoll(cannonAngle, force);
			}
			break;

		case Event::MouseButtonReleased:
			if (evt.mouseButton.button == Mouse::Left)
			{
				_shot = false;
			}
			break;
		}
		if (evt.type == Event::KeyPressed)
		{
			if (evt.key.code == Keyboard::P)
			{
				GamePause();
			}
		}
		if (evt.type == Event::KeyPressed)
		{
			if (evt.key.code == Keyboard::R)
			{
				RestartGame();
			}
		}
	}
}

void Mission1::InitPhysics()
{

	_world = new b2World(b2Vec2(0.f, 9.8f));
	_render = new SFML(_wnd);
	_render->SetFlags(UINT_MAX);
	_world->SetDebugDraw(_render);

	//plataforma
	_platform = Box2d::CreateRectangularStaticBody(_world, 15.f, 3.f);
	_platform->SetTransform(b2Vec2(80.f, 30.f), 0.f);

	//barriles
	_barrel[0] = Box2d::CreateRectangularDynamicBody(_world, 5.f, 10.f, 0.5f, 0.f, 0.f);
	_barrel[0]->SetTransform(b2Vec2(75.f, 25.f), 0.f);
	_barrel[1] = Box2d::CreateRectangularDynamicBody(_world, 5.f, 10.f, 0.5f, 0.f, 0.f);
	_barrel[1]->SetTransform(b2Vec2(85.f, 25.f), 0.f);

	//limites de la pantalla
	_limitsScreen[0] = Box2d::CreateRectangularStaticBody(_world, 2.5f, 100.f);
	_limitsScreen[0]->SetTransform(b2Vec2(100.f, 50.f), 0.f);
	_limitsScreen[1] = Box2d::CreateRectangularStaticBody(_world, 2.5f, 100.f);
	_limitsScreen[1]->SetTransform(b2Vec2(0.f, 50.f), 0.f);
	_limitsScreen[2] = Box2d::CreateRectangularStaticBody(_world, 100.f, 2.5f);
	_limitsScreen[2]->SetTransform(b2Vec2(50.f, 0.f), 0.f);
	_limitsScreen[3] = Box2d::CreateRectangularStaticBody(_world, 100.f, 2.5f);
	_limitsScreen[3]->SetTransform(b2Vec2(50.f, 100.f), 0.f);

	//Ca�on
	_cannon[0] = Box2d::CreateRectangularKinematicBody(_world, 10.f, 5.f); // Cuerpo
	_cannon[1] = Box2d::CreateCircularStaticBody(_world, 2.f); // Rueda
	_cannon[1]->SetTransform(b2Vec2(4.f, 96.f), 0.f);

	Box2d::CreateDistanceJoint(_world, _cannon[1], b2Vec2(_cannon[1]->GetWorldCenter()), _cannon[0], b2Vec2(_cannon[0]->GetWorldCenter()), 0.f, 0.f, 1.f);

	//ragdoll
	_bodies[0] = Box2d::CreateCircularDynamicBody(_world, 1.f, 0.3f, 0.f, 0.1f); // Cabeza
	_bodies[1] = Box2d::CreateRectangularDynamicBody(_world, 2.f, 4.f, 1.f, 0.f, 0.1f); // Pecho
	_bodies[2] = Box2d::CreateRectangularDynamicBody(_world, 1.f, 2.f, 0.1f, 0.f, 0.1f); // Brazo izquierdo
	_bodies[3] = Box2d::CreateRectangularDynamicBody(_world, 1.f, 2.f, 0.1f, 0.f, 0.1f); // Brazo derecho
	_bodies[4] = Box2d::CreateRectangularDynamicBody(_world, 1.f, 2.f, 0.1f, 0.f, 0.1f); // Pierna izquierda
	_bodies[5] = Box2d::CreateRectangularDynamicBody(_world, 1.f, 2.f, 0.1f, 0.f, 0.1f); // Pierna derecha
}

void Mission1::UpdatePhysics()
{

	_world->Step(_frametime, 8, 8);
	_world->ClearForces();
	_world->DebugDraw();

}

void Mission1::SetZoom()
{

	View camara;
	camara.setSize(100.f, 100.f);
	camara.setCenter(50.f, 50.f);
	_wnd->setView(camara);
}

void Mission1::CreateAndShootRagdoll(float angle, float force)
{

	Vector2i mousePos = Mouse::getPosition(*_wnd);
	Vector2f mousePosWorld = _wnd->mapPixelToCoords(mousePos);

	// ragdolls
	b2Body* _bodies[6];
	_bodies[0] = Box2d::CreateCircularDynamicBody(_world, 1.f, 0.3f, 0.f, 0.1f); // Cabeza
	_bodies[1] = Box2d::CreateRectangularDynamicBody(_world, 2.f, 4.f, 1.f, 0.f, 0.1f); // Pecho
	_bodies[2] = Box2d::CreateRectangularDynamicBody(_world, 1.f, 2.f, 0.1f, 0.f, 0.1f); // Brazo izquierdo
	_bodies[3] = Box2d::CreateRectangularDynamicBody(_world, 1.f, 2.f, 0.1f, 0.f, 0.1f); // Brazo derecho
	_bodies[4] = Box2d::CreateRectangularDynamicBody(_world, 1.f, 2.f, 0.1f, 0.f, 0.1f); // Pierna izquierda
	_bodies[5] = Box2d::CreateRectangularDynamicBody(_world, 1.f, 2.f, 0.1f, 0.f, 0.1f); // Pierna derecha

	//posiciones
	_bodies[0]->SetTransform(b2Vec2(_cannon[0]->GetWorldCenter().x + 9.5f, _cannon[0]->GetWorldCenter().y), 0.f);
	_bodies[1]->SetTransform(b2Vec2(_cannon[0]->GetWorldCenter().x + 9.5f, _cannon[0]->GetWorldCenter().y + 3.f), 0.f);
	_bodies[2]->SetTransform(b2Vec2(_cannon[0]->GetWorldCenter().x + 8.5f, _cannon[0]->GetWorldCenter().y + 2.f), -50.f);
	_bodies[3]->SetTransform(b2Vec2(_cannon[0]->GetWorldCenter().x + 10.5f, _cannon[0]->GetWorldCenter().y + 2.f), 50.f);
	_bodies[4]->SetTransform(b2Vec2(_cannon[0]->GetWorldCenter().x + 8.5f, _cannon[0]->GetWorldCenter().y + 5.f), -50.f);
	_bodies[5]->SetTransform(b2Vec2(_cannon[0]->GetWorldCenter().x + 10.5f, _cannon[0]->GetWorldCenter().y + 5.f), 50.f);

	//joints
	Box2d::CreateDistanceJoint(_world, _bodies[0], b2Vec2(_bodies[0]->GetWorldCenter()), _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2d::CreateRevoluteJoint(_world, _bodies[1], b2Vec2(_bodies[0]->GetWorldCenter().x, _bodies[0]->GetWorldCenter().y), _bodies[0], -b2_pi * 0.4f, b2_pi * 0.4f, 0.f, 0.f, false, true);
	Box2d::CreateDistanceJoint(_world, _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter()), _bodies[2], b2Vec2(_bodies[2]->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2d::CreateRevoluteJoint(_world, _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter().x, _bodies[2]->GetWorldCenter().y), _bodies[2], -b2_pi * 1.f, b2_pi * 0.6f, 0.f, 0.f, false, true);
	Box2d::CreateDistanceJoint(_world, _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter()), _bodies[3], b2Vec2(_bodies[3]->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2d::CreateRevoluteJoint(_world, _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter().x, _bodies[3]->GetWorldCenter().y), _bodies[3], -b2_pi * 1.f, b2_pi * 0.6f, 0.f, 0.f, false, true);
	Box2d::CreateDistanceJoint(_world, _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter()), _bodies[4], b2Vec2(_bodies[4]->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2d::CreateRevoluteJoint(_world, _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter().x, _bodies[4]->GetWorldCenter().y), _bodies[4], -b2_pi * 0.4f, b2_pi * 0.4f, 0.f, 0.f, false, true);
	Box2d::CreateDistanceJoint(_world, _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter()), _bodies[5], b2Vec2(_bodies[5]->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2d::CreateRevoluteJoint(_world, _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter().x, _bodies[5]->GetWorldCenter().y), _bodies[5], -b2_pi * 0.4f, b2_pi * 0.4f, 0.f, 0.f, false, true);

	//impulsos
	b2Vec2 impulseForce(force * cos(angle * M_PI / 180.f), force * sin(angle * M_PI / 180.f));
	for (int i = 0; i < 6; i++)
	{
		_bodies[i]->ApplyLinearImpulse(impulseForce, _bodies[i]->GetPosition(), true);
	}
}

void Mission1::UpdateCannonPosition()
{

	Vector2i mousePos = Mouse::getPosition(*_wnd);
	Vector2f worldPosMouse = _wnd->mapPixelToCoords(mousePos);

	float dx = worldPosMouse.x - _cannonPos.x;
	float dy = worldPosMouse.y - _cannonPos.y;
	float distance = sqrt(dx * dx + dy * dy);
	float angle = atan2(dy, dx);
	float force = 50.0f + (distance * 2.0f);

	_cannon[0]->SetTransform(b2Vec2(_cannonPos.x, _cannonPos.y), angle);
}

float Mission1::CalculateCannonAngle(Vector2f _mouseWorldPos)
{

	float dx = _mouseWorldPos.x - _cannonPos.x;
	float dy = _mouseWorldPos.y - _cannonPos.y;
	float angleRad = atan2(dy, dx);
	float angleDeg = angleRad * 180 / M_PI;

	return angleDeg;
}

void Mission1::DrawGame()
{

}

void Mission1::GamePause()
{

	if (_gameStarted)
	{
		_gameStarted = false;
	}
	else
	{
		_gameStarted = true;
	}
}

void Mission1::RestartGame()
{

	_gameStarted = false;
	_gameRestarted = true;

}

Mission1::~Mission1(void)
{
	_world->DestroyBody(_bodies[6]);
	_world->DestroyBody(_barrel[2]);
	_world->DestroyBody(_cannon[2]);
	_world->DestroyBody(_platform);
	_world->DestroyBody(_limitsScreen[4]);
}
