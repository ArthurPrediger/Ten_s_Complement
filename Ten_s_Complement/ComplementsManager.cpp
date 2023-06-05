#include "ComplementsManager.h"
#include "World.h"
#include "Player.h"
#include <algorithm>

ComplementsManager::ComplementsManager(World* world, Player* player)
	:
	world_(world),
	player_(player),
	spawn_rate_(2.5f),
	time_since_last_spawn_(0.0f),
	rnd_gen_(),
	complements_dist_(1, 9),
	location_dist_(1, world_->GetExtent().x - 2)
{
	std::random_device rd;
	rnd_gen_.seed(rd());
}

int ComplementsManager::UpdateComplementsLifetime(float dt)
{
	time_since_last_spawn_ += dt;

	if (time_since_last_spawn_ >= spawn_rate_)
	{
		time_since_last_spawn_ = 0.0f;
		complements.emplace_back(Location2D{ location_dist_(rnd_gen_), 0 }, complements_dist_(rnd_gen_));
	}

	int points = 0;

	for (auto& complement : complements)
	{
		complement.time_since_last_update_ += dt;

		if (complement.time_since_last_update_ > complement.update_rate_)
		{
			complement.time_since_last_update_ = 0.0f;

			const Location2D extent = world_->GetExtent();

			int prevArrayLocation = complement.loc_.y * extent.x + complement.loc_.x;

			std::string& world_content = world_->GetContentRef();
			if (world_content[prevArrayLocation] == complement.number_ + char('0'))
				world_content[prevArrayLocation] = ' ';

			complement.loc_.y += 1;

			if (complement.loc_ == player_->GetLocation())
			{
				complement.dirty_ = true;
				points = (complement.number_ + player_->GetNumber() == 10) ? complement.number_ : 0;
			}
			else if (complement.loc_.y >= extent.y - 1)
			{
				complement.dirty_ = true;
			}
			else
			{
				int curArrayLocation = complement.loc_.y * extent.x + complement.loc_.x;

				world_content[curArrayLocation] = complement.number_ + char('0');
			}
		}
	}

	auto new_end = std::remove_if(complements.begin(), complements.end(), [](const Complement& c) { return c.dirty_; });
	complements.erase(new_end, complements.end());

	return points;
}
