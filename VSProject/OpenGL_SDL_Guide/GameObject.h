// GameObject
// Entity in the game
//
// Written by Jibran Syed

#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <glm/glm.hpp>

class GameObject
{
public:
	// Ctor/Dtor ===================
	
	GameObject();						// Constuctor
	virtual ~GameObject();				// Virtual Destructor

	// Routines ====================
	
	virtual void Update();				// Update the object state
	virtual void Draw();				// Draw the object

	// Properties ==================

	void SetPosition(glm::vec3 newPosition);
	void SetPosition(float newX, float newY, float newZ);
	void SetScale(glm::vec3 newScale);
	void SetScale(float newX, float newY, float newZ);
	void SetEulerAngles(glm::vec3 newEulerAngles);
	void SetEulerAngles(float xRotation, float yRotation, float zRotation);
	void SetTextureUnit(unsigned int newTextureUnit);

	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::vec3 GetEulerAngles();
	unsigned int GetTextureUnit();

private:

	// Data ========================
	glm::vec3 position;					// Position in world space
	glm::vec3 scale;					// Mesh scale in 3 dimensions
	glm::vec3 eulerAngles;				// Angle rotations in 3 dimentions
	unsigned int textureUnit;			// Assigns a texture unit to an object

	// Matrices ====================
	glm::mat4 rotationMatrix;
	glm::mat4 translateMatrix;
	glm::mat4 scaleMatrix;

	// Helpers =====================

	void updateMatrices();				// Update all tranformation matrices
	glm::mat4 constructModelMatrix();	// Make the model matrix to send to shaders
};



#endif