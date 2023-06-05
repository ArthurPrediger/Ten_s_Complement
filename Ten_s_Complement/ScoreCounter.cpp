#include "ScoreCounter.h"
#include <iostream>
#include <format>

void ScoreCounter::Draw() const
{
	std::cout << std::format("\nSCORE: {}\n", score_);
}

void ScoreCounter::AddToScore(int value)
{
	score_ += value;
}
