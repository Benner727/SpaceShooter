#include "Raider.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "PowerUp.h"

Raider::Raider()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mWasHit = false;
	mAnimating = false;

	mShip = new Texture("Ships/playerShip1_red.png");
	mShip->Parent(this);
	mShip->Pos(VEC2_ZERO);

	mShield = new Texture("Ships/shield1.png");
	mShield->Parent(this);
	mShield->Pos(VEC2_ZERO);

	mDamages[0] = new Texture("Ships/playerShip1_damage1.png");
	mDamages[1] = new Texture("Ships/playerShip1_damage2.png");
	mDamages[2] = new Texture("Ships/playerShip1_damage3.png");

	for (int i = 0; i < TOTAL_DAMAGES; i++)
	{
		mDamages[i]->Parent(this);
		mDamages[i]->Pos(VEC2_ZERO);
	}

	mDeathAnimation = new AnimatedTexture("Ships/shipExplosion.png", 0, 0, 100, 102, 4, 1.0f, AnimatedTexture::horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::once);

	mAcceleration = 650.0f;
	mRotationSpeed = 6.0f;

	Reset();

	mEngine[0] = new GameEntity();
	mEngine[0]->Parent(this);
	mEngine[0]->Pos(Vector2(0.0f, mShip->ScaledDimensions().y * 0.55f));

	for (int i = 0; i < TOTAL_GUNS; i++)
	{
		mGun[i] = new GameEntity();
		mGun[i]->Parent(this);
	}

	mGun[0]->Pos(Vector2(mShip->ScaledDimensions().x * 0.45f, mShip->ScaledDimensions().y * -0.25f));
	mGun[1]->Pos(Vector2(mShip->ScaledDimensions().x * -0.45f, mShip->ScaledDimensions().y * -0.25f));

	for (int i = 0; i < MAX_BULLETS; i++)
		mBullets[i] = new Bullet(true);

	mReloadTimer = 0.0f;

	AddCollider(new BoxCollider(Vector2(24.0f, 75.0f)));
	AddCollider(new BoxCollider(Vector2(99.0f, 39.0f)), Vector2(0.0f, 9.0f));

	mCollisionLayer = CollisionLayers::Friendly;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}

Raider::~Raider()
{
	mTimer = nullptr;
	mAudio = nullptr;

	delete mShip;
	mShip = nullptr;

	delete mShield;
	mShield = nullptr;

	for (int i = 0; i < TOTAL_DAMAGES; i++)
	{
		delete mDamages[i];
		mDamages[i] = nullptr;
	}

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

	for (int i = 0; i < TOTAL_ENGINES; i++)
	{
		delete mEngine[i];
		mEngine[i] = nullptr;
	}

	for (int i = 0; i < TOTAL_GUNS; i++)
	{
		delete mGun[i];
		mGun[i] = nullptr;
	}

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		delete mBullets[i];
		mBullets[i] = nullptr;
	}
}

void Raider::Reset()
{
	mRechargeTimer = 0.0f;
	mShielded = true;

	mStatus = healthy;

	Active(true);

	mOrientation = 0.0f;
	Rotation(mOrientation);

	mVelocity = VEC2_ZERO;
	mDirection.x = cos(Rotation());
	mDirection.y = sin(Rotation());

	mDoublePointTimer = 0.0f;
	mDoublePoints = false;

	mInvincibleTimer = 0.0f;
	mInvincible = false;
}

bool Raider::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Raider::HandleMovement()
{
	//Find current direction vector
	mDirection.x = cos(((Rotation() - 90.0f) * DEG_TO_RAD));
	mDirection.y = sin(((Rotation() - 90.0f) * DEG_TO_RAD));
	mDirection.Normalize();

	//Simulate friction
	mVelocity *= 0.99f;
	mOrientation *= 0.99f;

	Translate(mVelocity * mTimer->DeltaTime(), world);
	Rotate(mOrientation);

	//Keep ship on screen
	if (Pos(world).x < 0.0f - mShip->ScaledDimensions().x * 0.5f)
		Translate(Vector2((Graphics::Instance()->SCREEN_WIDTH + mShip->ScaledDimensions().x), 0.0f), world);

	if (Pos(world).x > Graphics::Instance()->SCREEN_WIDTH + mShip->ScaledDimensions().x * 0.5f)
		Translate(Vector2(-(Graphics::Instance()->SCREEN_WIDTH + mShip->ScaledDimensions().x), 0.0f), world);

	if (Pos(world).y < 0.0f - mShip->ScaledDimensions().y * 0.5f)
		Translate(Vector2(0.0f, (Graphics::Instance()->SCREEN_HEIGHT + mShip->ScaledDimensions().y)), world);

	if (Pos(world).y > Graphics::Instance()->SCREEN_HEIGHT + mShip->ScaledDimensions().y * 0.5f)
		Translate(Vector2(0.0f, -(Graphics::Instance()->SCREEN_HEIGHT + mShip->ScaledDimensions().y)), world);
}

void Raider::HandleParticles()
{
	for (int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i]->Update();

		if (mParticles[i]->Dead())
		{
			delete mParticles[i];
			mParticles[i] = nullptr;

			mParticles.erase(mParticles.begin() + i);
		}
	}
}

void Raider::Visible(bool visible)
{
	mVisible = visible;
}

