#include "ProgramCtrlr.h"

#include "GraphicsCtrlr.h"
#include "GameObjectCtrlr.h"
#include "GameLogicCtrlr.h"
#include "TimeCtrlr.h"
#include "RandomCtrlr.h"
#include "DifficultyCtrlr.h"

#include <iostream>

// Static data ==============================================

bool ProgramCtrlr::shouldReset = false;

// Ctor/Dtor ================================================

// Ctor
ProgramCtrlr::ProgramCtrlr()
{

}

// Singleton =================================================

// Singleton Instance Getter
ProgramCtrlr* ProgramCtrlr::GetInstance()
{
	return ProgramCtrlr::privGetInstance();
}

// Private Instance Getter
ProgramCtrlr* ProgramCtrlr::privGetInstance()
{
	// Static object only initalizes once
	static ProgramCtrlr instance;
	return &instance;
}

// Structure =================================================

// Setup the program components
void ProgramCtrlr::InitializeProgram()
{
	// Start SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	int width = 800;
	int height = 600;

	// Make a window
	this->theWindow = SDL_CreateWindow("BlockDodger", 100, 100, width, height, SDL_WINDOW_OPENGL);

	// Make a graphics canvas (OpenGL context)
	this->theGLContext = SDL_GL_CreateContext(this->theWindow);

	// Make a OpenGL graphics manager
	this->graphicsCtrlr = GraphicsCtrlr::GetInstance();
	this->graphicsCtrlr->SetWindowSize(width, height);

	// Initilaize everything for graphics
	this->graphicsCtrlr->InitializeGraphics();

	// Make GameObject Manager
	this->gameObjectCtrlr = GameObjectCtrlr::GetInstance();

	// Initialize anything GameObject Manager needs
	this->gameObjectCtrlr->InitializeGameObjects();

	// Create the Game Logic handler
	this->gameLogicCtrlr = GameLogicCtrlr::GetInstance();

	// Initialize everything for the actual game
	this->gameLogicCtrlr->InitializeGame();
	ProgramCtrlr::shouldReset = false;

	// Initialize TimeCtrlr for time functionality
	this->timeCtrlr = TimeCtrlr::GetInstance();
	timeCtrlr->InitializeTime();

	// Initialize RandomCtrlr for random generation
	this->randomCtrlr = RandomCtrlr::GetInstance();
	this->randomCtrlr->InitializeRand();

	// Initialize DifficultyCtrlr to scale difficulty over time
	this->difficultyCtrlr = DifficultyCtrlr::GetInstance();
	this->difficultyCtrlr->InitializeDifficulty();

	// Initialized struct of key holding states (keyboard)
	this->keysHeld.Left = false;
	this->keysHeld.Right = false;
	this->keysHeld.Space = false;
}

// Run the program every frame
void ProgramCtrlr::LoopProgram(bool& shouldQuit)
{
	// Poll for window events
	if (SDL_PollEvent(&(this->windowEvent)))
	{
		// Leave main loop when X on window corner is pressed
		if (this->windowEvent.type == SDL_QUIT)
		{
			shouldQuit = true;
			return;
		}

		// Leave main loop if escape key was released
		if (this->windowEvent.type == SDL_KEYUP && 
			this->windowEvent.key.keysym.sym == SDLK_ESCAPE)
		{
			shouldQuit = true;
			return;
		}

		// Leave Game Over screen (only if game over)
		if (this->windowEvent.type == SDL_KEYUP && 
			this->windowEvent.key.keysym.sym == SDLK_RETURN)
		{
			if(this->gameLogicCtrlr->IsGameOver())
			{
				ProgramCtrlr::MarkProgramForReset();
			}
		}

		// Update player input key down events
		if(this->windowEvent.type == SDL_KEYDOWN)
		{
			switch(this->windowEvent.key.keysym.sym)
			{
				case SDLK_LEFT: this->keysHeld.Left = true; break;
				case SDLK_RIGHT: this->keysHeld.Right = true; break;
				case SDLK_SPACE: this->keysHeld.Space = true; break;
			}
		}

		// Uppdate player input key up events
		if(this->windowEvent.type == SDL_KEYUP)
		{
			switch(this->windowEvent.key.keysym.sym)
			{
				case SDLK_LEFT: this->keysHeld.Left = false; break;
				case SDLK_RIGHT: this->keysHeld.Right = false; break;
				case SDLK_SPACE: this->keysHeld.Space = false; break;
			}
		}
	}

	// Update input
	if(this->keysHeld.Left)
		this->gameLogicCtrlr->MakePlayerMoveLeft();
	if(this->keysHeld.Right) 
		this->gameLogicCtrlr->MakePlayerMoveRight();
	if(this->keysHeld.Space)
		this->gameLogicCtrlr->MakePlayerShootBullet();

	// Update time
	this->timeCtrlr->LoopTime();

	// Update difficulty scale
	this->difficultyCtrlr->LoopDifficulty();

	// Update randomizer
	this->randomCtrlr->LoopRand();

	// Update GameLogic
	this->gameLogicCtrlr->LoopGame();

	// Update GameObjects
	this->gameObjectCtrlr->LoopGameObjects();

	// The Graphics Loop
	graphicsCtrlr->LoopGraphics();

	// glSwapBuffers - swap between the front and back render buffer
	SDL_GL_SwapWindow(this->theWindow);

	// Check if program was flagged for reset
	if(ProgramCtrlr::shouldReset == true)
	{
		this->ResetProgram();
	}
}

// Deallocate everything in the program
void ProgramCtrlr::FinalizeProgram()
{
	// Destroy game logic
	this->gameLogicCtrlr->ReleaseGame();

	// Destroy all the GameObjects
	this->gameObjectCtrlr->ReleaseGameObjects();

	// Delete everything for graphics
	this->graphicsCtrlr->ReleaseGraphics();

	// Release things for randomization
	this->randomCtrlr->FinalizeRand();

	// Release things for difficulty scaling
	this->difficultyCtrlr->FinalizeDifficulty();

	// Release things for time functionality
	this->timeCtrlr->FinalizeTime();

	// Delete graphics canvas (OpenGL context)
	SDL_GL_DeleteContext(this->theGLContext);

	// Free SDL
	SDL_Quit();

	ProgramCtrlr::shouldReset = false;
}

// Routines ===================================================

// Marks the program for resetting
void ProgramCtrlr::MarkProgramForReset()
{
	ProgramCtrlr::shouldReset = true;
}

// Helpers ====================================================

// Actually resets the program
void ProgramCtrlr::ResetProgram()
{
	// Release game ------------
	
	// Destroy game logic
	this->gameLogicCtrlr->ReleaseGame();

	// Destroy all the GameObjects
	this->gameObjectCtrlr->ReleaseGameObjects();

	// Reset difficulty
	this->difficultyCtrlr->FinalizeDifficulty();

	// Reset time data
	this->timeCtrlr->FinalizeTime();

	// Re-init game ------------

	// Initialize anything GameObject Manager needs
	this->gameObjectCtrlr->InitializeGameObjects();

	// Initialize everything for the actual game
	this->gameLogicCtrlr->InitializeGame();

	// Initialize time data
	this->timeCtrlr->InitializeTime();
	
	// Initialize difficulty scaling
	this->difficultyCtrlr->InitializeDifficulty();

	// Reset flag
	ProgramCtrlr::shouldReset = false;
}