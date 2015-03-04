#include "Missile.h"
#include <SDL.h>
#include <math.h>
#include <iostream>

Missile::Missile() : GameObject()
{

}

Missile::~Missile()
{

}

void Missile::Initialize(SDL_Renderer * renderer, char * file)
{
	_missilePosition = { _transform.position.x, _transform.position.y };

	Vector2 posOffset = { 10, 10 };

	_missileOffSet =
	{
		10 * sinf(MathUtils::ToRadians(_transform.rotation.x)),
		(-10) * cosf(MathUtils::ToRadians(_transform.rotation.x))
	};

	_missileLife = 2;

	printf("Missile Life: %d\n", _missileLife);

}

void Missile::Update(float dt)
{
	if (_missileLive)
	{
		//_missileLife -= dt;
		_missilePosition.x += (_missileOffSet.x*dt * 50);
		_missilePosition.y += (_missileOffSet.y*dt * 50);

	}
	if (_missileLife == 0)
	{
		printf("Missile erased!\n");
		_missileLive = false;
		_missileFired = false;
	}

}

void Missile::Draw(SDL_Renderer * renderer, float dt)
{
	if (_missileLive)
	{
		MissileBounceWalls(&_missilePosition, &_missileOffSet, dt, &_missileLife);

		SDL_RenderDrawLine
			(renderer,
			_missilePosition.x,
			_missilePosition.y,
			_missilePosition.x + _missileOffSet.x,
			_missilePosition.y + _missileOffSet.y
			);
	}
}

void Missile::Reform(Vector2* point)
{
	if (point->x > 640)
		point->x -= 640;
	if (point->x < 0)
		point->x += 640;
	if (point->y > 640)
		point->y -= 640;
	if (point->y < 0)
		point->y += 640;
}

void Missile::Reform3(Vector3* point)
{
	if (point->x > 640)
		point->x -= 640;
	if (point->x < 0)
		point->x += 640;
	if (point->y > 640)
		point->y -= 640;
	if (point->y < 0)
		point->y += 640;
	if (point->z > 640)
		point->z -= 640;
	if (point->z < 0)
		point->z += 640;
}

Transform& Missile::GetTransform()
{
	return _transform;
}

void Missile::SetTransform(Transform transform)
{
	this->_transform = transform;
}

void Missile::SetPosition(Vector2 position)
{
	this->_transform.position.x = position.x;
	this->_transform.position.y = position.y;
}

void Missile::SetRotation(float rotation)
{
	this->_transform.rotation.x = rotation;
}

void Missile::MissileBounceWalls(Vector2* position, Vector2* vector, float dt, int* missileLife)
{
	//Wall Handlers
	if (position->x < 10)
	{
		position->x = 10;
		vector->x = -vector->x;
		*missileLife = *missileLife - 1;
	}
	if (position->x > 630)
	{
		position->x = 630;
		vector->x = -vector->x;
		*missileLife = *missileLife - 1;
	}
	if (position->y < 10)
	{
		position->y = 10;
		vector->y = -vector->y;
		*missileLife = *missileLife - 1;
	}
	if (position->y > 630)
	{
		position->y = 630;
		vector->y = -vector->y;
		*missileLife = *missileLife - 1;
	}
}
