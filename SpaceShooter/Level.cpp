#include "Level.h"

Level::Level(PlayTopBar* topBar, Player* player)
{
	mTimer = Timer::Instance();

	mLevelTimer = 0.0f;
	mMeteorTimer = 0.0f;

	mTopBar = topBar;

	mPlayer = player;
	mPlayerHit = false;
	mPlayerRespawnDelay = 3.0f;
	mPlayerRespawnTimer = 0.0f;

	mRespawnLabel = new Texture("RESPAWNING", "kenvector_future.ttf", 42, { 34, 34, 178 });
	mRespawnLabel->Parent(this);
	mRespawnLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5, Graphics::Instance()->SCREEN_HEIGHT * 0.5));
	mRespawnLabelOnScreen = 2.0f;

	mGameOverLabel = new Texture("GAME OVER", "kenvector_future.ttf", 42, { 178, 34, 34 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5, Graphics::Instance()->SCREEN_HEIGHT * 0.5));

	mGameOver = false;
	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = running;
}

Level::~Level()
{
	mTimer = nullptr;

	mTopBar = nullptr;

	mPlayer = nullptr;

	delete mRespawnLabel;
	mRespawnLabel = nullptr;

	delete mGameOverLabel;
	mGameOverLabel = nullptr;

	ClearMeteors();
	ClearPowerUps();
}

void Level::HandleCollision()
{
	if (!mPlayerHit)
	{
		if (mPlayer->WasHit())
		{
			mPlayer->Died();
			mTopBar->Lives(mPlayer->Lives());

			mPlayerHit = true;
			mPlayerRespawnTimer = 0.0f;
			mPlayer->Active(false);
		}
	}
}

void Level::HandlePlayerDeath()
{
	if (!mPlayer->IsAnimating())
	{
		if (mPlayer->Lives() > 0)
		{
			mPlayerRespawnTimer += mTimer->DeltaTime();

			if (mPlayerRespawnTimer >= mPlayerRespawnDelay)
			{
				mPlayer->Active(true);
				mPlayer->Visible(true);
				mPlayerHit = false;
				mPlayer->Reset();
			}
		}
		else
		{
			if (mGameOverTimer == 0.0f)
				mPlayer->Visible(false);

			mGameOverTimer += mTimer->DeltaTime();

			if (mGameOverTimer >= mGameOverDelay)
			{
				ClearMeteors();
				ClearPowerUps();
				mCurrentState = gameover;		
			}
		}
	}
}

void Level::ClearMeteors()
{
	for (int i = 0; i < mMeteors.size(); i++)
	{
		delete mMeteors[i];
		mMeteors[i] = nullptr;
	}

	mMeteors.clear();
}

void Level::HandleMeteorSpawning()
{
	int hugeMeteors = 0;

	if (mMeteors.size())
	{
		for (int i = 0; i < mMeteors.size(); i++)
		{
			if (mMeteors[i]->Size() == Meteor::huge)
				hugeMeteors++;
		}
	}

	/*
	if (hugeMeteors < 1)
	{
		switch (rand() % 5)
		{
		case 0:
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(-150.0f, -150.0f))); //Top Left
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(Graphics::SCREEN_WIDTH + 200.0f, Graphics::SCREEN_HEIGHT * 0.5f))); //Middle Right
			break;
		case 1:
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(Graphics::SCREEN_WIDTH + 150.0f, -150.0f))); //Top Right
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT + 200.0f))); //Bottom Middle
			break;
		case 2:
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(-200.0f, Graphics::SCREEN_HEIGHT + 200.0f))); //Bottom Left
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(Graphics::SCREEN_WIDTH + 200.0f, Graphics::SCREEN_HEIGHT + 200.0f))); //Bottom Right
			break;
		case 3:
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(Graphics::SCREEN_WIDTH + 200.0f, Graphics::SCREEN_HEIGHT + 200.0f))); //Bottom Right
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(-150.0f, -150.0f))); //Top Left
			break;
		case 4:
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(Graphics::SCREEN_WIDTH * 0.5f, -200.0f))); //Top Middle
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(-200.0f, Graphics::SCREEN_HEIGHT * 0.5f))); //Middle Left
			break;
		}
	}
	*/
	
	if((mMeteorTimer >= 5.0f || hugeMeteors < 1) && hugeMeteors < 3)
	{
		switch (rand() % 7)
		{
		case 0:
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(-150.0f, -150.0f))); //Top Left
			break;
		case 1:
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(Graphics::SCREEN_WIDTH + 150.0f, -150.0f))); //Top Right
			break;
		case 2:
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(Graphics::SCREEN_WIDTH * 0.5f, -200.0f))); //Top Middle
			break;
		case 3:
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(Graphics::SCREEN_WIDTH * 0.33f, -200.0f))); //Top Middle Left
			break;
		case 4:
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(Graphics::SCREEN_WIDTH * 0.66f, -150.0f))); //Top Middle Right
			break;
		case 5:
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(-150.0f, Graphics::SCREEN_HEIGHT * 0.2))); //Middle Top Left
			break;
		case 6:
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(Graphics::SCREEN_WIDTH + 150.0f, Graphics::SCREEN_HEIGHT * 0.2))); //Middle Top Right
			break;
		default:
			mMeteors.push_back(new Meteor(Meteor::SIZE::huge, Vector2(Graphics::SCREEN_WIDTH * 0.5f, -200.0f))); //Top Middle
		}

		mMeteorTimer = 0.0f; //Reset timer for last spawn
	}
}

