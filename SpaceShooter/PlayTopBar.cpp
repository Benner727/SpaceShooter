#include "PlayTopBar.h"

PlayTopBar::PlayTopBar(int ship)
{
	mTimer = Timer::Instance();

	mScore = new Scoreboard();
	mScore->Parent(this);
	mScore->Pos(VEC2_ZERO);

	mPlayerLives = new GameEntity();

	switch (ship)
	{
	case 0:
		mShip = new Texture("Ships/playerLife3_green.png");
		break;
	case 1: 
		mShip = new Texture("Ships/playerLife1_red.png");
		break;
	case 2:
		mShip = new Texture("Ships/playerLife2_blue.png");
		break;
	default:
		mShip = new Texture("Ships/playerLife3_green.png");
	}
	
	
	mSymbol = new Texture("numeralX.png");
	mTotalLivesLabel = new Scoreboard();

	mShip->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.45, 0.0f));
	mSymbol->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.40, 0.0f));
	mTotalLivesLabel->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.35, 0.0f));

	mShip->Parent(mPlayerLives);
	mSymbol->Parent(mPlayerLives);
	mTotalLivesLabel->Parent(mPlayerLives);
	mPlayerLives->Parent(this);

	mDoublePoints = new GameEntity();
	mDoublePointsLabel = new Texture("Double Points:", "kenvector_future.ttf", 26, { 255, 215, 0 });
	mDoublePointsTimer = new Scoreboard();

	mDoublePointsLabel->Parent(mDoublePoints);
	mDoublePointsTimer->Parent(mDoublePoints);
	mDoublePoints->Parent(this);

	mDoublePoints->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));
	mDoublePointsLabel->Pos(Vector2(-75.0f, 0.0f));
	mDoublePointsTimer->Pos(Vector2(100.0f, 0.0f));
	mDoublePointsTime = 0.0f;

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mVisible = true;
}

PlayTopBar::~PlayTopBar()
{
	mTimer = nullptr;

	delete mScore;
	mScore = nullptr;

	delete mShip;
	mShip = nullptr;

	delete mSymbol;
	mSymbol = nullptr;

	delete mPlayerLives;
	mPlayerLives = nullptr;

	delete mDoublePointsLabel;
	mDoublePointsLabel = nullptr;

	delete mDoublePointsTimer;
	mDoublePointsTimer = nullptr;

	delete mDoublePoints;
	mDoublePoints = nullptr;
}

void PlayTopBar::Score(int score)
{
	mScore->Score(score);
}

void PlayTopBar::Lives(int lives)
{
	mTotalLives = lives;
	mTotalLivesLabel->Score(mTotalLives);
}

void PlayTopBar::DoublePoints(float doublepoints)
{
	mDoublePointsTime = doublepoints;
	mDoublePointsTimer->Score((int)mDoublePointsTime);
}

void PlayTopBar::Update()
{
	mScore->Update();

	mDoublePointsTimer->Update();

	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval)
	{
		mVisible = !mVisible;
		mBlinkTimer = 0.0f;
	}
}

void PlayTopBar::Render()
{
	mScore->Render();

	mShip->Render();
	mSymbol->Render();
	mTotalLivesLabel->Render();

	if (mDoublePointsTime > 0)
	{
		if (mVisible)
			mDoublePointsLabel->Render();
		mDoublePointsTimer->Render();
	}
}