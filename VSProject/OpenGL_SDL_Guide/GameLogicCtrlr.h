#ifndef GAME_LOGIC_CTRLR
#define GAME_LOGIC_CTRLR

#define ENEMY_SPAWN_HEIGHT 27.0f
#define EDGE_BORDER 15.0f
#define VISIBLE_TOP 30.0f
#define VISIBLE_BOTTOM (-7.0f)

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

	// Make Player shoot Bullet
	void MakePlayerShootBullet();

	// Make Player move left
	void MakePlayerMoveLeft();

	// Make Player move right
	void MakePlayerMoveRight();

	// Increase the score by one
	void IncrementScore();

	// Properties ===========================

	void SetBulletInstance(GameObject* newBullet);
	void SetPlayerInstance(PlayerObject* newPlayer);
	void DeclareGameOver();

	GameObject* GetBulletInstance();
	PlayerObject* GetPlayerInstance();
	bool IsGameOver();

private:
	// Singleton Management =================

	static GameLogicCtrlr* privGetInstance();	// Private singleton handler
	GameLogicCtrlr();							// Private constructor

	// Data =================================
	
	GameObject* bulletInstance;					// The current bullet instance
	PlayerObject* playerInstance;				// The current player instance
	bool gameOver;								// Is it Game Over yet?
	bool launchedEnemies;						// Did the enemies launch?
	float launchTimeStamp;						// Timestamp for launching enemies (in seconds)
	float launchTimeInterval;					// Interval to launch enemies (in seconds)
	int score;									// How many enemies passed by the player

};

#endif