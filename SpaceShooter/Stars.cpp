#include "Stars.h"

Stars::Stars()
{
	mTimer = Timer::Instance();

	for (int i = 0; i < TOTAL_STARS; i++)
	{
		mStars.push_back(new AnimatedTexture("star.png", 25, 0, 25, 24, 4, 0.5f, AnimatedTexture::ANIM_DIR::horizontal));
		mStars[i]->Pos(Vector2(rand() % Graphics::SCREEN_WIDTH, rand() % Graphics::SCREEN_HEIGHT));
		mStars[i]->Scale(Vector2(0.25f, 0.25f));
	}

	mPaused = true;
}

Stars::~Stars()
{
	mTimer = nullptr;

	for (int i = 0; i < mStars.size(); i++)
	{
		delete mStars[i];
		mStars[i] = nullptr;
	}

	mStars.clear();
}

void Stars::Pause()
{
	mPaused = true;
}

void Stars::Start()
{
	mPaused = false;
}

void Stars::Scroll()
{
	int starsOnSameLine = 0;

	for (int i = 0; i < mStars.size(); i++)
	{
		mStars[i]->Translate(-(VEC2_UP * SCROLL_SPEED * mTimer->DeltaTime()));

		if (mStars[i]->Pos().y >= Graphics::SCREEN_HEIGHT)
			mStars[i]->Pos(Vector2(rand() % Graphics::SCREEN_WIDTH, 0.0f));

		if (mStars[i]->Pos().y == 0.0f)
			starsOnSameLine++;
	}

	if (starsOnSameLine > TOTAL_STARS / 10)
	{
		for (int i = 0; i < mStars.size(); i++)
			mStars[i]->Pos(Vector2(rand() % Graphics::SCREEN_WIDTH, rand() % Graphics::SCREEN_HEIGHT));
	}

}

void Stars::Update()
{
	if(!mPaused)
		Scroll();

	for (int i = 0; i < mStars.size(); i++)
	{
		if (rand() % 2)
			mStars[i]->Update();
	}
}

void Stars::Render()
{
	for (int i = 0; i < mStars.size(); i++)
		mStars[i]->Render();
}