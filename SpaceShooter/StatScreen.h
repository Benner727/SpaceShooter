#ifndef STATSCREEN_H
#define STATSCREEN_H

#include "Scoreboard.h"
#include "Timer.h"
#include "InputManager.h"
#include "Player.h"

class StatScreen : public GameEntity
{
public:
	StatScreen();
	~StatScreen();

private:
	Timer* mTimer;

	Texture* mTitle;

	GameEntity* mStats;
	Texture* mStatsTitle;

	Texture* mScoreText;
	Scoreboard* mScore;

	Texture* mTimeText;
	Scoreboard* mTime;

	Texture* mAccuracyText;
	Scoreboard* mAccuracy;

	GameEntity* mMeteorStats;
	Texture* mMeteorTitle;

	Texture* mHugeMeteorsText;
	Scoreboard* mHugeMeteors;

	Texture* mBigMeteorsText;
	Scoreboard* mBigMeteors;

	Texture* mMediumMeteorsText;
	Scoreboard* mMediumMeteors;

	Texture* mSmallMeteorsText;
	Scoreboard* mSmallMeteors;

	Texture* mTinyMeteorsText;
	Scoreboard* mTinyMeteors;

	Texture* mContinue;
	float mContinueBlinkTimer;
	float mContinueBlinkInterval;
	bool mContinueVisible;

public:
	void Initialize(const Player& player);

	void Update();
	void Render();
};

#endif