#include "GameObjectCtrlr.h"

#include "GameObject.h"

#include <iostream>

// Singleton ================================================

// Constructor
GameObjectCtrlr::GameObjectCtrlr()
{
	//this->listOfGameObjects = GameObjectList();
}

// Public singleton instance getter
GameObjectCtrlr* GameObjectCtrlr::GetInstance()
{
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
	this->UpdateAll();

	// Delete any GameObjects marked for deletion
	GameObjectList::const_iterator itr;
	for(itr = this->listOfGameObjects.begin(); 
		itr != this->listOfGameObjects.end();
		itr++)
	{
		bool shouldDelete = static_cast<GameObject*>(*itr)->IsMarkedForDeletion();
		if (shouldDelete)
		{
			// Delete GameObject
			itr = this->listOfGameObjects.erase(itr);
		}
	}
}

// Delete objects after the main loop
void GameObjectCtrlr::ReleaseGameObjects()
{
	// Delete all GameObjects
	GameObjectList::const_iterator itr;
	for(itr = this->listOfGameObjects.begin(); 
		itr != this->listOfGameObjects.end();
		itr++)
	{
		itr = this->listOfGameObjects.erase(itr);
	}
}

// Routines ================================================

// Updates all GameObjects
void GameObjectCtrlr::UpdateAll()
{
	GameObjectList::const_iterator itr;
	for(itr = this->listOfGameObjects.begin(); 
		itr != this->listOfGameObjects.end();
		itr++)
	{
		static_cast<GameObject*>(*itr)->Update();
	}
}

// Draws all GameObjects
void GameObjectCtrlr::DrawAll()
{
	GameObjectList::iterator itr;
	for(itr = this->listOfGameObjects.begin(); 
		itr != this->listOfGameObjects.end();
		itr++)
	{
		static_cast<GameObject*>(*itr)->Draw();
	}
}

// Adds a GameObject to list
void GameObjectCtrlr::Add(GameObject* newGameObject)
{
	this->listOfGameObjects.push_back(newGameObject);
}