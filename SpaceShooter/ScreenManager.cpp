#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new ScreenManager();

	return sInstance;
}

void ScreenManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager()
{
	mInput = InputManager::Instance();

	mStars = new Stars();
	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
	mInstructionScreen = new InstructionScreen();
	mShipSelection = new ShipSelection();
	mStatScreen = new StatScreen();

	mCurrentScreen = start;
}

ScreenManager::~ScreenManager()
{
	mInput = nullptr;

	delete mStars;
	mStars = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;

	delete mInstructionScreen;
	mInstructionScreen = nullptr;

	delete mShipSelection;
	mShipSelection = nullptr;
}

void ScreenManager::Update()
{
	mStars->Update();

	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN))
		{
			if (mStartScreen->SelectedOption() == 0)
			{
				mCurrentScreen = selection;
			}
			else if (mStartScreen->SelectedOption() == 1)
			{
				mCurrentScreen = instruction;
			}
		}
		break;
	case selection:
		mShipSelection->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN))
		{
			mCurrentScreen = play;
			mPlayScreen->StartNewGame(mShipSelection->SelectedOption());
			mStars->Start();
		}

		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
			mCurrentScreen = start;
		break;
	case play:
		mPlayScreen->Update();

		if (mPlayScreen->GameOver())
		{
			mStatScreen->Initialize(mPlayScreen->GetPlayer());
			mCurrentScreen = stats;
			mStars->Pause();
		}
		break;
	case instruction:
		mInstructionScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
			mCurrentScreen = start;
		break;
	case stats:
		mStatScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN))
		{
			mStartScreen->Score(mPlayScreen->GetPlayer().Score());
			mCurrentScreen = start;
		}
		break;
	}
}

void ScreenManager::Render()
{
	mStars->Render();

	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Render();
		break;
	case selection:
		mShipSelection->Render();
		break;
	case play:
		mPlayScreen->Render();
		break;
	case instruction:
		mInstructionScreen->Render();
		break;
	case stats:
		mStatScreen->Render();
		break;
	}
}