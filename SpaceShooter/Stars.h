#ifndef STARS_H
#define STARS_H

#include "AnimatedTexture.h"
#include <vector>

class Stars : GameEntity
{
public:
	Stars();
	~Stars();

private:
	const int TOTAL_STARS = 75;
	const float SCROLL_SPEED = 250.0f;

	Timer* mTimer;

	std::vector<AnimatedTexture*> mStars;

	bool mPaused;

	void Scroll();
public:
	void Pause();
	void Start();

	void Update();
	void Render();
};

#endif