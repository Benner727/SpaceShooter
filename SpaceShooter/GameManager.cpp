#include "GameManager.h"

GameManager* GameManager::sInstance = nullptr;

GameManager* GameManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new GameManager();

	return sInstance;
}

void GameManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

GameManager::GameManager()
{
	mQuit = false;

	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized())
		mQuit = true;

	mAssetManager = AssetManager::Instance();

	mInputManager = InputManager::Instance();

	mAudioManager = AudioManager::Instance();

	mTimer = Timer::Instance();

	mPhysicsManager = PhysicsManager::Instance();
	mPhysicsManager->SetLayerCollisionMask(PhysEntity::CollisionLayers::Friendly, PhysEntity::CollisionFlags::Hostile | PhysEntity::CollisionFlags::HostileProjectiles | PhysEntity::CollisionFlags::Meteor | PhysEntity::CollisionFlags::PowerUp);
	mPhysicsManager->SetLayerCollisionMask(PhysEntity::CollisionLayers::FriendlyProjectiles, PhysEntity::CollisionFlags::Hostile | PhysEntity::CollisionFlags::Meteor);
	mPhysicsManager->SetLayerCollisionMask(PhysEntity::CollisionLayers::Hostile, PhysEntity::CollisionFlags::Friendly | PhysEntity::CollisionFlags::FriendlyProjectiles);
	mPhysicsManager->SetLayerCollisionMask(PhysEntity::CollisionLayers::HostileProjectiles, PhysEntity::CollisionFlags::Friendly);
	mPhysicsManager->SetLayerCollisionMask(PhysEntity::CollisionLayers::Meteor, PhysEntity::CollisionFlags::Friendly | PhysEntity::CollisionFlags::FriendlyProjectiles | PhysEntity::CollisionFlags::Meteor);
	mPhysicsManager->SetLayerCollisionMask(PhysEntity::CollisionLayers::PowerUp, PhysEntity::CollisionFlags::Friendly);

	mScreenManager = ScreenManager::Instance();

	srand(time(nullptr));
}


GameManager::~GameManager()
{
	ScreenManager::Release();
	mScreenManager = nullptr;

	PhysicsManager::Release();
	mPhysicsManager = nullptr;

	AudioManager::Release();
	mAudioManager = nullptr;

	AssetManager::Release();
	mAssetManager = nullptr;

	Graphics::Release();
	mGraphics = nullptr;

	InputManager::Release();
	mInputManager = nullptr;

	Timer::Release();
	mTimer = nullptr;
	
}

void GameManager::EarlyUpdate()
{
	mInputManager->Update();
}

void GameManager::Update()
{
	mScreenManager->Update();
}

void GameManager::LateUpdate()
{
	mPhysicsManager->Update();
	mInputManager->UpdatePrevInput();

	mTimer->Reset();
}

void GameManager::Render()
{
	mGraphics->ClearBackBuffer();

	//Render here
	mScreenManager->Render();

	mGraphics->Render();
}

void GameManager::Run()
{
	while (!mQuit)
	{
		mTimer->Update();

		while (SDL_PollEvent(&mEvent) != 0)
		{
			if (mEvent.type == SDL_QUIT)
				mQuit = true;
		}

		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
		{
			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}
	}
}