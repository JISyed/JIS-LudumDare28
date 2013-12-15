#include "PlayerObject.h"

#include "GameLogicCtrlr.h"

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

// Helpers ================================================

// Initialization after construction
void PlayerObject::init()
{
	// Register with GameLogicCtrlr
	GameLogicCtrlr::GetInstance()->SetPlayerInstance(this);

	// Set up other properties
	this->eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
	this->radius = 0.5f;
	this->colorTint = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	// Green
}