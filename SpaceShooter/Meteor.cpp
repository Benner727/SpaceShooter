#include "Meteor.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"

Meteor::Meteor(SIZE size, Vector2 pos)
{
	mSize = size;
	Pos(pos);
	mSpawning = true;

	//float offsetx = rand() % Graphics::SCREEN_WIDTH * 0.33f;
	//float offsety = rand() % Graphics::SCREEN_HEIGHT * 0.33f;

	//mDirection = (Vector2((Graphics::SCREEN_WIDTH * 0.5f) - offsetx, (Graphics::SCREEN_HEIGHT * 0.5f) - offsety) - Pos(GameEntity::world)).Normalize();

	float offsetx = rand() % Graphics::SCREEN_WIDTH * 0.10f;
	float offsety = rand() % Graphics::SCREEN_HEIGHT * 0.25f;

	mDirection = (Vector2((Graphics::SCREEN_WIDTH * 0.55f) - offsetx, (Graphics::SCREEN_HEIGHT * 0.9f) - offsety) - Pos(GameEntity::world)).Normalize();

	Initialize();
};

Meteor::Meteor(SIZE size, Vector2 pos, Vector2 dir)
{
	mSize = size;
	Pos(pos);
	mDirection = dir;
	mSpawning = false;

	Initialize();
};

Meteor::~Meteor()
{
	mTimer = nullptr;
	mAudio = nullptr;

	delete mTexture;
	mTexture = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;
}

void Meteor::Initialize()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mAnimating = false;
	mDead = false;

	mDeathAnimation = new AnimatedTexture("meteorExplosion.png", 0, 0, 100, 102, 4, 0.33f, AnimatedTexture::horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::once);

	//mSpeed = 125.0f * ((int)mSize + 1);
	//mSpeed = 125.0f + ((int)mSize * 75);
	mSpeed = 150.0f + ((int)mSize * 100);
	mAcceleration = mSpeed * 0.05f;
	mVelocity = mSpeed * 0.50f;

	mTurn = (1.5f * ((int)mSize + 1));
	mSpin = mTurn * 0.50;

	std::string path = "Meteors/meteorBrown_";

	switch (mSize)
	{
	case huge:
		path += "huge" + std::to_string(rand() % 4 + 1);
		mDeathAnimation->Scale(Vector2(1.5f, 1.5f));
		break;
	case big:
		path += "big" + std::to_string(rand() % 4 + 1);
		mDeathAnimation->Scale(Vector2(0.75f, 0.75f));
		break;
	case med:
		path += "med" + std::to_string(rand() % 2 + 1);
		mDeathAnimation->Scale(Vector2(0.35f, 0.35f));
		break;
	case small:
		path += "small" + std::to_string(rand() % 2 + 1);
		mDeathAnimation->Scale(Vector2(0.15f, 0.15f));
		break;
	case tiny:
		path += "tiny" + std::to_string(rand() % 2 + 1);
		mDeathAnimation->Scale(Vector2(0.05f, 0.05f));
		break;
	default:
		path += "tiny" + std::to_string(rand() % 2 + 1);
		mDeathAnimation->Scale(Vector2(0.05f, 0.05f));
	}

	mTexture = new Texture(path + ".png");
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);

	AddCollider(new CircleCollider(mTexture->ScaledDimensions().x * 0.5f));

	mCollisionLayer = CollisionLayers::Meteor;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);

	mWasHit = false;
	mWasShot = false;
	mWasCrashed = false;
}

void Meteor::Hit(PhysEntity* other)
{
	mDeathAnimation->ResetAnimation();
	mAnimating = true;
	mWasHit = true;

	if (other->CollisionLayer() == CollisionLayers::FriendlyProjectiles)
		mWasShot = true;
	else if (other->CollisionLayer() == CollisionLayers::Friendly)
		mWasCrashed = true;
}

bool Meteor::WasHit()
{
	return mWasHit;
}

bool Meteor::WasShot()
{
	return mWasShot;
}

bool Meteor::WasCrashed()
{
	return mWasCrashed;
}

bool Meteor::IsAnimating()
{
	return mAnimating;
}

bool Meteor::Dead()
{
	return mDead;
}

bool Meteor::IgnoreCollisions()
{
	return mAnimating || mDead || mSpawning;
}

void Meteor::Update()
{
	if (mAnimating)
	{
		if (mWasHit)
			mWasHit = false;

		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
		mDead = !mAnimating;
	}
	else
	{
		mVelocity += mSpeed * mTimer->DeltaTime();
		mVelocity *= 0.99f;
		mSpeed += mAcceleration * mTimer->DeltaTime();
		Translate(mDirection * mVelocity * mTimer->DeltaTime(), world);
		
		mSpin += mTurn * mTimer->DeltaTime();
		mSpin *= 0.99f;
		Rotate(mSpin);

		//Keep meteor on screen

		if (mSpawning)
		{
			if (((Pos().x > 0 - mTexture->ScaledDimensions().x * 0.5f) && (Pos().x < Graphics::Instance()->SCREEN_WIDTH + mTexture->ScaledDimensions().x * 0.5f))
				&& ((Pos().y > 0 - mTexture->ScaledDimensions().x * 0.5f) && (Pos().y < Graphics::Instance()->SCREEN_HEIGHT + mTexture->ScaledDimensions().x * 0.5f)))
			{
				mSpawning = false;
			}
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

void Meteor::Render()
{
	if (mAnimating)
		mDeathAnimation->Render();
	else
		mTexture->Render();
	
	PhysEntity::Render();
}