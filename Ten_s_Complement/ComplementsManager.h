#pragma once

#include "Location2D.h"
#include <vector>
#include <random>

class World;
class GameStatus;
class Player;

class ComplementsManager
{
public:
	ComplementsManager(World* world, GameStatus* game_status, Player* player);

	void UpdateComplementsLifetime(float dt);

private:
	struct Complement
	{
		Location2D loc_;
		char number_;
		constexpr static float update_rate_ = 0.5f;
		float time_since_last_update_;
		bool dirty_ = false;
	};

private:
	World* world_;
	GameStatus* game_status_;
	Player* player_;
	std::vector<Complement> complements;
	float spawn_rate_;
	float time_since_last_spawn_;

	std::mt19937 rnd_gen_;
	std::uniform_int_distribution<int> complements_dist_;
	std::uniform_int_distribution<int> location_dist_;
};