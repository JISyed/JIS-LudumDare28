#include "EnemyObject.h"

#include "GameLogicCtrlr.h"

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

	// Run parent's update
	GameObject::Update();
}

// Helpers ================================================

// Initialization after construction
void EnemyObject::init()
{
	this->eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
	this->radius = 0.5f;
	this->colorTint = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);	// Red
}