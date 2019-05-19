#ifndef INSTRUCTIONSCREEN_H
#define INSTRUCTIONSCREEN_H

#include "Texture.h"
#include "Timer.h"

class InstructionScreen : public GameEntity
{
public:
	InstructionScreen();
	~InstructionScreen();

private:
	Timer* mTimer;

	Texture* mInstructions;

	GameEntity* mControlInfo;
	Texture* mControls;
	Texture* mMovement;
	Texture* mFiring;

	GameEntity* mObjectiveInfo;
	Texture* mObjective;
	Texture* mHugePoints;
	Texture* mBigPoints;
	Texture* mMedPoints;
	Texture* mSmallPoints;
	Texture* mTinyPoints;
	Texture* mGoal;

	Texture* mEscape;
	float mBlinkTimer;
	float mBlinkInterval;
	bool mEscapeVisible;

public:
	void Update();
	void Render();
};

#endif