void Raider::Hit(PhysEntity* other)
{
	if (other->CollisionLayer() == CollisionLayers::Meteor)
	{
		mRechargeTimer = RECHARGE_DELAY;
		
		if (mInvincible)
		{
			//Ignore damage
		}
		else if (mShielded)
		{
			mShielded = false;
			mAudio->PlaySFX("shield_down.wav", 0, 0);
		}
		else
		{
			switch (mStatus)
			{
			case healthy:
				mStatus = scratched;
				mAudio->PlaySFX("hit.mp3", 0, 1);
				break;
			case scratched:
				mStatus = injured;
				mAudio->PlaySFX("hit.mp3", 0, 1);
				break;
			case injured:
				mStatus = critical;
				mAudio->PlaySFX("hit.mp3", 0, 1);
				break;
			case critical:
				mStatus = dead;
				mDeathAnimation->ResetAnimation();
				mAnimating = true;
				mWasHit = true;
				Active(false);
				mAudio->PlaySFX("8bit_bomb_explosion.wav", 0, 2);
				break;
			}
		}
	}
	else if (other->CollisionLayer() == CollisionLayers::PowerUp)
	{
		int type = static_cast<PowerUp*> (other)->Type();

		switch (type)
		{
		case 0:
			mRechargeTimer = 0.0f;
			mShielded = true;

			mStatus = healthy;
			break;
		case 1:
			mDoublePoints = true;
			mDoublePointTimer = DOUBLE_POINTS;
			break;
		case 2:
			mInvincibleTimer = INVINCIBLE_TIME;
			mInvincible = true;
			break;
		}

		mAudio->PlaySFX("powerup_pickup.wav", 0, 0);
	}
}

bool Raider::WasHit()
{
	return mWasHit;
}

bool Raider::DoublePoints()
{
	return mDoublePoints;
}

float Raider::DoublePointsTimer()
{
	return mDoublePointTimer;
}

bool Raider::IsAnimating()
{
	return mAnimating;
}

float Raider::Accuracy()
{
	int totalMisses = 0;
	int totalHits = 0;

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		totalMisses += mBullets[i]->Misses();
		totalHits += mBullets[i]->Hits();
	}

	return totalHits ? (float)totalHits / (totalMisses + totalHits) : totalHits;
}

void Raider::Accelerate(bool forward)
{
	//Apply forward acceleration
	if (forward)
	{
		mVelocity += mDirection * mAcceleration * mTimer->DeltaTime();

		for (int i = 0; i < TOTAL_ENGINES; i++)
		{
			mParticles.push_back(new Particle(mEngine[i]->Pos(), -mVelocity));
			mParticles.push_back(new Particle(mEngine[i]->Pos(), -mVelocity));
			mParticles.push_back(new Particle(mEngine[i]->Pos(), -mVelocity));
		}
	}
	//Apply backward acceleration
	else
	{
		mVelocity -= mDirection * mAcceleration * 0.66f * mTimer->DeltaTime();
	}
}

void Raider::Turn(bool clockwise)
{
	//Add to rotation
	if (clockwise)
	{
		mOrientation += mRotationSpeed * mTimer->DeltaTime();
	}
	//Subtract from rotation
	else
	{
		mOrientation -= mRotationSpeed * mTimer->DeltaTime();
	}
}

void Raider::Fire()
{
	if (mReloadTimer > 0.0f)
		return;
	else
	{
		int gun = 0;

		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (!mBullets[i]->Active())
				gun++;
		}


		if (gun >= TOTAL_GUNS)
		{
			gun = 0;

			for (int i = 0; i < MAX_BULLETS; i++)
			{
				if (!mBullets[i]->Active())
				{
					mBullets[i]->Fire(mGun[gun]->Pos(), Rotation());
					gun++;

					if (gun == TOTAL_GUNS)
					{
						mAudio->PlaySFX("sfx_laser1.ogg", 0, 2);
						break;
					}
				}
			}
		}

		mReloadTimer = FIRE_RATE;
	}
}

void Raider::Update()
{
	if (mAnimating)
	{
		if (mWasHit)
			mWasHit = false;

		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
		mVisible = mAnimating;
	}
	else
	{
		if (Active())
		{
			HandleMovement();

			if (mInvincible)
				mShip->Flash(255, 0, 0);

			if (mRechargeTimer > 0.0f)
			{
				mRechargeTimer -= mTimer->DeltaTime();

				if (mRechargeTimer <= 0.0f)
				{
					mRechargeTimer = 0.0f;
					mShielded = true;
					mAudio->PlaySFX("shield_up.wav", 0, 0);
				}
			}

			if (mReloadTimer > 0.0f)
			{
				mReloadTimer -= mTimer->DeltaTime();

				if (mReloadTimer <= 0.0f)
					mReloadTimer = 0.0f;
			}

			if (mInvincibleTimer > 0.0f)
			{
				mInvincibleTimer -= mTimer->DeltaTime();

				if (mInvincibleTimer <= 0.0f)
				{
					mInvincibleTimer = 0.0f;
					mInvincible = false;
				}
			}
		}
	}

	if (mDoublePointTimer > 0.0f)
	{
		mDoublePointTimer -= mTimer->DeltaTime();

		if (mDoublePointTimer <= 0.0f)
		{
			mDoublePointTimer = 0.0f;
			mDoublePoints = false;
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++)
		mBullets[i]->Update();

	HandleParticles();
}

void Raider::Render()
{
	if (mVisible)
	{
		switch (mStatus)
		{
		case healthy:
			mShip->Render();
			break;
		case scratched:
			mShip->Render();
			mDamages[0]->Render();
			break;
		case injured:
			mShip->Render();
			mDamages[1]->Render();
			break;
		case critical:
			mShip->Render();
			mDamages[2]->Render();
			break;
		case dead:
			mDeathAnimation->Render();
			break;
		}

		if (mShielded)
			mShield->Render();
	}

	for (int i = 0; i < MAX_BULLETS; i++)
		mBullets[i]->Render();

	for (int i = 0; i < mParticles.size(); i++)
		mParticles[i]->Render();

	PhysEntity::Render();
}