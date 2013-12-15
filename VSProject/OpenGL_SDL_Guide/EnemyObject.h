#ifndef ENEMY_OBJECT
#define ENEMY_OBJECT

#include "GameObject.h"

class EnemyObject : public GameObject
{
public:
	// Ctors =========================

	EnemyObject();							// Default constructor
	EnemyObject(glm::vec3 initialPos);		// Position constructor

	// Routines ======================

	virtual void Update();					// Override GameObject's Update()

private:
	// Helpers =======================

	void init();							// Initialization after construction

protected:
	// Dtor ==========================

	virtual ~EnemyObject();
};



#endif