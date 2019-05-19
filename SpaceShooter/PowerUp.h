#ifndef POWERUP_H
#define POWERUP_H

#include "PhysEntity.h"
#include "Timer.h"

class PowerUp : public PhysEntity
{
public:
	PowerUp(Vector2 pos, Vector2 dir, int type = 0);
	~PowerUp();

private:
	Timer* mTimer;

	int mType;

	Texture* mTexture;

	const float mPowerUpLife = 10.0f;
	float mPowerUpTimer;

	const float mSpeed = 75.0f;
	Vector2 mDirection;

	float mBlinkTimer;
	float mBlinkInterval;
	int mColor;

	bool mDead;
public:
	bool Dead();

	int Type();

	void Hit(PhysEntity* other) override;

	void Update();
	void Render();
};

#endif