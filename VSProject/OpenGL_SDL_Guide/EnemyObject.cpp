#include "EnemyObject.h"

#include "GameLogicCtrlr.h"
#include "PlayerObject.h"

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

	// Collision with player
	PlayerObject* player = GameLogicCtrlr::GetInstance()->GetPlayerInstance();
	if(player != NULL)
	{
		if(GameLogicCtrlr::DoObjectsOverlap(this, player))
		{
			// Delete player only
			player->MarkForDeletion();
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
	float zDisplace = newPosition.z - this->speed;
	newPosition = glm::vec3(newPosition.x, newPosition.y, zDisplace);
	this->SetPosition(newPosition);

	// Run parent's update
	GameObject::Update();
}

// Helpers ================================================

// Initialization after construction
void EnemyObject::init()
{

	// Set other properties
	this->eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
	this->radius = 0.5f;
	this->colorTint = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);	// Red

	// Set speed
	this->speed = 0.2f;
}