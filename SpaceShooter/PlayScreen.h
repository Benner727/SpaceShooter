#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include "Level.h"

class PlayScreen : public GameEntity
{
private:
	Timer *mTimer;
	InputManager* mInput;

	PlayTopBar* mTopBar;

	Texture* mPlayLabel[4];

	float mGameStartTimer;
	float mGameStartDelay;

	bool mGameStarted;

	Level* mLevel;

	Player* mPlayer;

	int mPlayerScore;
public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame(int ship);

	bool GameOver();

	Player& GetPlayer() const;

	void Update();
	void Render();
};

#endif