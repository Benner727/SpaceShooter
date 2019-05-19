#ifndef BULLET_H
#define BULLET_H

#include "PhysEntity.h"
#include "Timer.h"

class Bullet : public PhysEntity
{
private:
	Timer *mTimer;

	float mSpeed;
	float mMaxDistance;
	float mDistanceTravelled;

	Texture* mTexture;

	int mMisses;
	int mHits;

	float mReloadTimer;
	const float RELOAD_TIME = 1.25f;

	bool IgnoreCollisions() override;
public:
	Bullet(bool friendly);
	~Bullet();

	void Speed(float speed);
	void MaxDistance(float distance);

	void Fire(Vector2 pos, float rotation);
	void Reload();

	int Misses();
	int Hits();

	void Hit(PhysEntity* other) override;

	void Update();
	void Render();
};

#endif