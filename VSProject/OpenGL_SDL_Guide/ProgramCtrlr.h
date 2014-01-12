// Program Controller (ProgramCtrlr)
// Handles application level tasks with SDL
//
// Written by Jibran Syed

#ifndef PROGRAM_CTRLR
#define PROGRAM_CTRLR

#if defined(_MSC_VER)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
//#include <SDL_ttf.h>

class GraphicsCtrlr;
class GameObjectCtrlr;
class GameLogicCtrlr;
class TimeCtrlr;
class RandomCtrlr;
class DifficultyCtrlr;

// Data struct to hold key holding states
struct KeysHeld
{
	bool Space;
	bool Left;
	bool Right;
};

// Program Controller Class
class ProgramCtrlr
{
public:
	// Singleton =================

	static ProgramCtrlr* GetInstance();	// Singleton Instance Getter

	// Program Structure =========

	void InitializeProgram();			// Setup the program components
	void LoopProgram(bool& shouldQuit);	// Run the program every frame
	void FinalizeProgram();				// Deallocate everything in the program

	// Routines ===================

	static void MarkProgramForReset();	// Marks the program for resetting

private:
	// Data ======================

	GraphicsCtrlr* graphicsCtrlr;		// STATIC instance of graphics wrapper
	GameObjectCtrlr* gameObjectCtrlr;	// STATIC instance of GameObject manager
	GameLogicCtrlr* gameLogicCtrlr;		// STATIC instance of game's logic
	TimeCtrlr* timeCtrlr;				// STATIC instance to time functionality
	RandomCtrlr* randomCtrlr;			// STATIC instance to the random generator
	DifficultyCtrlr* difficultyCtrlr;	// STATIC instance to difficulty scaler
	SDL_Window* theWindow;				// Game window handled by SDL
	SDL_GLContext theGLContext;			// OpenGL graphics context
	SDL_Event windowEvent;				// Program event handled by SDL per frame

	KeysHeld keysHeld;					// Tells which keys are held down

	static bool shouldReset;			// Flag if program should reset

	//SDL_Surface* textSurface;			// Surface to render text upon
	//TTF_Font* textFont;					// Font to use text with
	//SDL_Color textColor;				// Color to use text with

	// Helpers ===================

	void ResetProgram();					// Actually resets the program
	static ProgramCtrlr* privGetInstance();	// Private Instance Getter
	ProgramCtrlr();							// Ctor
	//void SetupFontRendering(const char* fontFilePath);// Setup font rendering
	//void DrawFont();						// Draw the font (display score)

};

#endif