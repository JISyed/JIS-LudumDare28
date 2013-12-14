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
	GameObject();
	virtual ~GameObject();

	// Routines ====================
	virtual void Update();				// Update the object state
	virtual void Draw();				// Draw the object
private:

	// Data ========================
	glm::vec3 position;					// Position in world space
	unsigned int textureUnit;			// Assigns a texture unit to an object
};



#endif