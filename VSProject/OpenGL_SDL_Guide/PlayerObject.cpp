#include "PlayerObject.h"

#include "GameLogicCtrlr.h"
#include "BulletObject.h"
#include "GameObjectCtrlr.h"
#include "TimeCtrlr.h"

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
	// Delta time
	float dt = TimeCtrlr::GetInstance()->GetDeltaTime();

	// Auto decelerate
	if(this->speed > 0.1f)
	{
		this->speed -= this->deccel * dt;
	}
	else if(this->speed < -0.1f)
	{
		this->speed += this->deccel * dt;
	}
	else
	{
		this->speed = 0.0f;
	}

	// Move player
	glm::vec3 newPosition = this->position;
	float yDisplace = newPosition.y + (this->speed * dt);
	newPosition = glm::vec3(newPosition.x, yDisplace, newPosition.z);
	this->SetPosition(newPosition);

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
		if(this->speed > (-1 * this->speedMax))
		{
			float dt = TimeCtrlr::GetInstance()->GetDeltaTime();
			this->speed -= this->accel * dt;
		}
	}
	else
	{
		this->speed = 0;
	}
}

// Move right
void PlayerObject::MoveRight()
{
	// Move along positve Y
	if(this->position.y < EDGE_BORDER)
	{
		if(this->speed < this->speedMax)
		{
			float dt = TimeCtrlr::GetInstance()->GetDeltaTime();
			this->speed += this->accel * dt;
		}
	}
	else
	{
		this->speed = 0;
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
	this->radius = 0.45f;
	this->colorTint = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	// Green

	// Set speed
	this->speed = 0.0f;
	this->accel = 70.0f;
	this->deccel = 35.0f;
	this->speedMax = 15.0f;
}