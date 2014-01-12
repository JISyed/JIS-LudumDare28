#include "EnemyObject.h"

#include "GameLogicCtrlr.h"
#include "PlayerObject.h"
#include "TimeCtrlr.h"
#include "RandomCtrlr.h"
#include "DifficultyCtrlr.h"

#include <iostream>

// Ctor / Dtor ===========================================

// Constructor
EnemyObject::EnemyObject()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	
	// Initialize other properties
	this->init();

	// Update patent class's data
	this->updateMatrices();
}

// Position constructor
EnemyObject::EnemyObject(glm::vec3 initialPos)
{
	this->position = initialPos;
	
	// Initialize other properties
	this->init();

	// Update patent class's data
	this->updateMatrices();
}

// Destructor
EnemyObject::~EnemyObject()
{

}

// Routines ===============================================

void EnemyObject::Update()
{
	// Collision with bullet
	GameObject* bullet = GameLogicCtrlr::GetInstance()->GetBulletInstance();
	if(bullet != NULL)
	{
		if(GameLogicCtrlr::DoObjectsOverlap(this, bullet))
		{
			// Delete both enemy and bullet
			this->MarkForDeletion();
			bullet->MarkForDeletion();
			return;
		}
	}

	// Collision with player and score keeping
	PlayerObject* player = GameLogicCtrlr::GetInstance()->GetPlayerInstance();
	if(player != NULL)
	{
		// Collision with player
		if(GameLogicCtrlr::DoObjectsOverlap(this, player))
		{
			// Delete player only
			player->MarkForDeletion();
		}

		// Score increments when an enemy passes by the player
		if( ! this->alreadyPassedByPlayer )
		{
			if(this->position.z < player->GetPosition().z)
			{
				this->alreadyPassedByPlayer = true;
				GameLogicCtrlr::GetInstance()->IncrementScore();
				std::cout << "Score: " << GameLogicCtrlr::GetInstance()->GetScore() << std::endl;
			}
		}
	}

	// Delete bullet if to far down
	if(this->position.z < VISIBLE_BOTTOM)
	{
		this->MarkForDeletion();
		return;
	}

	// Move along positive Z
	glm::vec3 newPosition = this->position;
	float dt = TimeCtrlr::GetInstance()->GetDeltaTime();
	this->speed = this->speed + (this->accel * dt);
	float zDisplace = newPosition.z - (this->speed * dt);
	newPosition = glm::vec3(newPosition.x, newPosition.y, zDisplace);
	this->SetPosition(newPosition);

	// Run parent's update
	GameObject::Update();
}

// Helpers ================================================

// Initialization after construction
void EnemyObject::init()
{
	RandomCtrlr* rand = RandomCtrlr::GetInstance();
	DifficultyCtrlr* diffScl = DifficultyCtrlr::GetInstance();

	// Set other properties
	this->eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(0.8f, 0.8f, 1.0f);
	this->radius = 0.5f;
	this->colorTint = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);	// Red
	this->alreadyPassedByPlayer = false;

	// Set speed and acceleration
	float sso = diffScl->GetSpawnSpeedOffset();
	this->speed = rand->Range(6.0f, 8.0f + sso);
	float sao = diffScl->GetSpawnAccelOffset();
	this->accel = rand->Range(8.0f, 10.0f + sao);
}