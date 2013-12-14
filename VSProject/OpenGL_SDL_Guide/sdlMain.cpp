#include "ProgramCtrlr.h"

int main(int argc, char *argv[])
{
	// Create the program controller
	ProgramCtrlr programController;

	// Initialize everything needed for the program
	programController.InitializeProgram();

	// Main loop
	bool shouldQuit = false;
	while (!shouldQuit)
	{
		programController.LoopProgram(shouldQuit);
	}

	// Delete everything the program made
	programController.FinalizeProgram();

	// Quit
    return 0;
}