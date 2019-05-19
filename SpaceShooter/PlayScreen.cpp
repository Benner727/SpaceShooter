#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mTopBar = nullptr;

	mPlayLabel[0] = new Texture("3", "kenvector_future.ttf", 54, { 34, 178, 34 });
	mPlayLabel[1] = new Texture("2", "kenvector_future.ttf", 54, { 34, 178, 34 });
	mPlayLabel[2] = new Texture("1", "kenvector_future.ttf", 54, { 34, 178, 34 });
	mPlayLabel[3] = new Texture("GO!", "kenvector_future.ttf", 54, { 34, 178, 34 });

	for (int i = 0; i < 4; i++)
	{
		mPlayLabel[i]->Parent(this);
		mPlayLabel[i]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5, Graphics::Instance()->SCREEN_HEIGHT * 0.5));
	}

	mGameStartTimer = 0.0f;
	mGameStartDelay = 4.0f;
	mGameStarted = false;

	mLevel = nullptr;

	mPlayer = nullptr;

	mPlayerScore = 0;
}

PlayScreen::~PlayScreen()
{
	mTimer = nullptr;
	mInput = nullptr;

	delete mTopBar;
	mTopBar = nullptr;

	for (int i = 0; i < 4; i++)
	{
		delete mPlayLabel[i];
		mPlayLabel[i] = nullptr;
	}

	delete mLevel;
	mLevel = nullptr;

	delete mPlayer;
	mPlayer = nullptr;
}

void PlayScreen::StartNewGame(int ship)
{
	delete mPlayer;
	mPlayer = new Player(ship);
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5, Graphics::Instance()->SCREEN_HEIGHT * 0.5));
	mPlayer->Active(false);

	mTopBar = new PlayTopBar(ship);
	mTopBar->Parent(this);
	mTopBar->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, 50.0f));

	mTopBar->Score(mPlayer->Score());
	mTopBar->Lives(mPlayer->Lives());

	mGameStarted = false;
	mGameStartTimer = 0.0f;
}

bool PlayScreen::GameOver()
{
	if (!mGameStarted)
		return false;
	
	return (mLevel->State() == Level::gameover);
}

Player& PlayScreen::GetPlayer() const
{
	return *mPlayer;
}

void PlayScreen::Update()
{
	if (!mGameStarted)
	{
		mGameStartTimer += mTimer->DeltaTime();

		if (mGameStartTimer >= mGameStartDelay)
		{
			mGameStarted = true;
			mGameStartTimer = 0.0f;

			mLevel = new Level(mTopBar, mPlayer);
			mPlayer->Active(true);
			mPlayer->Visible(true);
		}
	}
	else if (mGameStarted)
	{
		mTopBar->Update();
		mLevel->Update();
		mPlayer->Update();

		mPlayerScore = mPlayer->Score();
	}
}

void PlayScreen::Render()
{
	if (!mGameStarted)
		mPlayLabel[(int)mGameStartTimer]->Render();
	else if (mGameStarted)
	{
		mLevel->Render();
		mPlayer->Render();
	}

	mTopBar->Render();
}