#ifndef RAIDER_H
#define RAIDER_H

#include "Ship.h"

class Raider : public Ship
{
private:
	enum STATUS { healthy, scratched, injured, critical, dead };

	Timer* mTimer;
	AudioManager* mAudio;

	STATUS mStatus;

	const float RECHARGE_DELAY = 6.0f;
	float mRechargeTimer;
	bool mShielded;

	bool  mVisible;
	bool mWasHit;
	bool mAnimating;

	Texture *mShip;

	Texture* mShield;

	static const int TOTAL_DAMAGES = 3;
	Texture* mDamages[TOTAL_DAMAGES];

	AnimatedTexture* mDeathAnimation;

	float mAcceleration;
	float mOrientation;
	float mRotationSpeed;

	Vector2 mVelocity;
	Vector2 mDirection;

	static const int TOTAL_ENGINES = 1;
	GameEntity* mEngine[TOTAL_ENGINES];

	static const int TOTAL_GUNS = 2;
	GameEntity* mGun[TOTAL_GUNS];

	float mReloadTimer;
	const float FIRE_RATE = 0.15f;

	static const int MAX_BULLETS = 8;
	Bullet* mBullets[MAX_BULLETS];

	std::vector<Particle*> mParticles;

	const float DOUBLE_POINTS = 15.0f;
	float mDoublePointTimer;
	bool mDoublePoints;

	const float INVINCIBLE_TIME = 5.0f;
	float mInvincibleTimer;
	bool mInvincible;

	bool IgnoreCollisions() override;

	void HandleMovement();
	void HandleParticles();
public:
	Raider();
	~Raider();

	void Reset();

	void Visible(bool visible);

	void Hit(PhysEntity* other) override;
	bool WasHit();

	bool DoublePoints();
	float DoublePointsTimer();

	bool IsAnimating();

	float Accuracy();

	void Accelerate(bool forward);
	void Turn(bool clockwise);
	void Fire();

	void Update();
	void Render();
};

#endif