#pragma once

class ScoreCounter
{
public:
	ScoreCounter() = default;

	void Draw() const;
	void AddToScore(int value);
private:
	int score_ = 0;
};