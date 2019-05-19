#include "InstructionScreen.h"

InstructionScreen::InstructionScreen()
{
	mTimer = Timer::Instance();

	mInstructions = new Texture("INSTRUCTIONS", "kenvector_future.ttf", 64, { 178, 34, 34 });
	mInstructions->Parent(this);
	mInstructions->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT * 0.05f));

	mControlInfo = new GameEntity();
	mControlInfo->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT * 0.15f));
	mControlInfo->Parent(this);

	mControls = new Texture("CONTROLS", "kenvector_future.ttf", 48, { 34, 34, 178 });
	mMovement = new Texture("Use 'WASD' to move.", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mFiring = new Texture("Press 'SPACEBAR' to shoot.", "kenvector_future.ttf", 32, { 245, 245, 245 });

	mControls->Parent(mControlInfo);
	mMovement->Parent(mControlInfo);
	mFiring->Parent(mControlInfo);

	mControls->Pos(Vector2(VEC2_ZERO));
	mMovement->Pos(Vector2(0.0f, 50.0f));
	mFiring->Pos(Vector2(0.0f, 100.0f));

	mObjectiveInfo = new GameEntity();
	mObjectiveInfo->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT * 0.40f));
	mObjectiveInfo->Parent(this);

	mObjective = new Texture("OBJECTIVES", "kenvector_future.ttf", 48, { 34, 178, 34 });
	mHugePoints = new Texture("Huge Meteors: 10 Points", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mBigPoints = new Texture("Big Meteors: 25 Points", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mMedPoints = new Texture("Medium Meteors: 50 Points", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mSmallPoints = new Texture("Small Meteors: 75 Points", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mTinyPoints = new Texture("Tiny Meteors: 100 Points", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mGoal = new Texture("Improvise. Adapt. Overcome.", "kenvector_future.ttf", 36, { 255, 215, 0 });

	mObjective->Parent(mObjectiveInfo);
	mHugePoints->Parent(mObjectiveInfo);
	mBigPoints->Parent(mObjectiveInfo);
	mMedPoints->Parent(mObjectiveInfo);
	mSmallPoints->Parent(mObjectiveInfo);
	mTinyPoints->Parent(mObjectiveInfo);
	mGoal->Parent(mObjectiveInfo);

	mObjective->Pos(VEC2_ZERO);
	mHugePoints->Pos(Vector2(0.0f, 50.0f));
	mBigPoints->Pos(Vector2(0.0f, 100.0f));
	mMedPoints->Pos(Vector2(0.0f, 150.0f));
	mSmallPoints->Pos(Vector2(0.0f, 200.0f));
	mTinyPoints->Pos(Vector2(0.0f, 250.0f));
	mGoal->Pos(Vector2(0.0f, 350.0f));

	mEscape = new Texture("Press 'ESCAPE' to return to start screen.", "kenvector_future.ttf", 32, { 80, 80, 80 });
	mEscape->Parent(this);
	mEscape->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT * 0.95f));

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mEscapeVisible = true;
}

InstructionScreen::~InstructionScreen()
{
	mTimer = nullptr;

	delete mInstructions;
	mInstructions = nullptr;

	delete mControls;
	mControls = nullptr;

	delete mMovement;
	mMovement = nullptr;

	delete mFiring;
	mFiring = nullptr;

	delete mControlInfo;
	mControlInfo = nullptr;

	delete mObjective;
	mObjective = nullptr;

	delete mHugePoints;
	mHugePoints = nullptr;

	delete mBigPoints;
	mBigPoints = nullptr;

	delete mMedPoints;
	mMedPoints = nullptr;

	delete mSmallPoints;
	mSmallPoints = nullptr;

	delete mTinyPoints;
	mTinyPoints = nullptr;

	delete mGoal;
	mGoal = nullptr;

	delete mObjectiveInfo;
	mObjectiveInfo = nullptr;

	delete mEscape;
	mEscape = nullptr;
}

void InstructionScreen::Update()
{
	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval)
	{
		mEscapeVisible = !mEscapeVisible;
		mBlinkTimer = 0.0f;
	}
}

void InstructionScreen::Render()
{
	mInstructions->Render();

	mControls->Render();
	mMovement->Render();
	mFiring->Render();

	mObjective->Render();
	mHugePoints->Render();
	mBigPoints->Render();
	mMedPoints->Render();
	mSmallPoints->Render();
	mTinyPoints->Render();
	mGoal->Render();

	if (mEscapeVisible)
		mEscape->Render();
}