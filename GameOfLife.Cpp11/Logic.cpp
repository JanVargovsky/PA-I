#include "Logic.h"


CellState Logic::NextState(int x, int y, Board & board)
{
	int liveNeighboursCount = board.GetLiveNeighbors(x, y);
	CellState state = board.Get(x, y);

	if (IsRule1(liveNeighboursCount, state)) return Dead;
	if (IsRule2(liveNeighboursCount, state)) return Alive;
	if (IsRule3(liveNeighboursCount, state)) return Dead;
	if (IsRule4(liveNeighboursCount, state)) return Alive;
	return state;
}

// 1. Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
bool Logic::IsRule1(int liveNeighbours, CellState state)
{
	return state == Alive && liveNeighbours < 2;
}

// 2. Any live cell with two or three live neighbours lives on to the next generation.
bool Logic::IsRule2(int liveNeighbours, CellState state)
{
	return state == Alive && (liveNeighbours == 2 || liveNeighbours == 3);
}

// 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
bool Logic::IsRule3(int liveNeighbours, CellState state)
{
	return state == Alive && liveNeighbours > 3;
}

// 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
bool Logic::IsRule4(int liveNeighbours, CellState state)
{
	return state == Dead && liveNeighbours == 3;
}
