#include "Particle.h"

Particle::Particle(Vector2 pos, Vector2 velocity)
{
	mTimer = Timer::Instance();

	mVelocity = velocity * 0.66f;

	if (std::abs(mVelocity.x) < std::abs(mVelocity.y))
	{
		pos.x -= 10.0f;
		pos.x += (rand() % 20);
		mVelocity.y *= (float)(rand() % 100 / 50.0f);
	}
	else
	{
		pos.y -= 10.0f;
		pos.y += (rand() % 20);
		mVelocity.x *= (float)(rand() % 100 / 50.0f);
	}

	Pos(pos);

	mDead = false;

	mParticleLife = 0.5f + rand() % 10 / 10.0f;
	mParticleTimer = 0.0f;
	mFrameCount = rand() % 2;

	int offset = rand() % 8;

	mLivingTexture = new Texture("Particles.png", 4 * offset, 0, 4, 5);
	mLivingTexture->Scale(Vector2(0.25f, 0.25f));
	mLivingTexture->Parent(this);
	mLivingTexture->Pos(VEC2_ZERO);

	mDyingTexture = new Texture("Particles.png", 4 * 7, 0, 4, 5);
	mDyingTexture->Scale(Vector2(0.25f, 0.25f));
	mDyingTexture->Parent(this);
	mDyingTexture->Pos(VEC2_ZERO);
}

Particle::~Particle()
{
	mTimer = nullptr;

	delete mLivingTexture;
	mLivingTexture = nullptr;

	delete mDyingTexture;
	mDyingTexture = nullptr;
}

bool Particle::Dead()
{
	return mDead;
}

void Particle::Update()
{
	mParticleTimer += mTimer->DeltaTime();

	if (mParticleTimer >= mParticleLife)
		mDead = true;
	else
	{
		mVelocity *= 1.01f;
		Translate(mVelocity * mTimer->DeltaTime(), world);

		if (Pos().x < 0)
			mDead = true;
		else if (Pos().x > Graphics::Instance()->SCREEN_WIDTH)
			mDead = true;
		else if (Pos().y < 0)
			mDead = true;
		else if (Pos().y > Graphics::Instance()->SCREEN_HEIGHT)
			mDead = true;
	}
}

void Particle::Render()
{
	mFrameCount++;

	if (!mDead && (mFrameCount % 2))
	{
		if (mParticleTimer < 0.5f)
			mLivingTexture->Render();
		else
			mDyingTexture->Render();
	}
}