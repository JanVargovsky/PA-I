#include "Renderer.h"
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>

void Renderer::Render(Board & board, int generation, int time)
{
	system("cls");
	std::stringstream ss;

	ss << "Generation: " << generation << ", Render Time: " << time << "ns" << std::endl;


	for (int y = 0; y < board.GetHeight(); y++)
	{
		for (int x = 0; x < board.GetWidth(); x++)
			ss << (board.Get(x, y) == Alive ? 'x' : ' ');
		ss << std::endl;
	}

	std::cout << ss.str();
}
