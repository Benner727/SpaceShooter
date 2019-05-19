#ifndef SHIPSELECTION_H
#define SHIPSELECTION_H

#include "Texture.h"
#include "Timer.h"
#include "InputManager.h"

class ShipSelection : public GameEntity
{
public:
	ShipSelection();
	~ShipSelection();

private:
	Timer* mTimer;
	InputManager* mInputManager;

	GameEntity* mShipOptions;
	Texture* mTitle;
	Texture* mWaspIcon;
	Texture* mWaspText;
	Texture* mRaiderIcon;
	Texture* mRaiderText;
	Texture* mFighterIcon;
	Texture* mFighterText;
	Texture* mCursor;

	Vector2 mCursorLeftPos;
	Vector2 mCursorOffset;

	int mSelectedOption;

	Texture* mEscape;
	float mEscapeBlinkTimer;
	float mEscapeBlinkInterval;
	bool mEscapeVisible;

public:
	int SelectedOption();

	void ChangeSelectedOption(int change);

	void Update();
	void Render();
};

#endif