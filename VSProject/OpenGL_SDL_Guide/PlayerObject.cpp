#include "PlayerObject.h"

#include "GameLogicCtrlr.h"
#include "BulletObject.h"
#include "GameObjectCtrlr.h"

// Ctor / Dtor ===========================================

// Constructor
PlayerObject::PlayerObject()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	
	// Initialize other properties
	this->init();

	// Update patent class's data
	this->updateMatrices();
}

// Position constructor
PlayerObject::PlayerObject(glm::vec3 initialPos)
{
	this->position = initialPos;
	
	// Initialize other properties
	this->init();

	// Update patent class's data
	this->updateMatrices();
}

// Destructor
PlayerObject::~PlayerObject()
{
	// Clear reference with GameLogicCtrlr
	GameLogicCtrlr::GetInstance()->SetPlayerInstance(NULL);

	// Declare Game Over
	GameLogicCtrlr::GetInstance()->DeclareGameOver();
}

// Routines ===============================================

void PlayerObject::Update()
{


	// Run parent's update
	GameObject::Update();
}

// Fire BulletObject from current position
void PlayerObject::ShootBullet()
{
	// Only shoot if there's no Bullet on the screen
	if(GameLogicCtrlr::GetInstance()->GetBulletInstance() == NULL)
	{
		BulletObject* newBullet = new BulletObject(this->position);
		GameObjectCtrlr::GetInstance()->Add(newBullet);
	}
}

// Move left
void PlayerObject::MoveLeft()
{
	// Move along negative Y
	if(this->position.y > -EDGE_BORDER)
	{
		glm::vec3 newPosition = this->position;
		float yDisplace = newPosition.y - this->speed;
		newPosition = glm::vec3(newPosition.x, yDisplace, newPosition.z);
		this->SetPosition(newPosition);
	}
}

// Move right
void PlayerObject::MoveRight()
{
	// Move along positve Y
	if(this->position.y < EDGE_BORDER)
	{
		glm::vec3 newPosition = this->position;
		float yDisplace = newPosition.y + this->speed;
		newPosition = glm::vec3(newPosition.x, yDisplace, newPosition.z);
		this->SetPosition(newPosition);
	}
}

// Helpers ================================================

// Initialization after construction
void PlayerObject::init()
{
	// Register with GameLogicCtrlr
	GameLogicCtrlr::GetInstance()->SetPlayerInstance(this);

	// Set up other properties
	this->eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(0.8f, 0.8f, 1.0f);
	this->radius = 0.5f;
	this->colorTint = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	// Green

	// Set speed
	this->speed = 0.4f;
}