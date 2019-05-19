#ifndef PLAYTOPBAR_H
#define PLAYTOPBAR_H

#include "Timer.h"
#include "Scoreboard.h"

class PlayTopBar : public GameEntity
{
private:
	Timer *mTimer;

	Scoreboard* mScore;

	GameEntity* mPlayerLives;
	Texture *mShip;
	Texture *mSymbol;
	Scoreboard* mTotalLivesLabel;
	int mTotalLives;

	GameEntity* mDoublePoints;
	Texture* mDoublePointsLabel;
	Scoreboard* mDoublePointsTimer;
	float mDoublePointsTime;

	float mBlinkTimer;
	float mBlinkInterval;
	bool mVisible;

public:
	PlayTopBar(int ship);
	~PlayTopBar();

	void Score(int score);
	void Lives(int lives);
	void DoublePoints(float doublepoints);

	void Update();
	void Render();
};

#endif