#include "BulletObject.h"

#include "GameLogicCtrlr.h"
#include "TimeCtrlr.h"

// Ctor / Dtor ===========================================

// Constructor
BulletObject::BulletObject()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	
	// Initialize other properties
	this->init();

	// Update patent class's data
	this->updateMatrices();
}

// Position constructor
BulletObject::BulletObject(glm::vec3 initialPos)
{
	this->position = initialPos;
	
	// Initialize other properties
	this->init();

	// Update patent class's data
	this->updateMatrices();
}

// Destructor
BulletObject::~BulletObject()
{
	// Clear reference to bullet in GameLogicCtrlr
	GameLogicCtrlr::GetInstance()->SetBulletInstance(NULL);
}

// Routines ===============================================

void BulletObject::Update()
{
	// Delete bullet if to far up
	if(this->position.z > VISIBLE_TOP)
	{
		this->MarkForDeletion();
		return;
	}

	// Move along positive Z
	glm::vec3 newPosition = this->position;
	float dt = TimeCtrlr::GetInstance()->GetDeltaTime();
	this->speed = this->speed + (this->accel * dt);
	float zDisplace = newPosition.z + (this->speed * dt);
	newPosition = glm::vec3(newPosition.x, newPosition.y, zDisplace);
	this->SetPosition(newPosition);

	// Run parent's update
	GameObject::Update();
}

// Helpers ================================================

// Initialization after construction
void BulletObject::init()
{
	// Register to GameLogicCtrlr
	GameLogicCtrlr::GetInstance()->SetBulletInstance(this);

	// Set other peroperties
	this->eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(0.4f, 0.4f, 0.5f);
	this->radius = 0.3f;
	this->colorTint = glm::vec4(0.0f, 0.3f, 1.0f, 1.0f);	// Blue

	// Set bullet speed
	this->speed = 5.0f;
	this->accel = 70.0f;
}