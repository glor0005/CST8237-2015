#pragma once

#include <GameEngine.h>
#include "Player.h"
union SDL_Event;
struct SDL_Texture;
struct SDL_Renderer;

class Game : public GameEngine
{
	friend class GameEngine;
public:
	~Game();

protected:
	Game();

	void InitializeImpl(SDL_Renderer *renderer);
	void UpdateImpl(float dt);
	void DrawImpl(SDL_Renderer *renderer, float dt);

	void Collision(Player* player1, Player* player2);
	bool WithinBounds(Vector2 centre, float targetRadius, Vector2 targetCentre);
	float CalcDistance(Vector2 v1, Vector2 v2);
	float CalcDistanceOffSet(Vector2 v1);

	Player _player1;
	Player _player2;

	int player1Score;
	int player2Score;

	char buffer[50];
};