void Level::HandleScoring(int i)
{
	if (mMeteors[i]->WasShot())
	{
		if (mPlayer->Active())
		{
			switch (mMeteors[i]->Size())
			{
			case Meteor::huge:
				mPlayer->AddScore(10);
				mPlayer->MeteorDesroyed((int)Meteor::huge);
				break;
			case Meteor::big:
				mPlayer->AddScore(25);
				mPlayer->MeteorDesroyed((int)Meteor::big);
				break;
			case Meteor::med:
				mPlayer->AddScore(50);
				mPlayer->MeteorDesroyed((int)Meteor::med);
				break;
			case Meteor::small:
				mPlayer->AddScore(75);
				mPlayer->MeteorDesroyed((int)Meteor::small);
				break;
			case Meteor::tiny:
				mPlayer->AddScore(100);
				mPlayer->MeteorDesroyed((int)Meteor::tiny);
				break;
			}

			mTopBar->Score(mPlayer->Score());
		}
	}
}

void Level::HandleMeteorCollision()
{
	for (int i = 0; i < mMeteors.size(); i++)
	{
		if (mMeteors[i]->WasHit())
		{
			HandleScoring(i);

			if (mMeteors.size() < MAX_METEORS)
			{
				switch (mMeteors[i]->Size())
				{
				case Meteor::huge:
					mMeteors.push_back(new Meteor(Meteor::SIZE::big, mMeteors[i]->Pos() + (RotateVector(mMeteors[i]->Direction(), 90.0f) * 60.0f), RotateVector(mMeteors[i]->Direction(), rand() % 10 + 5)));
					mMeteors.push_back(new Meteor(Meteor::SIZE::big, mMeteors[i]->Pos() - (RotateVector(mMeteors[i]->Direction(), 90.0f) * 60.0f), RotateVector(mMeteors[i]->Direction(), -(rand() % 10 + 5))));
					break;
				case Meteor::big:
					if (rand() % 4)
					{
						mMeteors.push_back(new Meteor(Meteor::SIZE::med, mMeteors[i]->Pos() + (RotateVector(mMeteors[i]->Direction(), 90.0f) * 35.0f), RotateVector(mMeteors[i]->Direction(), rand() % 10 + 5)));
						mMeteors.push_back(new Meteor(Meteor::SIZE::med, mMeteors[i]->Pos() - (RotateVector(mMeteors[i]->Direction(), 90.0f) * 35.0f), RotateVector(mMeteors[i]->Direction(), -(rand() % 10 + 5))));
					}
					else
						mMeteors.push_back(new Meteor(Meteor::SIZE::med, mMeteors[i]->Pos(), mMeteors[i]->Direction()));
					break;
				case Meteor::med:
					if (!mMeteors[i]->WasCrashed()) //Stop medium meteors from instantly doing 3-5 damage to player ship upon collision
					{
						if (rand() % 3)
						{
							mMeteors.push_back(new Meteor(Meteor::SIZE::small, mMeteors[i]->Pos() + (RotateVector(mMeteors[i]->Direction(), 90.0f) * 25.0f), RotateVector(mMeteors[i]->Direction(), rand() % 10 + 5)));
							mMeteors.push_back(new Meteor(Meteor::SIZE::small, mMeteors[i]->Pos() - (RotateVector(mMeteors[i]->Direction(), 90.0f) * 25.0f), RotateVector(mMeteors[i]->Direction(), -(rand() % 10 + 5))));
						}
						else
							mMeteors.push_back(new Meteor(Meteor::SIZE::small, mMeteors[i]->Pos(), mMeteors[i]->Direction()));
					}
					break;
				case Meteor::small:
					if (!mMeteors[i]->WasCrashed()) //Stop small meteors from instantly doing 2-3 damage to player ship upon collision
					{
						if (rand() % 2)
						{
							mMeteors.push_back(new Meteor(Meteor::SIZE::tiny, mMeteors[i]->Pos() + (RotateVector(mMeteors[i]->Direction(), 90.0f) * 15.0f), RotateVector(mMeteors[i]->Direction(), rand() % 10 + 5)));
							mMeteors.push_back(new Meteor(Meteor::SIZE::tiny, mMeteors[i]->Pos() - (RotateVector(mMeteors[i]->Direction(), 90.0f) * 15.0f), RotateVector(mMeteors[i]->Direction(), -(rand() % 10 + 5))));
						}
						else
							mMeteors.push_back(new Meteor(Meteor::SIZE::tiny, mMeteors[i]->Pos(), mMeteors[i]->Direction()));
					}
					break;
				case Meteor::tiny:
					break;
				}
			}
		}
		else if (mMeteors[i]->Dead())
		{
			if (mMeteors[i]->Size() == Meteor::huge)
			{
				if (!(rand() % 5))
					mPowerUps.push_back(new PowerUp(mMeteors[i]->Pos(), mMeteors[i]->Direction(), rand() % 3));
			}

			delete mMeteors[i];
			mMeteors[i] = nullptr;
			mMeteors.erase(mMeteors.begin() + i);
		}
	}
}

