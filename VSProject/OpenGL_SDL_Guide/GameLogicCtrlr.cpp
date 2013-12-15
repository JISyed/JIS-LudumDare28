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

// Routines ===============================================

// Get the squared distance between two objects
float GameLogicCtrlr::GetSquaredDistance(GameObject* obj1, GameObject* obj2)
{
	// Get difference is positions for each dimension
	float deltaX = obj1->GetPosition().x - obj2->GetPosition().x;
	float deltaY = obj1->GetPosition().y - obj2->GetPosition().y;
	float deltaZ = obj1->GetPosition().z - obj2->GetPosition().z;

	// Distance formula without the square root
	float squareDistance = deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ;

	return squareDistance;
}

// Check of two GameObjects overlap
bool GameLogicCtrlr::DoObjectsOverlap(GameObject* obj1, GameObject* obj2)
{
	float bothRadii = obj1->GetRadius() + obj2->GetRadius();
	float squaredDistance = GameLogicCtrlr::GetSquaredDistance(obj1, obj2);

	// Compare distance^2 with bothRadii^2
	return squaredDistance < (bothRadii*bothRadii);
}