#include "GameObject.h"

#include "GameObjectCtrlr.h"
#include "GraphicsCtrlr.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

// Ctor/Dtor ========================================

// Constructor
GameObject::GameObject()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
	this->colorTint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);	// Default to white
	this->textureUnit = 0;
	this->rotationMatrix = glm::mat4(1.0f);
	this->translateMatrix = glm::translate(this->position);
	this->scaleMatrix = glm::mat4(1.0f);
	this->markedForDeletion = false;
	this->numOfVertices = 36;			// Default verts in a cube
	this->radius = 0.5f;
}

// Destructor (protected virtual)
GameObject::~GameObject()
{
	
	 
}

// Routines =========================================

// Update the object state
void GameObject::Update()
{

	// Update internal matrix data
	this->updateMatrices();
}

// Draw the object
void GameObject::Draw()
{
	// Send transformations to shaders
	glm::mat4 modelMatrix = this->constructModelMatrix();
	GraphicsCtrlr::GetInstance()->SetUniform(modelMatrix, "model");

	// Send uniform color to shaders
	GraphicsCtrlr::GetInstance()->SetUniform(this->colorTint, "colorTint");

	// Send texture unit to shader
	GraphicsCtrlr::GetInstance()->SetUniform((int) this->textureUnit, "texUnit");

	// Draw object
	GraphicsCtrlr::GetInstance()->DrawTriangles(this->numOfVertices);
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

void GameObject::SetScale(glm::vec3 newScale)
{
	this->scale = newScale;

	float average = (newScale.x + newScale.y + newScale.z) / 3.0f;
	this->radius = average;
}

void GameObject::SetScale(float newX, float newY, float newZ)
{
	this->scale = glm::vec3(newX, newY, newZ);

	float average = (newX + newY + newZ) / 3.0f;
	this->radius = average;
}

void GameObject::SetEulerAngles(glm::vec3 newEulerAngles)
{
	this->eulerAngles = newEulerAngles;
}

void GameObject::SetEulerAngles(float xRotation, float yRotation, float zRotation)
{
	this->eulerAngles = glm::vec3(xRotation, yRotation, zRotation);
}

void GameObject::SetColorTint(glm::vec4 newColor)
{
	this->colorTint = newColor;
}

void GameObject::SetColorTint(float red, float green, float blue, float alpha)
{
	this->colorTint = glm::vec4(red, green, blue, alpha);
}

void GameObject::SetTextureUnit(unsigned int newTextureUnit)
{
	this->textureUnit = newTextureUnit;
}

void GameObject::MarkForDeletion()
{
	this->markedForDeletion = true;
}

void GameObject::SetNumOfVertices(int newNumOfVerts)
{
	this->numOfVertices = newNumOfVerts;
}

glm::vec3 GameObject::GetPosition()
{
	return this->position;
}

glm::vec3 GameObject::GetScale()
{
	return this->scale;
}

glm::vec3 GameObject::GetEulerAngles()
{
	return this->eulerAngles;
}

glm::vec4 GameObject::GetColorTint()
{
	return this->colorTint;
}

unsigned int GameObject::GetTextureUnit()
{
	return this->textureUnit;
}

bool GameObject::IsMarkedForDeletion()
{
	return this->markedForDeletion;
}

int GameObject::GetNumOfVertices()
{
	return this->numOfVertices;
}

float GameObject::GetRadius()
{
	return this->radius;
}

//  Helpers ===========================================

void GameObject::updateMatrices()
{
	this->translateMatrix = glm::translate(this->position);
	this->scaleMatrix = glm::scale(this->scale);

	this->rotationMatrix = glm::rotate(eulerAngles.x, 1.0f, 0.0f, 0.0f);
	this->rotationMatrix = glm::rotate(this->rotationMatrix, eulerAngles.y, 0.0f, 1.0f, 0.0f);
	this->rotationMatrix = glm::rotate(this->rotationMatrix, eulerAngles.z, 0.0f, 0.0f, 1.0f);
}

glm::mat4 GameObject::constructModelMatrix()
{
	glm::mat4 modelMatrix;

	modelMatrix = this->translateMatrix * this->rotationMatrix * this->scaleMatrix;

	return modelMatrix;
}