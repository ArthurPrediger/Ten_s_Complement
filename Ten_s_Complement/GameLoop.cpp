#include "GameLoop.h"
#include "World.h"
#include "Player.h"
#include "ComplementsManager.h"
#include "ScoreCounter.h"
#include "WinInclude.h"
#include "Timer.h"
#include <iostream>
#include <chrono>
#include <thread>

GameLoop::GameLoop()
	:
	world_(std::make_unique<World>(Location2D{ 17, 17 })),
	player_(std::make_unique<Player>(Location2D{ 8, 15 }, world_.get())),
	comps_manager_(std::make_unique<ComplementsManager>(world_.get(), player_.get())),
	score_counter_(std::make_unique<ScoreCounter>())
{
}

GameLoop::~GameLoop()
{
}

void GameLoop::Run()
{
	player_->UpdateWorldLocation({ 0, 0 });

	Timer timer{};

	while (true)
	{
		world_->Draw();
		score_counter_->Draw();

		Location2D displacement = { 0, 0 };
		int player_number = player_->GetNumber();

		if (GetAsyncKeyState('A') & 0x8000) {
			displacement.x = -1;
		}
		else if (GetAsyncKeyState('D') & 0x8000) {
			displacement.x = 1;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if(++player_number > 9) player_number = 1;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (--player_number < 1) player_number = 9;
		}
		else if (GetAsyncKeyState('1') & 0x8000) {
			player_number = 1;
		}
		else if (GetAsyncKeyState('2') & 0x8000) {
			player_number = 2;
		}
		else if (GetAsyncKeyState('3') & 0x8000) {
			player_number = 3;
		}
		else if (GetAsyncKeyState('4') & 0x8000) {
			player_number = 4;
		}
		else if (GetAsyncKeyState('5') & 0x8000) {
			player_number = 5;
		}
		else if (GetAsyncKeyState('6') & 0x8000) {
			player_number = 6;
		}
		else if (GetAsyncKeyState('7') & 0x8000) {
			player_number = 7;
		}
		else if (GetAsyncKeyState('8') & 0x8000) {
			player_number = 8;
		}
		else if (GetAsyncKeyState('9') & 0x8000) {
			player_number = 9;
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			return;
		}

		player_->SetNumber(player_number);
		player_->UpdateWorldLocation(displacement);
		int value = comps_manager_->UpdateComplementsLifetime(timer.Tick());
		score_counter_->AddToScore(value);

		using namespace std::chrono_literals;
		std::this_thread::sleep_for(16.667ms);

		std::system("cls");
	}
}
