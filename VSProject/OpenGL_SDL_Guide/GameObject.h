// GameObject
// Entity in the game
//
// Written by Jibran Syed

#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <glm/glm.hpp>

class GameObjectCtrlr;

class GameObject
{
public:
	// Ctor/Dtor ===================
	
	GameObject();						// Constuctor

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
	void SetColorTint(glm::vec4 newColor);
	void SetColorTint(float red, float green, float blue, float alpha);
	void SetTextureUnit(unsigned int newTextureUnit);
	void MarkForDeletion();
	void SetNumOfVertices(int newNumOfVerts);

	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::vec3 GetEulerAngles();
	glm::vec4 GetColorTint();
	unsigned int GetTextureUnit();
	bool IsMarkedForDeletion();
	int GetNumOfVertices();
	float GetRadius();

private:

	// Data ========================

	glm::vec3 position;					// Position in world space
	glm::vec3 scale;					// Mesh scale in 3 dimensions
	glm::vec3 eulerAngles;				// Angle rotations in 3 dimentions
	glm::vec4 colorTint;				// The color independent of textures
	unsigned int textureUnit;			// Assigns a texture unit to an object
	bool markedForDeletion;				// Will the object get deleted?
	int numOfVertices;					// The number of vertices to draw
	float radius;						// Half the length of the cube

	// Matrices ====================

	glm::mat4 rotationMatrix;			// Matrix that stores rotation
	glm::mat4 translateMatrix;			// Matrix that stores position
	glm::mat4 scaleMatrix;				// Matrix that stores size scale

	// Helpers =====================

	void updateMatrices();				// Update all tranformation matrices
	glm::mat4 constructModelMatrix();	// Make the model matrix to send to shaders

protected:

	// Protected members ===========

	friend class GameObjectCtrlr;		// GameObjectCtrlr can access Destructor
	virtual ~GameObject();				// Virtual Destructor
};



#endif