#include "Scoreboard.h"

Scoreboard::Scoreboard()
{
	mTime = false;
	mPercentage = false;

	Score(0);
}

Scoreboard::~Scoreboard()
{
	ClearBoard();
}

void Scoreboard::ClearBoard()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		delete mScore[i];
		mScore[i] = nullptr;
	}

	mScore.clear();
}

void Scoreboard::Time(bool time)
{
	mTime = time;
}

void Scoreboard::Percentage(bool percentage)
{
	mPercentage = percentage;
}

void Scoreboard::Score(int score)
{
	ClearBoard();

	std::string str = std::to_string(score);

	if (mTime)
	{
		str = std::to_string(score / 60);
		str.push_back('C');

		if (score % 60 < 10)
			str.push_back('0');

		str += std::to_string(score % 60);
	}
	else if (mPercentage)
	{
		str.push_back('P');
	}

	int lastIndex = str.length() - 1;

	for (int i = 0; i <= lastIndex; i++)
	{
		mScore.push_back(new Texture("numeral" + str.substr(i, 1) + ".png"));
		mScore[i]->Parent(this);

		if (i < lastIndex / 2)
			mScore[i]->Pos(Vector2(-20.0f * (lastIndex / 2 - i), 0.0f));
		else
			mScore[i]->Pos(Vector2(20.0f * (i - lastIndex / 2), 0.0f));
	}
}

void Scoreboard::Render()
{
	for (int i = 0; i < mScore.size(); i++)
		mScore[i]->Render();
}