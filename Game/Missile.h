#pragma once

#include "GameObject.h"
#include "Missile.h"

class Missile : public GameObject
{
public:
	Missile();
	~Missile();

	void Initialize(SDL_Renderer * renderer, char* file);

	Vector2 _missilePosition;
	Vector2 _missileOffSet;

	int _missileLife;

	bool _missileFired = false;
	bool _missileLive = false;


	void Update(float dt);
	void Draw(SDL_Renderer *renderer, float dt);
	void Reform(Vector2* point);
	void Reform3(Vector3* point);

	Transform& GetTransform();
	void SetTransform(Transform transform);
	void Missile::SetPosition(Vector2 position);
	void Missile::SetRotation(float rotation);

	void MissileBounceWalls(Vector2* point, Vector2* vector, float dt, int* missileLife);
};
