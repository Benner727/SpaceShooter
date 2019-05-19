#include "ShipSelection.h"


ShipSelection::ShipSelection()
{
	mTimer = Timer::Instance();;
	mInputManager = InputManager::Instance();

	mShipOptions = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mTitle = new Texture("Choose your ship", "kenvector_future.ttf", 48, { 222, 83, 44 });
	mWaspIcon = new Texture("Ships/playerShip3_green.png");
	mWaspText = new Texture("Wasp", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mRaiderIcon = new Texture("Ships/playerShip1_red.png");
	mRaiderText = new Texture("Raider", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mFighterIcon = new Texture("Ships/playerShip2_blue.png");
	mFighterText = new Texture("Hyperion", "kenvector_future.ttf", 32, { 245, 245, 245 });
	mCursor = new Texture("cursor.png");
	
	mTitle->Parent(mShipOptions);
	mWaspIcon->Parent(mShipOptions);
	mWaspText->Parent(mShipOptions);
	mRaiderIcon->Parent(mShipOptions);
	mRaiderText->Parent(mShipOptions);
	mFighterIcon->Parent(mShipOptions);
	mFighterText->Parent(mShipOptions);
	mCursor->Parent(mShipOptions);
	mShipOptions->Parent(this);

	mTitle->Pos(Vector2(0.0f, -175.0f));
	mWaspIcon->Pos(Vector2(-250.0f, -15.0f));
	mWaspText->Pos(Vector2(-250.0f, 45.0f));
	mRaiderIcon->Pos(Vector2(0.0f, -15.0f));
	mRaiderText->Pos(Vector2(0.0f, 45.0f));
	mFighterIcon->Pos(Vector2(250.0f, -15.0f));
	mFighterText->Pos(Vector2(250.0f, 45.0f));
	mCursor->Pos(Vector2(0.0f, 100.0f));

	mCursorLeftPos = Vector2(-250.0f, 100.0f);
	mCursorOffset = Vector2(250.0f, 0.0f);
	mSelectedOption = 1;

	mEscape = new Texture("Press 'ESCAPE' to return to start screen.", "kenvector_future.ttf", 32, { 80, 80, 80 });
	mEscape->Parent(this);
	mEscape->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT * 0.95f));

	mEscapeBlinkTimer = 0.0f;
	mEscapeBlinkInterval = 0.5f;
	mEscapeVisible = true;
}


ShipSelection::~ShipSelection()
{
	mTimer = nullptr;
	mInputManager = nullptr;

	delete mTitle;
	mTitle = nullptr;

	delete mWaspIcon;
	mWaspIcon = nullptr;

	delete mWaspText;
	mWaspText = nullptr;

	delete mRaiderIcon;
	mRaiderIcon = nullptr;

	delete mRaiderText;
	mRaiderText = nullptr;

	delete mFighterIcon;
	mFighterIcon = nullptr;

	delete mFighterText;
	mFighterText = nullptr;
	
	delete mCursor;
	mCursor = nullptr;

	delete mShipOptions;
	mShipOptions = nullptr;

	delete mEscape;
	mEscape = nullptr;
}

int ShipSelection::SelectedOption()
{
	return mSelectedOption;
}

void ShipSelection::ChangeSelectedOption(int change)
{
	mSelectedOption += change;

	if (mSelectedOption < 0)
		mSelectedOption = 2;
	else if (mSelectedOption > 2)
		mSelectedOption = 0;

	mCursor->Pos(mCursorLeftPos + mCursorOffset * mSelectedOption);
}

void ShipSelection::Update()
{
	if (mInputManager->KeyPressed(SDL_SCANCODE_LEFT))
		ChangeSelectedOption(-1);
	else if (mInputManager->KeyPressed(SDL_SCANCODE_RIGHT))
		ChangeSelectedOption(1);

	mEscapeBlinkTimer += mTimer->DeltaTime();
	if (mEscapeBlinkTimer >= mEscapeBlinkInterval)
	{
		mEscapeVisible = !mEscapeVisible;
		mEscapeBlinkTimer = 0.0f;
	}
}

void ShipSelection::Render()
{
	mTitle->Render();
	mWaspIcon->Render();
	mWaspText->Render();
	mRaiderIcon->Render();
	mRaiderText->Render();
	mFighterIcon->Render();
	mFighterText->Render();
	mCursor->Render();

	if(mEscapeVisible)
		mEscape->Render();
}