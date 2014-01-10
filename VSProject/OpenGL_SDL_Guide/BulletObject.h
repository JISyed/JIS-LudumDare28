#ifndef BULLET_OBJECT
#define BULLET_OBJECT

#include "GameObject.h"

class BulletObject : public GameObject
{
public:
	// Ctors/Dtor ====================

	BulletObject();							// Default constructor
	BulletObject(glm::vec3 initialPos);		// Position constructor
	
	
	// Routines ======================

	virtual void Update();					// Override GameObject's Update()

private:
	// Data ==========================

	float speed;							// Speed of bullet
	float accel;							// Acceleration

	// Helpers =======================

	void init();							// Initialization after construction

protected:
	// Inherited Routines ============

	virtual ~BulletObject();				// Destructor
	
};



#endif