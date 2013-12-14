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
	void SetTextureUnit(unsigned int newTextureUnit);

	glm::vec3 GetPosition();
	unsigned int GetTextureUnit();

private:

	// Data ========================
	glm::vec3 position;					// Position in world space
	unsigned int textureUnit;			// Assigns a texture unit to an object
};



#endif