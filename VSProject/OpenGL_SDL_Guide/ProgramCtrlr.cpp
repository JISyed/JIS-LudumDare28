#include "ProgramCtrlr.h"

#include "GraphicsCtrlr.h"
#include "GameObjectCtrlr.h"
#include "GameLogicCtrlr.h"
#include "TimeCtrlr.h"
#include "RandomCtrlr.h"

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

		// Shoot bullet (only if player exists)
		if (this->windowEvent.type == SDL_KEYDOWN && 
			this->windowEvent.key.keysym.sym == SDLK_SPACE)
		{
			if(this->gameLogicCtrlr->GetPlayerInstance() != NULL)
			{
				this->gameLogicCtrlr->MakePlayerShootBullet();
			}
		}

		// Move left
		if (this->windowEvent.type == SDL_KEYDOWN && 
			this->windowEvent.key.keysym.sym == SDLK_LEFT)
		{
			if(this->gameLogicCtrlr->GetPlayerInstance() != NULL)
			{
				this->gameLogicCtrlr->MakePlayerMoveLeft();
			}
		}

		// Move right
		if (this->windowEvent.type == SDL_KEYDOWN && 
			this->windowEvent.key.keysym.sym == SDLK_RIGHT)
		{
			if(this->gameLogicCtrlr->GetPlayerInstance() != NULL)
			{
				this->gameLogicCtrlr->MakePlayerMoveRight();
			}
		}
	}

	// Update time
	this->timeCtrlr->LoopTime();

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

	// Re-init game ------------

	// Initialize anything GameObject Manager needs
	this->gameObjectCtrlr->InitializeGameObjects();

	// Initialize everything for the actual game
	this->gameLogicCtrlr->InitializeGame();

	// Reset flag
	ProgramCtrlr::shouldReset = false;
}