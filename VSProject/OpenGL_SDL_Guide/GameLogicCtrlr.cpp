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
	for(int i = 1; i < 6; i++)
	{
		GameObject* obj = new GameObject();

		obj->SetPosition((float) -i, (float) i, 0);
		obj->SetEulerAngles(i*10.0f, i*10.0f, i*10.0f);
		obj->SetScale(i/5.0f, i/5.0f, i/5.0f);
		obj->SetTextureUnit(0);
		obj->SetColorTint(0.2f*i, 1.0f, 0.2f*i, 1.0f);

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