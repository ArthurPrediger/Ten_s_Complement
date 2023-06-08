#pragma once

class GameStatus
{
public:
	GameStatus() = default;

	void Draw() const;
	void AddToScore(int value);
	void AddToScoreLost(int value);
	void PlayerLifesMinusOne();
	bool IsGameOver();
private:
	int score_ = 0;
	int score_lost_ = 0;
	int player_lifes_ = 3;
};