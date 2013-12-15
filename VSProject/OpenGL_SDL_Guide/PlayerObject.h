#ifndef PLAYER_OBJECT
#define PLAYER_OBJECT

#include "GameObject.h"

class PlayerObject : public GameObject
{
public:
	// Ctors =========================

	PlayerObject();							// Default constructor
	PlayerObject(glm::vec3 initialPos);		// Position constructor

	// Routines ======================

	virtual void Update();					// Override GameObject's Update()

private:
	// Helpers =======================

	void init();							// Initialization after construction

protected:
	// Dtor ==========================

	virtual ~PlayerObject();
};



#endif
