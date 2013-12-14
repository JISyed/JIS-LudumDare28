#include "GameObject.h"

#include "GraphicsCtrlr.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

// Ctor/Dtor ========================================

// Constructor
GameObject::GameObject()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->textureUnit = 0;
}

// Destructor
GameObject::~GameObject()
{

}

// Routines =========================================

// Update the object state
void GameObject::Update()
{

}

// Draw the object
void GameObject::Draw()
{

}

// Properties ========================================

void GameObject::SetPosition(glm::vec3 newPosition)
{
	this->position = newPosition;
}

void GameObject::SetPosition(float newX, float newY, float newZ)
{
	this->position = glm::vec3(newX, newY, newZ);
}

void GameObject::SetTextureUnit(unsigned int newTextureUnit)
{
	this->textureUnit = newTextureUnit;
}

glm::vec3 GameObject::GetPosition()
{
	return this->position;
}

unsigned int GameObject::GetTextureUnit()
{
	return this->textureUnit;
}

