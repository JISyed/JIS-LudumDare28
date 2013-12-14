#include "GameObjectCtrlr.h"

#include "GameObject.h"

#include <iostream>

// Singleton ================================================

// Constructor
GameObjectCtrlr::GameObjectCtrlr()
{
	// Setup stuff here
}

// Public singleton instance getter
GameObjectCtrlr* GameObjectCtrlr::getInstance()
{
	std::cout << "Getting GameObjectCtrlr." << std::endl;
	return GameObjectCtrlr::privGetInstance();
}

// Private singleton handler
GameObjectCtrlr* GameObjectCtrlr::privGetInstance()
{
	// Static object only initializes once
	static GameObjectCtrlr instance;
	return &instance;
}

// Game Structure ==========================================

// Create objects before the main loop
void GameObjectCtrlr::InitializeGameObjects()
{

}

// The main loop itself
void GameObjectCtrlr::LoopGameObjects()
{

}

// Delete objects after the main loop
void GameObjectCtrlr::ReleaseGameObjects()
{

}