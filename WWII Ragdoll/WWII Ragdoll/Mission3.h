#pragma once
#include "MainHeader.h"
#include "Box2d.h"
#include "Sfml_renderer.h"
#include "Avatar.h"

class Mission3
{

private:

	//enteros
	int _width;
	int _height;
	int _fps;
	int _ragdollsCounter;

	//flotantes
	float _frametime;
	float _angle;
	float _force;

	//booleanos
	bool _shot;
	bool _gameStarted;
	bool _gameRestarted;

	//Ventana
	RenderWindow* _wnd;

	//SFML
	SFML* _render;
	Color _clearColor;

	//Box2D
	b2World* _world;
	b2Body* _bodies[6];
	b2Body* _limitsScreen[4];
	b2Body* _barrel[2];
	b2Body* _platform;
	b2Body* _cannon;

	//Texturas y sprites
	Texture* _M1Tx;
	Sprite* _M1Sp;
	Sprite* _tankSp;
	Texture* _tankTex;

	Avatar* _tank;

	//Vector para posicion del tanque
	Vector2f _cannonPos;

	//Audio
	Music _musicM1;
	SoundBuffer _startGame;

	//Fuente
	Font _font;
	Text _text;

	//funciones privadas
	void InitPhysics();
	void UpdatePhysics();
	void DoEvents();
	void SetZoom();
	void DrawGame();

	void GamePause();

	void CreateAndShootRagdoll(float angle, float force);
	void UpdateCannonPosition();
	float CalculateCannonAngle(Vector2f _mousePosition);
public:

	//constructor y deconstuctor
	Mission3(int _width, int _height);
	~Mission3(void);

	//funcion publica
	void Loop();
};