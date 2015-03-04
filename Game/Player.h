#pragma once

#include "GameObject.h"
#include <SDL.h>
#include "Missile.h"

struct SDL_Surface;
struct SDL_Window;
struct SDL_Texture;

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Initialize(SDL_Renderer * renderer, char* file);

	void Update(float dt);
	void Draw(SDL_Renderer *renderer, float dt);

	void PlayerBounceWalls(Vector2* position, Vector2* vector, float dt);


	Vector2 tankPos;
	Vector2 _tankOffset;


	SDL_Rect posRect;
	float rotation;

	SDL_Point center;

	Missile _missile;

	bool _playerAlive;
	float _playerDeathTimer;

protected:

	float _speed;
	float _rotationSpeed;
	float _timeDead;
	Vector3 _directionVector;
	SDL_Rect _tankRect;
	SDL_Texture *_tankTexture;

};