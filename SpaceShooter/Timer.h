#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
private:
	static Timer* sInstance;

	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
	float mDeltaTime;
	float mTimeScale;

	Timer();
	~Timer();

public:
	static Timer* Instance();
	static void Release();

	void Reset();
	float DeltaTime();

	void TimeScale(float);
	float TimeScale();

	void Update();
};

#endif