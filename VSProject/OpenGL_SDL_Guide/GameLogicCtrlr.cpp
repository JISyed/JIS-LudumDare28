#include "GameLogicCtrlr.h"
#include "GameObject.h"
#include "GameObjectCtrlr.h"

// Singleton ============================================

// Constructor
GameLogicCtrlr::GameLogicCtrlr()
{
	// Setup stuff here
}

// Public singleton instance getter
GameLogicCtrlr* GameLogicCtrlr::GetInstance()
{
	return GameLogicCtrlr::privGetInstance();
}

// Private singleton handler
GameLogicCtrlr* GameLogicCtrlr::privGetInstance()
{
	// Static object only initializes once
	static GameLogicCtrlr instance;
	return &instance;
}

// Game Structure ========================================

// Create objects before the main loop
void GameLogicCtrlr::InitializeGame()
{
	for(int i = 0; i < 5; i++)
	{
		GameObject* obj = new GameObject();

		obj->SetPosition(i, 0, 0);

		GameObjectCtrlr::GetInstance()->Add(obj);
	}
}

// The main loop itself
void GameLogicCtrlr::LoopGame()
{

}

// Delete objects after the main loop
void GameLogicCtrlr::ReleaseGame()
{

}