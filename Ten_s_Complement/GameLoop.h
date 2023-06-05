#pragma once

#include <memory>

class World;
class Player;
class ComplementsManager;
class ScoreCounter;

class GameLoop
{
public:
	GameLoop();
	~GameLoop();

	void Run();

private:
	std::unique_ptr<World> world_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<ComplementsManager> comps_manager_;
	std::unique_ptr<ScoreCounter> score_counter_;
};