#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Texture.h"
#include <vector>

class Scoreboard : public GameEntity
{
public:
	Scoreboard();
	~Scoreboard();

private:
	std::vector<Texture*> mScore;

	bool mTime;
	bool mPercentage;

	void ClearBoard();
public:
	void Time(bool time);
	void Percentage(bool percentage);

	void Score(int score);

	void Render();
};

#endif