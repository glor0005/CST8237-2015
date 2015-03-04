#include "Player.h"
#include <math.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

Player::Player() : GameObject()
{
	_transform.position = { 320.0f, 320.0f, 0.0f }; //Player spawn point
}

Player::~Player()
{
	SDL_DestroyTexture(_tankTexture);
}

void Player::Initialize(SDL_Renderer * renderer, char* file)
{
	_tankTexture = IMG_LoadTexture(renderer, file);
	if (_tankTexture == NULL){
		printf(SDL_GetError());
	}
	int w = 10, h = 10;
	if (SDL_QueryTexture(_tankTexture, NULL, NULL, &w, &h) == -1){
		printf(SDL_GetError());
	}
	_tankRect.w = w;
	_tankRect.h = h;

	rotation = 0.0f;
	posRect = { 80, 80, 0, 0 };

	_playerAlive = true;
	//tankPos = { 400, 400 };

}

void Player::Update(float dt)
{

	//Resets the rotation value if the degrees exceeds 360°
	rotation += (rotation >= 360.0f ? -360.0f : 0);

	if (!_playerAlive)
	{
		_playerDeathTimer -= dt;
		rotation += 2500 * dt;
	}

	if (_playerDeathTimer < 0)
	{
		_playerAlive = true;
	}

}

void Player::Draw(SDL_Renderer *renderer, float dt)
{

	center.x = 15;
	center.y = 25;


	posRect.x = (tankPos.x - 15);
	posRect.y = (tankPos.y - 25);


	posRect.w = 45;//30
	posRect.h = 50;

	_tankOffset = { 10.0 * sinf(MathUtils::ToRadians(rotation)), -10.0 * cosf(MathUtils::ToRadians(rotation)) };

	PlayerBounceWalls(&tankPos, &_tankOffset, dt);

	SDL_RenderCopyEx(renderer, _tankTexture, NULL, &posRect, rotation, &center, SDL_FLIP_NONE);
}

void Player::PlayerBounceWalls(Vector2* position, Vector2* vector, float dt)
{
	//Border Wall Handler
	if (position->x < 10 || position->x > 630 || position->y < 10 || position->y > 630)
	{
		*position = { position->x - vector->x, position->y - vector->y };
		printf("Border hit");
	}
}
