#include "GameLoop.h"
#include "World.h"
#include "Player.h"
#include "ComplementsManager.h"
#include "GameStatus.h"
#include "WinInclude.h"
#include "Timer.h"
#include <iostream>
#include <chrono>
#include <thread>

GameLoop::GameLoop()
	:
	world_(std::make_unique<World>(Location2D{ 17, 17 })),
	game_status_(std::make_unique<GameStatus>()),
	player_(std::make_unique<Player>(Location2D{ 8, 15 }, world_.get())),
	comps_manager_(std::make_unique<ComplementsManager>(world_.get(), game_status_.get(), player_.get()))
{
}

GameLoop::~GameLoop()
{
}

void GameLoop::Start()
{
	std::cout << "\n\n\t TEN'S COMPLEMENT \n\n\n\n";
	std::cout << "    Match the numbers in order \n    their sum is equal to ten.\n\n";
	std::cout << "    CONTROLS: \n";
	std::cout << "    A - Move left\n";
	std::cout << "    D - Move right\n";
	std::cout << "    UP - Increase number\n";
	std::cout << "    DOWN - Decrease number\n\n";
	std::cout << "    Press enter to start\n";
	
	while (!(GetAsyncKeyState(VK_RETURN) & 0x8000));

	std::system("cls");

	Run();

	std::system("cls");
	std::cout << "\n\n\tGAME OVER\n\n";
	game_status_->Draw();
	std::cout << "\n\n    Press enter to close\n";

	while (!(GetAsyncKeyState(VK_RETURN) & 0x8000));
}

void GameLoop::Run()
{
	player_->UpdateWorldLocation({ 0, 0 });

	Timer timer{};

	while (!game_status_->IsGameOver())
	{
		world_->Draw();
		game_status_->Draw();

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
		//else if (GetAsyncKeyState('1') & 0x8000) {
		//	player_number = 1;
		//}
		//else if (GetAsyncKeyState('2') & 0x8000) {
		//	player_number = 2;
		//}
		//else if (GetAsyncKeyState('3') & 0x8000) {
		//	player_number = 3;
		//}
		//else if (GetAsyncKeyState('4') & 0x8000) {
		//	player_number = 4;
		//}
		//else if (GetAsyncKeyState('5') & 0x8000) {
		//	player_number = 5;
		//}
		//else if (GetAsyncKeyState('6') & 0x8000) {
		//	player_number = 6;
		//}
		//else if (GetAsyncKeyState('7') & 0x8000) {
		//	player_number = 7;
		//}
		//else if (GetAsyncKeyState('8') & 0x8000) {
		//	player_number = 8;
		//}
		//else if (GetAsyncKeyState('9') & 0x8000) {
		//	player_number = 9;
		//}

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			return;
		}

		player_->SetNumber(player_number);
		player_->UpdateWorldLocation(displacement);
		comps_manager_->UpdateComplementsLifetime(timer.Tick());

		using namespace std::chrono_literals;
		std::this_thread::sleep_for(16.667ms);

		std::system("cls");
	}
}
