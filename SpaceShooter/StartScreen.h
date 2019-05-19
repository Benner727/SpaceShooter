#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "Scoreboard.h"
#include "Timer.h"
#include "InputManager.h"

class StartScreen : public GameEntity
{
public:
	StartScreen();
	~StartScreen();

private:
	Timer* mTimer;
	InputManager* mInputManager;

	GameEntity* mTopBar;
	Texture* mScore;
	Texture* mHiScore;
	Scoreboard* mPrevScore;
	Scoreboard* mTopScore;
	int mLastScore;
	int mHighScore;

	Texture* mLogo;

	GameEntity* mMenuOptions;
	Texture* mStartGame;
	Texture* mInstructions;
	Texture* mCursor;
	
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;
	
	int mSelectedOption;
	float mBlinkTimer;
	float mBlinkInterval;
	bool mSelectedOptionVisible;

	GameEntity* mBottomBar;
	Texture* mCreator;
	Texture* mAssets;
	Texture* mPatch;

public:
	int SelectedOption();

	void ChangeSelectedOption(int change);
	void Score(int score);

	void Update();
	void Render();
};

#endif