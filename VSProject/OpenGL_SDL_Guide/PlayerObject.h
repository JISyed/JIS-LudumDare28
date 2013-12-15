#ifndef PLAYER_OBJECT
#define PLAYER_OBJECT

#include "GameObject.h"

class PlayerObject : public GameObject
{
public:
	// Ctors/Dtor ====================

	PlayerObject();							// Default constructor
	PlayerObject(glm::vec3 initialPos);		// Position constructor
	

	// Routines ======================

	virtual void Update();					// Override GameObject's Update()
	void ShootBullet();						// Fire BulletObject from current position

private:
	// Helpers =======================

	void init();							// Initialization after construction

protected:

	// Inherited Routines ============

	virtual ~PlayerObject();				// Destructor
	
};



#endif
