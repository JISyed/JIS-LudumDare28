#ifndef GAME_LOGIC_CTRLR
#define GAME_LOGIC_CTRLR

#define ENEMY_SPAWN_HEIGHT 25.0f
#define EDGE_BORDER 15.0f
#define VISIBLE_TOP 29.0f
#define VISIBLE_BOTTOM (-3.0f)

class GameObject;
class PlayerObject;

class GameLogicCtrlr
{
public:
	// Singleton Access =====================

	static GameLogicCtrlr* GetInstance();		// Public singleton instance getter

	// Game Structures =====================

	void InitializeGame();					// Create objects before the main loop
	void LoopGame();						// The main loop itself
	void ReleaseGame();						// Delete objects after the main loop

	// Routines =============================

	// Get the squared distance between two objects
	static float GetSquaredDistance(GameObject* obj1, GameObject* obj2);

	// Check if two GameObjects overlap
	static bool DoObjectsOverlap(GameObject* obj1, GameObject* obj2);

	// Generate random number between x and -x
	//static float GetRandomNumber(int x);

	// Make Player shoot Bullet
	void MakePlayerShootBullet();

	// Make Player move left
	void MakePlayerMoveLeft();

	// Make Player move right
	void MakePlayerMoveRight();

	// Properties ===========================

	void SetBulletInstance(GameObject* newBullet);
	void SetPlayerInstance(PlayerObject* newPlayer);
	void DeclareGameOver();

	GameObject* GetBulletInstance();
	PlayerObject* GetPlayerInstance();
	bool IsGameOver();
	//unsigned int GetRandomSeed();

private:
	// Singleton Management =================

	static GameLogicCtrlr* privGetInstance();	// Private singleton handler
	GameLogicCtrlr();							// Private constructor

	// Data =================================

	bool gameOver;								// Is it Game Over yet?
	GameObject* bulletInstance;					// The current bullet instance
	PlayerObject* playerInstance;				// The current player instance
	bool launchEnemies;							// Will enemies be launched;
	//unsigned int randomSeed;					// Seed for rand()
	long int launchTimeStamp;					// Timestamp for launching enemies
	int launchTimeInterval;						// Interval to launch enemies

	

};



#endif