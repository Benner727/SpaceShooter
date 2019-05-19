#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Player::Player(int ship)
{
	mInput = InputManager::Instance();

	mScore = 0;
	mLives = 3;

	switch (ship)
	{
	case 0:
		mShip = new Wasp;
		break;
	case 1:
		mShip = new Raider;
		break;
	case 2:
		mShip = new Hyperion;
		break;
	default:
		mShip = new Raider;
	}

	mShip->Parent(this);
	mShip->Pos(VEC2_ZERO);

	mTimeSurvived = 0.0f;

	for (int i = 0; i < 5; i++)
		mMeteorsDestroyed[i] = 0;
}

Player::~Player()
{
	mInput = nullptr;

	delete mShip;
	mShip = nullptr;
}

void Player::Reset()
{
	mShip->Reset();
	mShip->Pos(VEC2_ZERO);
}

void Player::HandleMovement()
{
	//Apply forward acceleration
	if (mInput->KeyDown(SDL_SCANCODE_W))
	{
		mShip->Accelerate(true);
	}

	//Apply backward acceleration
	if (mInput->KeyDown(SDL_SCANCODE_S))
	{
		mShip->Accelerate(false);
	}

	//Subtract from rotation
	if (mInput->KeyDown(SDL_SCANCODE_A))
	{
		mShip->Turn(false);
	}

	//Add to rotation
	if (mInput->KeyDown(SDL_SCANCODE_D))
	{
		mShip->Turn(true);
	}
}

void Player::HandleFiring()
{
	if (mInput->KeyDown(SDL_SCANCODE_SPACE))
	{
		mShip->Fire();
	}
}

void Player::Visible(bool visible)
{
	mShip->Visible(visible);
}

bool Player::WasHit()
{
	return mShip->WasHit();
}

bool Player::IsAnimating()
{
	return mShip->IsAnimating();
}

int Player::Accuracy() const
{
	return (int)(mShip->Accuracy() * 100);
}

int Player::Score() const
{
	return mScore;
}

int Player::Lives()
{
	return mLives;
}

void Player::TimeSurvived(float time)
{
	mTimeSurvived = time;
}

float Player::TimeSurvived() const
{
	return mTimeSurvived;
}

void Player::MeteorDesroyed(int size)
{
	mMeteorsDestroyed[size]++;
}

int Player::HugeMeteors() const
{
	return mMeteorsDestroyed[0];
}

int Player::BigMeteors() const
{
	return mMeteorsDestroyed[1];
}

int Player::MediumMeteors() const
{
	return mMeteorsDestroyed[2];
}

int Player::SmallMeteors() const
{
	return mMeteorsDestroyed[3];
}

int Player::TinyMeteors() const
{
	return mMeteorsDestroyed[4];
}

void Player::AddScore(int change)
{
	if (mShip->DoublePoints())
		change *= 2;
	
	mScore += change;
}

void Player::Died()
{
	mLives--;
}

Ship* Player::Ship()
{
	return mShip;
}

void Player::Update()
{
	if (Active())
	{
		HandleMovement();
		HandleFiring();
	}

	mShip->Update();
}

void Player::Render()
{
	mShip->Render();
}