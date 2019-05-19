#include "PowerUp.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"


PowerUp::PowerUp(Vector2 pos, Vector2 dir, int type)
{
	mTimer = Timer::Instance();

	mType = type;

	switch (mType)
	{
	case 0:
		mTexture = new Texture("PowerUps/shield_silver.png");
		break;
	case 1:
		mTexture = new Texture("PowerUps/things_silver.png");
		break;
	case 2:
		mTexture = new Texture("PowerUps/star_silver.png");
		break;
	default:
		mTexture = new Texture("PowerUps/shield_silver.png");
	}
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);

	Pos(pos);

	mDirection = dir;

	mPowerUpTimer = 0.0f;

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.25f;
	mColor = 0;

	mDead = false;

	AddCollider(new CircleCollider(mTexture->ScaledDimensions().x));

	mCollisionLayer = CollisionLayers::PowerUp;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}


PowerUp::~PowerUp()
{
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

bool PowerUp::Dead()
{
	return mDead;
}

int PowerUp::Type()
{
	return mType;
}

void PowerUp::Hit(PhysEntity* other)
{
	mDead = true;
}

void PowerUp::Update()
{
	Translate(mDirection * mSpeed * mTimer->DeltaTime(), world);

	mPowerUpTimer += mTimer->DeltaTime();
	mBlinkTimer += mTimer->DeltaTime();

	if (mBlinkTimer >= mBlinkInterval)
	{
		switch (mColor)
		{
		case 0:
			mTexture->Color(255, 255, 255);
			break;
		case 1:
			mTexture->Color(255, 0, 0);
			break;
		case 2:
			mTexture->Color(0, 255, 0);
			break;
		case 3:
			mTexture->Color(0, 0, 255);
			break;
		}

		mBlinkTimer = 0.0f;
		mColor++;

		if (mColor > 3)
			mColor = 0;
	}

	if (mPowerUpTimer >= mPowerUpLife)
		mDead = true;
}

void PowerUp::Render()
{
	mTexture->Render();

	PhysEntity::Render();
}