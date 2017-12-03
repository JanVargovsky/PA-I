#include "Game.h"
#include <thread>
#include <thread>
#include <chrono>
#include <ctime>

Game::Game(int width, int height, Renderer &renderer, Logic &logic)
	:renderer(renderer), logic(logic)
{
	board = new Board(width, height);

	srand(42);
	for (int i = 0; i < 200; i++)
	{
		int x = rand() % width;
		int y = rand() % height;
		board->Set(x, y, Alive);
	}
}

Game::~Game()
{
	delete board;
}

void Game::Run()
{
	int generation = 0;
	int nextGenerationTime = 0;
	do
	{
		renderer.Render(*board, generation++, nextGenerationTime);
		auto begin = clock();
		auto newBoard = NextGeneration();
		auto end = clock();
		nextGenerationTime = double(end - begin);
		delete board;
		board = nullptr;
		board = newBoard;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	} while (true);
}

Board * Game::NextGeneration()
{
	auto b = new Board(board->GetWidth(), board->GetHeight());

#pragma omp parallel for
	for (int x = 0; x < b->GetWidth(); x++)
#pragma omp parallel for
		for (int y = 0; y < b->GetHeight(); y++)
			b->Set(x, y, logic.NextState(x, y, *board));

	return b;
}