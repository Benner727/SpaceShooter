#ifndef LEVEL_H
#define LEVEL_H

#include "PlayTopBar.h"
#include "Player.h"
#include "Meteor.h"
#include "PowerUp.h"

class Level : public GameEntity
{
public:
	enum LEVEL_STATES {running, gameover};

	const int MAX_METEORS = 45;
private:
	Timer* mTimer;

	float mLevelTimer;
	float mMeteorTimer;

	PlayTopBar* mTopBar;

	Player* mPlayer;
	bool mPlayerHit;
	float mPlayerRespawnDelay;
	float mPlayerRespawnTimer;

	Texture* mRespawnLabel;
	float mRespawnLabelOnScreen;

	Texture* mGameOverLabel;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LEVEL_STATES mCurrentState;

	std::vector<Meteor*> mMeteors;

	std::vector<PowerUp*> mPowerUps;

	void HandleCollision();
	void HandlePlayerDeath();

	void ClearMeteors();
	void HandleMeteorSpawning();
	void HandleScoring(int i);
	void HandleMeteorCollision();
	void HandleMeteors();

	void ClearPowerUps();
	void HandlePowerUps();

public:
	Level(PlayTopBar* topBar, Player* player);
	~Level();

	LEVEL_STATES State();

	void Update();
	void Render();
};

#endif