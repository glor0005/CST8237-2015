#include "Game.h"
#include "InputManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <istream>

// Initializing our static member pointer.
GameEngine* GameEngine::_instance = nullptr;

GameEngine* GameEngine::CreateInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Game();
	}
	return _instance;
}

Game::Game() : GameEngine()
{

}

Game::~Game()
{
}

void Game::InitializeImpl(SDL_Renderer * renderer)
{

	// Using the default member-wise initializer for our new struct.
	_player1.Initialize(renderer, "MechaTank01.png");
	_player1.tankPos = { 50, 50 };
	_player2.Initialize(renderer, "MechaTank02.png");
	_player2.tankPos = { 580, 580 };

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	player1Score = 0;
	player2Score = 0;

	sprintf(buffer, "Assignment 02 by Juan Marco Gloriani \t - \t Player 1: %i \t\t - \t\t Player 2: %i", player1Score, player2Score);
	SDL_SetWindowTitle(_window, buffer);
}



void Game::UpdateImpl(float dt)
{
	InputManager *im = InputManager::GetInstance();
	im->Update(dt);

	// Check for user input.
	if (_player1._playerAlive)
	{
		if (im->IsKeyDown(SDLK_UP) == true) // move forward towards the positive direction
		{
			_player1.tankPos.x += 20.0 * sinf(MathUtils::ToRadians(_player1.rotation))*dt;
			_player1.tankPos.y -= 20.0 * cosf(MathUtils::ToRadians(_player1.rotation))*dt;


		}
		if (im->IsKeyDown(SDLK_DOWN) == true) // move forward towards the negative direction
		{

		}
		if (im->IsKeyDown(SDLK_LEFT) == true) // rotate 10 degrees to the left
		{
			_player1.rotation -= 50.0f * dt;

		}
		if (im->IsKeyDown(SDLK_RIGHT) == true) // rotate 10 degrees to the right
		{
			_player1.rotation += 50.0f * dt;
		}
		if (im->IsKeyDown(SDLK_LCTRL) == true) // FULL STOP!
		{
			_player1.tankPos.x = 400;
			_player1.tankPos.y = 400;
		}
		if (im->IsKeyDown(SDLK_SPACE) == true && _player2._playerAlive == true)
		{
			_player1._missile._missileFired = true;
			//printf("true!\n");
		}
	}

	if (_player2._playerAlive)
	{
		if (im->IsKeyDown(SDLK_e) == true)
		{
			_player2.tankPos.x += 20.0 * sinf(MathUtils::ToRadians(_player2.rotation))*dt;
			_player2.tankPos.y -= 20.0 * cosf(MathUtils::ToRadians(_player2.rotation))*dt;

		}
		if (im->IsKeyDown(SDLK_s) == true)
		{
			_player2.rotation -= 50.0f * dt;
		}
		if (im->IsKeyDown(SDLK_a) == true && _player1._playerAlive == true)
		{
			_player2._missile._missileFired = true;
			//printf("true!\n");
		}
		if (im->IsKeyDown(SDLK_f) == true)
		{
			_player2.rotation += 50.0f * dt;
		}
	}
	//printf("%0.2f\n", _player1Pos.x);

	_player1.Update(dt);
	_player2.Update(dt);

	Collision(&_player1, &_player2);

	if (_player1._missile._missileLive)
	{
		_player1._missile.Update(dt);

	}
	if (_player2._missile._missileLive)
	{
		_player2._missile.Update(dt);

	}
}

