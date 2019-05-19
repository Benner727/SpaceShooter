#include "StartScreen.h"

StartScreen::StartScreen()
{
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();

	mTopBar = new GameEntity(Vector2(Graphics::SCREEN_WIDTH * 0.5f, 75.0f));
	mScore = new Texture("Score", "kenvector_future.ttf", 36, { 185, 185, 185 });
	mHiScore = new Texture("HiScore", "kenvector_future.ttf", 36, { 185, 185, 185 });
	mPrevScore = new Scoreboard();
	mTopScore = new Scoreboard();

	mScore->Parent(mTopBar);
	mHiScore->Parent(mTopBar);
	mPrevScore->Parent(mTopBar);
	mTopScore->Parent(mTopBar);
	mTopBar->Parent(this);

	mScore->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.30, 0.0f));
	mHiScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.30, 0.0f));
	mPrevScore->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.305, 30.0f));
	mTopScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.29, 30.0f));

	mLastScore = 0;
	mHighScore = 0;

	mPrevScore->Score(mLastScore);
	mTopScore->Score(mHighScore);

	mLogo = new Texture("Space Shooter", "kenvector_future.ttf", 72, { 178, 34, 34 });
	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.33f));
	mLogo->Parent(this);

	mMenuOptions = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f));
	mStartGame = new Texture("Play Game", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mInstructions = new Texture("Instructions", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mCursor = new Texture("cursor.png");

	mStartGame->Parent(mMenuOptions);
	mInstructions->Parent(mMenuOptions);
	mCursor->Parent(mMenuOptions);
	mMenuOptions->Parent(this);

	mStartGame->Pos(Vector2(0.0f, -35.0f));
	mInstructions->Pos(Vector2(0.0f, 35.0f));
	mCursor->Pos(Vector2(-180.0f, -35.0f));

	mCursorStartPos = mCursor->Pos(local);
	mCursorOffset = Vector2(0.0f, 70.0f);
	mSelectedOption = 0;

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mSelectedOptionVisible = true;
	
	mBottomBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.95f));
	mCreator = new Texture("Created by Stephen Benner", "kenvector_future_thin.ttf", 32, { 96, 96, 96 });
	mAssets = new Texture("Assets by Kenney Vleugels", "kenvector_future_thin.ttf", 32, { 64, 64, 64 });
	mPatch = new Texture("Patch 1.0", "kenvector_future_thin.ttf", 16, { 32, 32, 32 });

	mCreator->Parent(mBottomBar);
	mAssets->Parent(mBottomBar);
	mPatch->Parent(mBottomBar);
	mBottomBar->Parent(this);

	mCreator->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.23, 0.0f));
	mAssets->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.23, 30.0f));
	mPatch->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.43, 35.0f));
}

StartScreen::~StartScreen()
{
	mTimer = nullptr;
	mInputManager = nullptr;

	delete mScore;
	mScore = nullptr;

	delete mHiScore;
	mHiScore = nullptr;

	delete mPrevScore;
	mPrevScore = nullptr;
	
	delete mTopScore;
	mTopScore = nullptr;

	delete mTopBar;
	mTopBar = nullptr;

	delete mLogo;
	mLogo = nullptr;

	delete mStartGame;
	mStartGame = nullptr;

	delete mInstructions;
	mInstructions = nullptr;

	delete mCursor;
	mCursor = nullptr;

	delete mMenuOptions;
	mMenuOptions = nullptr;

	delete mCreator;
	mCreator = nullptr;

	delete mAssets;
	mAssets = nullptr;

	delete mPatch;
	mPatch = nullptr;

	delete mBottomBar;
	mBottomBar = nullptr;
}

int StartScreen::SelectedOption()
{
	return mSelectedOption;
}

void StartScreen::ChangeSelectedOption(int change)
{
	mSelectedOption += change;

	if (mSelectedOption < 0)
		mSelectedOption = 1;
	else if (mSelectedOption > 1)
		mSelectedOption = 0;

	mCursor->Pos(mCursorStartPos + mCursorOffset * mSelectedOption);
}

void StartScreen::Score(int score)
{
	mLastScore = score;

	if (mLastScore > mHighScore)
		mHighScore = mLastScore;

	mPrevScore->Score(mLastScore);
	mTopScore->Score(mHighScore);
}

void StartScreen::Update()
{
	if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN))
		ChangeSelectedOption(1);
	else if (mInputManager->KeyPressed(SDL_SCANCODE_UP))
		ChangeSelectedOption(-1);

	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval)
	{
		mSelectedOptionVisible = !mSelectedOptionVisible;
		mBlinkTimer = 0.0f;
	}

	if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN) || mInputManager->KeyPressed(SDL_SCANCODE_UP))
	{
		mBlinkTimer = 0.0f;
		mSelectedOptionVisible = true;
	}
}

void StartScreen::Render()
{
	mScore->Render();
	mHiScore->Render();
	mPrevScore->Render();
	mTopScore->Render();

	mLogo->Render();

	if ((mSelectedOption == 0 && mSelectedOptionVisible) || mSelectedOption != 0)
		mStartGame->Render();
	if ((mSelectedOption == 1 && mSelectedOptionVisible) || mSelectedOption != 1)
		mInstructions->Render();
	mCursor->Render();

	mCreator->Render();
	mAssets->Render();
	mPatch->Render();
}