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

void NextGenerationInterval(Board *board, Board *newBoard, Logic &logic, int from, int to)
{
	for (int i = from; i < to; i++)
	{
		int x = i % board->GetWidth();
		int y = i / board->GetWidth();
		newBoard->Set(x, y, logic.NextState(x, y, *board));
	}
}

Board * Game::NextGeneration()
{
	auto b = new Board(board->GetWidth(), board->GetHeight());
	const int NumberOfThreads = 4;
	std::thread threads[NumberOfThreads];
	int chuckSize = (board->GetWidth() * board->GetHeight()) / NumberOfThreads;

	for (int i = 0; i < NumberOfThreads; i++)
		threads[i] = std::thread(NextGenerationInterval, board, b, logic, i * chuckSize, (i + 1) * chuckSize);

	for (int i = 0; i < NumberOfThreads; i++)
		threads[i].join();

	return b;
}