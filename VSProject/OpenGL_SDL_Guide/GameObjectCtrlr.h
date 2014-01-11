// GameObject Controller (GraphicsCtrlr)
// Helps delegate GameObjects
//
// Written by Jibran Syed
// Stack-allocated singleton from Edward Keenan

#ifndef GAME_OBJECT_CTRLR
#define GAME_OBJECT_CTRLR

#include <list>

class GameObject;

typedef std::list<GameObject*> GameObjectList;

class GameObjectCtrlr
{
public:
	// Singleton Access =====================

	static GameObjectCtrlr* GetInstance();		// Public singleton instance getter

	// Game Structures =====================

	void InitializeGameObjects();				// Create objects before the main loop
	void LoopGameObjects();						// The main loop itself
	void ReleaseGameObjects();					// Delete objects after the main loop

	// Routines =============================

	void UpdateAll();							// Updates all GameObjects
	void DrawAll();								// Draws all GameObjects
	void Add(GameObject* newGameObject);		// Adds a GameObject to list

private:
	// Singleton Management =================
	
	static GameObjectCtrlr* privGetInstance();	// Private singleton handler
	GameObjectCtrlr();							// Private constructor

	// Data =================================
	GameObjectList listOfGameObjects;			// List of all GameObjects

};

#endif