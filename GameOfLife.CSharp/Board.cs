using System.Collections.Generic;

namespace GameOfLife.CSharp
{
    public enum CellState
    {
        Dead,
        Alive,
    }

    public class Board
    {
        readonly CellState[] cells;
        public int Width { get; }
        public int Height { get; }

        public Board(int width, int height)
        {
            cells = new CellState[width * height];
            Width = width;
            Height = height;
        }

        public CellState this[int x, int y]
        {
            get => cells[y * Width + x];
            set => cells[y * Width + x] = value;
        }

        bool IsInRange(int x, int y) =>
            x >= 0 &&
            y >= 0 &&
            x < Width &&
            y < Height;

        public IEnumerable<CellState> GetNeighbors(int x, int y)
        {
            for (int i = x - 1; i <= x + 1; i++)
                for (int j = y - 1; j <= y + 1; j++)
                {
                    if (i == x && j == y)
                        continue;

                    if (IsInRange(i, j))
                        yield return this[i, j];
                }
        }
    }
}
