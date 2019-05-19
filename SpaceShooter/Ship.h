#ifndef SHIP_H
#define SHIP_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Bullet.h"
#include "Particle.h"

class Ship : public PhysEntity
{
public:
	virtual void Reset() = 0;

	virtual void Visible(bool visible) = 0;

	virtual void Hit(PhysEntity* other) override = 0;
	virtual bool WasHit() = 0;

	virtual bool DoublePoints() = 0;
	virtual float DoublePointsTimer() = 0;

	virtual bool IsAnimating() = 0;

	virtual float Accuracy() = 0;

	virtual void Accelerate(bool forward) = 0;
	virtual void Turn(bool clockwise) = 0;
	virtual void Fire() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;
};

#endif