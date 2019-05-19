#ifndef METEOR_H
#define METEOR_H

#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "AudioManager.h"

class Meteor : public PhysEntity
{
public:
	enum SIZE { huge, big, med, small, tiny };

private:
	int mIndex;

	Timer *mTimer;
	AudioManager *mAudio;

	SIZE mSize;

	bool mSpawning;
	bool mAnimating;
	bool mDead;

	AnimatedTexture* mDeathAnimation;

	float mSpeed;
	float mAcceleration;
	float mVelocity;
	float mTurn;
	float mSpin;
	Vector2 mDirection;

	Texture* mTexture;

	bool mWasHit;
	bool mWasShot;
	bool mWasCrashed;

	void Initialize();

	bool IgnoreCollisions() override;

public:
	Meteor(SIZE size, Vector2 pos);
	Meteor(SIZE size, Vector2 pos, Vector2 dir);
	~Meteor();

	SIZE Size() { return mSize; }
	Vector2 Direction() { return mDirection; }

	void Hit(PhysEntity* other) override;
	bool WasHit();
	bool WasShot();
	bool WasCrashed();

	bool IsAnimating();
	bool Dead();

	void Update();
	void Render();
};

#endif