#include "Bullet.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Bullet::Bullet(bool friendly)
{
	mTimer = Timer::Instance();

	mSpeed = 1250.0f;

	mMaxDistance = 500.0f;

	if (friendly)
	{
		mTexture = new Texture("laserGreen11.png");
		mCollisionLayer = PhysEntity::CollisionLayers::FriendlyProjectiles;
	}
	else
	{
		mTexture = new Texture("laserRed01.png");
		mCollisionLayer = PhysEntity::CollisionLayers::HostileProjectiles;
	}

	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);

	mReloadTimer = 0.0f;

	mMisses = 0;
	mHits = 0;

	Reload();

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}

Bullet::~Bullet()
{
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void Bullet::Speed(float speed)
{
	mSpeed = speed;
}

void Bullet::MaxDistance(float distance)
{
	mMaxDistance = distance;
}

void Bullet::Fire(Vector2 pos, float rotation)
{
	Pos(pos);
	Rotation(rotation);
	Active(true);
	mDistanceTravelled = 0.0f;
}

void Bullet::Reload()
{
	Active(false);
}

void Bullet::Hit(PhysEntity* other)
{
	mHits++;
	Reload();
}

bool Bullet::IgnoreCollisions()
{
	return !Active();
}

int Bullet::Misses()
{
	return mMisses;
}

int Bullet::Hits()
{
	return mHits;
}

void Bullet::Update()
{
	if (Active())
	{ 
		Vector2 prevPos = Pos();
		Translate(VEC2_UP * mSpeed * mTimer->DeltaTime(), local);
		mDistanceTravelled += -(VEC2_UP * mSpeed * mTimer->DeltaTime()).y;

		if (mDistanceTravelled >= mMaxDistance)
		{
			mMisses++;
			Reload();
		}
		else
		{
			if (Pos().x < 0 - mTexture->ScaledDimensions().x * 0.5f)
				Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH + mTexture->ScaledDimensions().x * 0.5f, Pos().y));

			if (Pos().x > Graphics::Instance()->SCREEN_WIDTH + mTexture->ScaledDimensions().x * 0.5f)
				Pos(Vector2(0.0f - mTexture->ScaledDimensions().x * 0.5f, Pos().y));

			if (Pos().y < 0 - mTexture->ScaledDimensions().y * 0.5f)
				Pos(Vector2(Pos().x, Graphics::Instance()->SCREEN_HEIGHT + mTexture->ScaledDimensions().y * 0.5f));

			if (Pos().y > Graphics::Instance()->SCREEN_HEIGHT + mTexture->ScaledDimensions().y * 0.5f)
				Pos(Vector2(Pos().x, 0.0f - mTexture->ScaledDimensions().y * 0.5f));
		}
	}
}

void Bullet::Render()
{
	if (Active())
	{
		mTexture->Render();
		PhysEntity::Render();
	}
}