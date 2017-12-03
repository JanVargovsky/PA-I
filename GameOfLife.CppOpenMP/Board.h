#pragma once

enum CellState
{
	Dead,
	Alive,
};

class Board
{
public:
	Board(int width, int height);
	~Board();

	int GetWidth();
	int GetHeight();

	int Board::GetLiveNeighbors(int x, int y);
	CellState Get(int x, int y);
	Board& Set(int x, int y, CellState state);

private:
	bool IsInRange(int x, int y);
	CellState* cells;
	int width, height;
};

