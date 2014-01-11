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
	void MoveLeft();						// Move left
	void MoveRight();						// Move right

private:
	// Data ==========================

	float speed;							// Speed of player
	float accel;							// Acceleration
	float deccel;							// Deceleration
	float speedMax;							// Maximum speed

	// Helpers =======================

	void init();							// Initialization after construction

protected:

	// Inherited Routines ============

	virtual ~PlayerObject();				// Destructor
	
};



#endif
