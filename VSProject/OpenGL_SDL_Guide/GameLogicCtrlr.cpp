#include "GameLogicCtrlr.h"
#include "GameObject.h"
#include "GameObjectCtrlr.h"
#include "ProgramCtrlr.h"

#include "PlayerObject.h"
#include "BulletObject.h"
#include "EnemyObject.h"

#include <ctime>
#include <iostream>

// Singleton ============================================

// Constructor
GameLogicCtrlr::GameLogicCtrlr()
{
	this->gameOver = false;
}

// Public singleton instance getter
GameLogicCtrlr* GameLogicCtrlr::GetInstance()
{
	return GameLogicCtrlr::privGetInstance();
}

// Private singleton handler
GameLogicCtrlr* GameLogicCtrlr::privGetInstance()
{
	// Static object only initializes once
	static GameLogicCtrlr instance;
	return &instance;
}

// Game Structure ========================================

// Create objects before the main loop
void GameLogicCtrlr::InitializeGame()
{
	/*
	for(int i = 1; i < 6; i++)
	{
		GameObject* obj = new GameObject();

		obj->SetPosition((float) -i, (float) i, 0);
		obj->SetEulerAngles(i*10.0f, i*10.0f, i*10.0f);
		obj->SetScale(i/5.0f, i/5.0f, i/5.0f);
		obj->SetTextureUnit(0);
		obj->SetColorTint(0.2f*i, 1.0f, 0.2f*i, 1.0f);

		GameObjectCtrlr::GetInstance()->Add(obj);
	}
	//*/

	// Make random number between EDGE_BORDER and -EDGE_BORDER
	float randomSpawnPos = GameLogicCtrlr::GetRandomNumber((int) EDGE_BORDER);
	//float randomSpawnPos = 9.0f;

	// Make a player
	PlayerObject* player = new PlayerObject(glm::vec3(0.0f, 0.0f, 0.0f));
	GameObjectCtrlr::GetInstance()->Add(player);

	// Make an enemy
	EnemyObject* enemy = new EnemyObject(glm::vec3(0.0f, 
												   randomSpawnPos, 
												   ENEMY_SPAWN_HEIGHT));
	float randScale = ((GameLogicCtrlr::GetRandomNumber(2) + 2) / 2.0f) + 0.5f;
	enemy->SetScale(randScale, randScale, randScale);
	GameObjectCtrlr::GetInstance()->Add(enemy);

	this->gameOver = false;
}

// The main loop itself
void GameLogicCtrlr::LoopGame()
{
	// Mark the program for reset if Game Over
	if((this->IsGameOver()))
	{
		
	}
}

// Delete objects after the main loop
void GameLogicCtrlr::ReleaseGame()
{
	// Reset game over flag
	this->gameOver = false;
}

// Routines ===============================================

// Get the squared distance between two objects
float GameLogicCtrlr::GetSquaredDistance(GameObject* obj1, GameObject* obj2)
{
	// Get difference is positions for each dimension
	float deltaX = obj1->GetPosition().x - obj2->GetPosition().x;
	float deltaY = obj1->GetPosition().y - obj2->GetPosition().y;
	float deltaZ = obj1->GetPosition().z - obj2->GetPosition().z;

	// Distance formula without the square root
	float squareDistance = deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ;

	return squareDistance;
}

// Check of two GameObjects overlap
bool GameLogicCtrlr::DoObjectsOverlap(GameObject* obj1, GameObject* obj2)
{
	float bothRadii = obj1->GetRadius() + obj2->GetRadius();
	float squaredDistance = GameLogicCtrlr::GetSquaredDistance(obj1, obj2);

	// Compare distance^2 with bothRadii^2
	return squaredDistance < (bothRadii*bothRadii);
}

// Generate random number between x and -x
float GameLogicCtrlr::GetRandomNumber(int x)
{
	// Use current time as seed
	std::srand( (unsigned int) std::time(0) );

	// Generate random number
	float randomNumber = (float) ((std::rand() % ((2*x)+1) ) - x );

	return randomNumber;
}

// Make Player shoot Bullet
void GameLogicCtrlr::MakePlayerShootBullet()
{
	if(this->playerInstance != NULL)
	{
		this->playerInstance->ShootBullet();
	}
}

// Make Player move left
void GameLogicCtrlr::MakePlayerMoveLeft()
{
	if(this->playerInstance != NULL)
	{
		this->playerInstance->MoveLeft();
	}
}

// Make Player move right
void GameLogicCtrlr::MakePlayerMoveRight()
{
	if(this->playerInstance != NULL)
	{
		this->playerInstance->MoveRight();
	}
}

// Properties ===========================

void GameLogicCtrlr::SetBulletInstance(GameObject* newBullet)
{
	this->bulletInstance = newBullet;
}

void GameLogicCtrlr::SetPlayerInstance(PlayerObject* newPlayer)
{
	this->playerInstance = newPlayer;
}

void GameLogicCtrlr::DeclareGameOver()
{
	this->gameOver = true;

	std::cout << "Game Over!" << std::endl;
	GameObject* gameOverSplash = new GameObject();
	gameOverSplash->SetTextureUnit(1);
	gameOverSplash->SetPosition(18.0f, 0.0f, 13.0f);
	gameOverSplash->SetScale(1.0f, 2.0f, 2.0f);
	GameObjectCtrlr::GetInstance()->Add(gameOverSplash);
}

GameObject* GameLogicCtrlr::GetBulletInstance()
{
	return this->bulletInstance;
}

PlayerObject* GameLogicCtrlr::GetPlayerInstance()
{
	return this->playerInstance;
}

bool GameLogicCtrlr::IsGameOver()
{
	return this->gameOver;
}