#include "GameLogicCtrlr.h"
#include "GameObject.h"
#include "GameObjectCtrlr.h"
#include "ProgramCtrlr.h"
#include "RandomCtrlr.h"
#include "TimeCtrlr.h"

#include "PlayerObject.h"
#include "BulletObject.h"
#include "EnemyObject.h"

#include <iostream>

// Singleton ============================================

// Constructor
GameLogicCtrlr::GameLogicCtrlr()
{
	this->gameOver = false;
	this->launchedEnemies = false;
	this->launchTimeInterval = 1.1f;
	this->launchTimeStamp = 0;
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
	// Make a player
	PlayerObject* player = new PlayerObject(glm::vec3(0.0f, 0.0f, 0.0f));
	GameObjectCtrlr::GetInstance()->Add(player);

	this->gameOver = false;
	this->launchedEnemies = false;
}

// The main loop itself
void GameLogicCtrlr::LoopGame()
{
	TimeCtrlr* time = TimeCtrlr::GetInstance();

	if(!launchedEnemies && !this->IsGameOver())
	{
		launchedEnemies = true;

		// Mark time stamp
		this->launchTimeStamp = time->GetRunTime() + this->launchTimeInterval;

		EnemyObject* enemy;
		float randSpawnPos;
		float randScale;

		// Make some enemies
		for(int i = 1; i < 6; i++)
		{
			randSpawnPos = RandomCtrlr::GetInstance()->Range(-EDGE_BORDER, EDGE_BORDER);
			enemy = NULL;
			enemy = new EnemyObject(glm::vec3(0.0f, randSpawnPos, ENEMY_SPAWN_HEIGHT));
			randScale = RandomCtrlr::GetInstance()->Range(0.5f, 3.0f);
			enemy->SetScale(randScale, randScale, randScale + randScale * 0.2f);
			GameObjectCtrlr::GetInstance()->Add(enemy);
		}
	}

	if( ( time->GetRunTime() > this->launchTimeStamp) && launchedEnemies)
	{
		launchedEnemies = false;
	}
}

// Delete objects after the main loop
void GameLogicCtrlr::ReleaseGame()
{
	// Reset game over flag
	this->gameOver = false;
	this->launchedEnemies = false;
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