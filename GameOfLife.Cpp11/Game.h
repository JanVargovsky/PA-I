#pragma once
#include "Board.h";
#include "Renderer.h";
#include "Logic.h";

class Game
{
public:
	Game(int width, int height, Renderer &renderer, Logic &logic);
	~Game();

	void Run();

private:
	Board *board;
	Renderer &renderer;
	Logic &logic;

	Board* NextGeneration();
	//static void NextGeneration(Board &board, Logic &logic, int from, int to);
};

