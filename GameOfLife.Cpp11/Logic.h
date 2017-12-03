#pragma once
#include "Board.h"

class Logic
{
public:
	CellState NextState(int x, int y, Board &board);

private:
	bool IsRule1(int liveNeighbours, CellState state);
	bool IsRule2(int liveNeighbours, CellState state);
	bool IsRule3(int liveNeighbours, CellState state);
	bool IsRule4(int liveNeighbours, CellState state);
};

