#ifndef PLAYER_H
#define PLAYER_H

#include "Raider.h"
#include "Wasp.h"
#include "Hyperion.h"

class Player : public GameEntity
{
private:
	InputManager* mInput;

	int mScore;
	int mLives;

	float mTimeSurvived;

	Ship *mShip;

	int mMeteorsDestroyed[5];

	void HandleMovement();
	void HandleFiring();

public:
	Player(int ship);
	~Player();

	void Reset();

	void Visible(bool visible);

	bool WasHit();

	bool IsAnimating();

	int Accuracy() const;

	int Score() const;
	int Lives();
	
	void TimeSurvived(float time);
	float TimeSurvived() const;

	void MeteorDesroyed(int size);
	int HugeMeteors() const;
	int BigMeteors() const;
	int MediumMeteors() const;
	int SmallMeteors() const;
	int TinyMeteors() const;

	void AddScore(int change);
	void Died();

	Ship* Ship();

	void Update();
	void Render();
};

#endif