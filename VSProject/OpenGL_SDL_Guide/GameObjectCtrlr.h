// GameObject Controller (GraphicsCtrlr)
// Helps delegate GameObjects
//
// Written by Jibran Syed
// Stack-allocated singleton from Edward Keenan

#ifndef GAME_OBJECT_CTRLR
#define GAME_OBJECT_CTRLR

#include <forward_list>		// Requires C++11

class GameObject;

typedef std::forward_list<GameObject*> GameObjectList;

class GameObjectCtrlr
{
public:
	// Singleton Access =====================

	static GameObjectCtrlr* getInstance();		// Public singleton instance getter

	// Game Structures ================

	void InitializeGameObjects();				// Create objects before the main loop
	void LoopGameObjects();						// The main loop itself
	void ReleaseGameObjects();					// Delete objects after the main loop

private:
	// Singleton Management =================
	
	static GameObjectCtrlr* privGetInstance();	// Private singleton handler
	GameObjectCtrlr();							// Private constructor

	// Data =================================
	GameObjectList listOfGameObjects;			// List of all GameObjects


};





#endif