#include "StatScreen.h"



StatScreen::StatScreen()
{
	mTimer = Timer::Instance();

	mTitle = new Texture("GAME OVER", "kenvector_future.ttf", 64, { 178, 34, 34 });
	mTitle->Parent(this);
	mTitle->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, 50.0f));

	mStats = new GameEntity(Vector2(Graphics::SCREEN_WIDTH * 0.5f, 150.0f));
	mStatsTitle = new Texture("Stats", "kenvector_future.ttf", 48, { 34, 34, 178 });

	mScoreText = new Texture("Score:", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mScore = new Scoreboard;

	mTimeText = new Texture("Time Survived:", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mTime = new Scoreboard;
	mTime->Time(true);

	mAccuracyText = new Texture("Accuracy:", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mAccuracy = new Scoreboard;
	mAccuracy->Percentage(true);

	mStatsTitle->Parent(mStats);
	mScoreText->Parent(mStats);
	mScore->Parent(mStats);
	mTimeText->Parent(mStats);
	mTime->Parent(mStats);
	mAccuracyText->Parent(mStats);
	mAccuracy->Parent(mStats);
	mStats->Parent(this);

	mStatsTitle->Pos(VEC2_ZERO);
	mScoreText->Pos(Vector2(-150.0f, 80.0f));
	mScore->Pos(Vector2(150.0f, 80.0f));
	mTimeText->Pos(Vector2(-150.0f, 130.0f));
	mTime->Pos(Vector2(150.0f, 130.0f));
	mAccuracyText->Pos(Vector2(-150.0f, 180.0f));
	mAccuracy->Pos(Vector2(150.0f, 180.0f));

	mMeteorStats = new GameEntity(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));
	mMeteorTitle = new Texture("Meteors Destroyed", "kenvector_future.ttf", 48, { 34, 178, 34 });

	mHugeMeteorsText = new Texture("Huge Meteors:", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mHugeMeteors = new Scoreboard;

	mBigMeteorsText = new Texture("Big Meteors:", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mBigMeteors = new Scoreboard;

	mMediumMeteorsText = new Texture("Medium Meteors:", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mMediumMeteors = new Scoreboard;

	mSmallMeteorsText = new Texture("Small Meteors:", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mSmallMeteors = new Scoreboard;

	mTinyMeteorsText = new Texture("Tiny Meteors:", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mTinyMeteors = new Scoreboard;

	mMeteorTitle->Parent(mMeteorStats);
	mHugeMeteorsText->Parent(mMeteorStats);
	mHugeMeteors->Parent(mMeteorStats);
	mBigMeteorsText->Parent(mMeteorStats);
	mBigMeteors->Parent(mMeteorStats);
	mMediumMeteorsText->Parent(mMeteorStats);
	mMediumMeteors->Parent(mMeteorStats);
	mSmallMeteorsText->Parent(mMeteorStats);
	mSmallMeteors->Parent(mMeteorStats);
	mTinyMeteorsText->Parent(mMeteorStats);
	mTinyMeteors->Parent(mMeteorStats);
	mMeteorStats->Parent(this);

	mMeteorTitle->Pos(Vector2(VEC2_ZERO));
	mHugeMeteorsText->Pos(Vector2(-150.0f, 80.0f));
	mHugeMeteors->Pos(Vector2(150.0f, 80.0f));
	mBigMeteorsText->Pos(Vector2(-150.0f, 130.0f));
	mBigMeteors->Pos(Vector2(150.0f, 130.0f));
	mMediumMeteorsText->Pos(Vector2(-150.0f, 180.0f));
	mMediumMeteors->Pos(Vector2(150.0f, 180.0f));
	mSmallMeteorsText->Pos(Vector2(-150.0f, 230.0f));
	mSmallMeteors->Pos(Vector2(150.0f, 230.0f));
	mTinyMeteorsText->Pos(Vector2(-150.0f, 280.0f));
	mTinyMeteors->Pos(Vector2(150.0f, 280.0f));

	mContinue = new Texture("Press 'return' to continue", "kenvector_future.ttf", 32, { 80, 80, 80 });
	mContinue->Parent(this);
	mContinue->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT * 0.95f));

	mContinueBlinkTimer = 0.0f;
	mContinueBlinkInterval = 0.5f;
	mContinueVisible = true;
}


StatScreen::~StatScreen()
{
	mTimer = nullptr;

	delete mTitle;
	mTitle = nullptr;

	delete mStatsTitle;
	mStatsTitle = nullptr;

	delete mScoreText;
	mScoreText = nullptr;

	delete mScore;
	mScore = nullptr;

	delete mTimeText;
	mTimeText = nullptr;

	delete mTime;
	mTime = nullptr;

	delete mAccuracyText;
	mAccuracy = nullptr;

	delete mAccuracy;
	mAccuracy = nullptr;

	delete mStats;
	mStats = nullptr;

	delete mMeteorTitle;
	mMeteorTitle = nullptr;

	delete mHugeMeteorsText;
	mHugeMeteorsText = nullptr;

	delete mHugeMeteors;
	mHugeMeteors = nullptr;

	delete mBigMeteorsText;
	mBigMeteors = nullptr;

	delete mBigMeteors;
	mBigMeteors = nullptr;

	delete mMediumMeteorsText;
	mMediumMeteorsText = nullptr;

	delete mMediumMeteors;
	mMediumMeteors = nullptr;

	delete mSmallMeteorsText;
	mSmallMeteorsText = nullptr;

	delete mSmallMeteors;
	mSmallMeteors = nullptr;

	delete mTinyMeteorsText;
	mTinyMeteorsText = nullptr;

	delete mTinyMeteors;
	mTinyMeteors = nullptr;

	delete mMeteorStats;
	mMeteorStats = nullptr;

	delete mContinue;
	mContinue = nullptr;
}

void StatScreen::Initialize(const Player& player)
{
	mScore->Score(player.Score());
	mTime->Score(player.TimeSurvived());
	mAccuracy->Score(player.Accuracy());

	mHugeMeteors->Score(player.HugeMeteors());
	mBigMeteors->Score(player.BigMeteors());
	mMediumMeteors->Score(player.MediumMeteors());
	mSmallMeteors->Score(player.SmallMeteors());
	mTinyMeteors->Score(player.TinyMeteors());
}

void StatScreen::Update()
{
	mContinueBlinkTimer += mTimer->DeltaTime();
	if (mContinueBlinkTimer >= mContinueBlinkInterval)
	{
		mContinueVisible = !mContinueVisible;
		mContinueBlinkTimer = 0.0f;
	}
}

void StatScreen::Render()
{
	mTitle->Render();

	mStatsTitle->Render();
	mScoreText->Render();
	mScore->Render();
	mTimeText->Render();
	mTime->Render();
	mAccuracyText->Render();
	mAccuracy->Render();

	mMeteorTitle->Render();
	mHugeMeteorsText->Render();
	mHugeMeteors->Render();
	mBigMeteorsText->Render();
	mBigMeteors->Render();
	mMediumMeteorsText->Render();
	mMediumMeteors->Render();
	mSmallMeteorsText->Render();
	mSmallMeteors->Render();
	mTinyMeteorsText->Render();
	mTinyMeteors->Render();

	if (mContinueVisible)
		mContinue->Render();
}