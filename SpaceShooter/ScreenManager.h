#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Stars.h"
#include "StartScreen.h"
#include "PlayScreen.h"
#include "InstructionScreen.h"
#include "ShipSelection.h"
#include "StatScreen.h"

class ScreenManager
{
private:
	enum SCREENS { start, play, instruction, selection, stats };

	static ScreenManager* sInstance;

	ScreenManager();
	~ScreenManager();

	InputManager* mInput;

	Stars* mStars;
	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;
	InstructionScreen* mInstructionScreen;
	ShipSelection* mShipSelection;
	StatScreen* mStatScreen;

	SCREENS mCurrentScreen;
public:
	static ScreenManager* Instance();

	static void Release();

	void Update();
	void Render();
};

#endif