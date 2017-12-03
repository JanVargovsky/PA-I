#include "Board.h"

Board::Board(int width, int height) :
	width(width), height(height)
{
	cells = new CellState[width * height]{};
}

Board::~Board()
{
	delete cells;
}

int Board::GetWidth()
{
	return width;
}

int Board::GetHeight()
{
	return height;
}

int Board::GetLiveNeighbors(int x, int y)
{
	int liveNeighbors = 0;

	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i == x && j == y)
				continue;

			if (IsInRange(i, j) && Get(i, j) == Alive)
				liveNeighbors++;
		}

	return liveNeighbors;
}

CellState Board::Get(int x, int y)
{
	return cells[y * width + x];
}

Board& Board::Set(int x, int y, CellState state)
{
	cells[y * width + x] = state;
	return *this;
}

bool Board::IsInRange(int x, int y)
{
	return x >= 0 &&
		y >= 0 &&
		x < width &&
		y < height;
}
