#ifndef PARTICLE_H
#define PARTICLE_H

#include "Texture.h"
#include "Timer.h"

class Particle : public GameEntity
{
public:
	Particle(Vector2 pos, Vector2 velocity);
	~Particle();

private:
	Timer* mTimer;

	Texture* mLivingTexture;
	Texture* mDyingTexture;

	Vector2 mVelocity;

	float mParticleLife;
	float mParticleTimer;
	int mFrameCount;

	bool mDead;

public:
	bool Dead();

	void Update();
	void Render();
};

#endif