void Level::HandleMeteors()
{
	if (mPlayerRespawnTimer >= mPlayerRespawnDelay || !mPlayerRespawnTimer)
		HandleMeteorSpawning();
	
	HandleMeteorCollision();
}

void Level::ClearPowerUps()
{
	for (int i = 0; i < mPowerUps.size(); i++)
	{
		delete mPowerUps[i];
		mPowerUps[i] = nullptr;
	}

	mPowerUps.clear();
}

void Level::HandlePowerUps()
{
	for (int i = 0; i < mPowerUps.size(); i++)
	{
		if (mPowerUps[i]->Dead())
		{
			delete mPowerUps[i];
			mPowerUps[i] = nullptr;
			mPowerUps.erase(mPowerUps.begin() + i);
		}
	}

	mTopBar->DoublePoints(mPlayer->Ship()->DoublePointsTimer());
}

Level::LEVEL_STATES Level::State()
{
	if (mCurrentState == gameover)
	{
		mPlayer->TimeSurvived(mLevelTimer);
	}

	return mCurrentState;
}

void Level::Update()
{
	HandleCollision();
	HandleMeteors();
	HandlePowerUps();

	if (mPlayerHit)
		HandlePlayerDeath();

	for (int i = 0; i < mMeteors.size(); i++)
		mMeteors[i]->Update();

	for (int i = 0; i < mPowerUps.size(); i++)
		mPowerUps[i]->Update();

	mLevelTimer += mTimer->DeltaTime();
	mMeteorTimer += mTimer->DeltaTime();
}

void Level::Render()
{
	for (int i = 0; i < mMeteors.size(); i++)
		mMeteors[i]->Render();

	for (int i = 0; i < mPowerUps.size(); i++)
		mPowerUps[i]->Render();

	if (mPlayerHit)
	{
		if (mPlayerRespawnTimer >= mRespawnLabelOnScreen)
		{
			mRespawnLabel->Render();
			ClearMeteors();
			ClearPowerUps();
		}

		if (mGameOverTimer >= mGameOverLabelOnScreen)
			mGameOverLabel->Render();
	}
}