void Game::DrawImpl(SDL_Renderer *renderer, float dt)
{
	// Set the draw colour for screen clearing.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	// Clear the renderer with the current draw colour.
	//SDL_RenderClear(renderer);

	//Borders
	SDL_RenderDrawLine(renderer, 10, 10, 10, 630);
	SDL_RenderDrawLine(renderer, 10, 10, 630, 10);
	SDL_RenderDrawLine(renderer, 10, 630, 630, 630);
	SDL_RenderDrawLine(renderer, 630, 10, 630, 630);

	_player1.Draw(renderer, dt);
	_player2.Draw(renderer, dt);

	if (_player1._missile._missileFired == true && _player1._missile._missileLive == false)
	{
		_player1._missile.SetPosition(_player1.tankPos);
		_player1._missile.SetRotation(_player1.rotation);
		_player1._missile.Initialize(renderer, NULL);

		_player1._missile._missileLive = true;
		printf("Player 1 fired!\n");
		_player1._missile._missileFired = false;
	}
	if (_player2._missile._missileFired == true && _player2._missile._missileLive == false)
	{
		_player2._missile.SetPosition(_player2.tankPos);
		_player2._missile.SetRotation(_player2.rotation);
		_player2._missile.Initialize(renderer, NULL);

		_player2._missile._missileLive = true;
		printf("Player 2 fired!\n");
		_player2._missile._missileFired = false;
	}

	if (_player1._missile._missileLive)
	{
		_player1._missile.Draw(renderer, dt);
	}
	if (_player2._missile._missileLive)
	{
		_player2._missile.Draw(renderer, dt);
	}

}

void Game::Collision(Player* player1, Player* player2)
{
	if (player2->_missile._missileLive)
	{
		if ((WithinBounds(player1->tankPos, 25.0, player2->_missile._missilePosition)))
		{
			player2->_missile._missileLive = false;
			player2->_missile._missileFired = false;
			player1->_playerAlive = false;
			printf("1 is hit!\n");
			player2Score++;
			player1->_playerDeathTimer = 1.0f;
			sprintf(buffer, "Assignment 02 by Juan Marco Gloriani \t - \t Player 1: %i \t\t - \t\t Player 2: %i", player1Score, player2Score);
			SDL_SetWindowTitle(_window, buffer);
		}
	}
	if (player1->_missile._missileLive)
	{
		if ((WithinBounds(player2->tankPos, 25.0, player1->_missile._missilePosition)))
		{
			player1->_missile._missileLive = false;
			player1->_missile._missileFired = false;
			player2->_playerAlive = false;
			printf("2 is hit\n");
			player1Score++;
			player2->_playerDeathTimer = 1.0f;
			sprintf(buffer, "Assignment 02 by Juan Marco Gloriani \t - \t Player 1: %i \t\t - \t\t Player 2: %i", player1Score, player2Score);
			SDL_SetWindowTitle(_window, buffer);
		}
	}

	if ((WithinBounds(player1->tankPos, 35.0, player2->tankPos)))
	{
		player1->tankPos = { player1->tankPos.x - (player2->tankPos.x - player1->tankPos.x) / 5, player1->tankPos.y - (player2->tankPos.y - player1->tankPos.y) / 5 };
		player2->tankPos = { player2->tankPos.x + (player2->tankPos.x - player1->tankPos.x) / 5, player2->tankPos.y + (player2->tankPos.y - player1->tankPos.y) / 5 };
		printf("Bump");
	}

}

/*
* bool Game::WithinBounds(Vector2 centre, float targetRadius, Vector2 targetCentre)
* Brief: Function to check if distance between two points are within a certain radius
* Param:
*	centre - coordinate of first point
*	targetRadius - the length of measured point
*	targetCentre - coordinate of the other point
*/
bool Game::WithinBounds(Vector2 centre, float targetRadius, Vector2 targetCentre)
{
	if (CalcDistance(centre, targetCentre) < targetRadius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
* float Game::CalcDistance(Vector2 v1, Vector2 v2)
* Brief: Calculates the distance between two points
* Param:
*	v1 - coordinate of first point
*	v2 - coordinate of second point
*/
float Game::CalcDistance(Vector2 v1, Vector2 v2)
{
	return (sqrt((v2.x - v1.x)*(v2.x - v1.x) + (v2.y - v1.y)*(v2.y - v1.y)));
}

/*f
* loat Game::CalcDistanceOffSet(Vector2 v1)
* Brief: Calculates the Distance for a certain offset
* Param : v1 - Vector2 of a point
*/
float Game::CalcDistanceOffSet(Vector2 v1)
{
	return (sqrt((v1.x*v1.x) + v1.y*v1.y));
}