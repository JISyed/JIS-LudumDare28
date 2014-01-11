#ifndef ENEMY_OBJECT
#define ENEMY_OBJECT

#include "GameObject.h"

class EnemyObject : public GameObject
{
public:
	// Ctors/Dtor ====================

	EnemyObject();							// Default constructor
	EnemyObject(glm::vec3 initialPos);		// Position constructor
	

	// Routines ======================

	virtual void Update();					// Override GameObject's Update()

private:
	// Data ==========================

	float speed;							// Speed of enemy
	float accel;							// Acceleration
	bool alreadyPassedByPlayer;				// Did the enemy already pass by the player?

	// Helpers =======================

	void init();							// Initialization after construction

protected:
	// Inherited Routines ============

	virtual ~EnemyObject();					// Destructor
	
};



#endif