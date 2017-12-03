using System;
using System.Text;

namespace GameOfLife.CSharp
{
    public class Renderer
    {
        public void Render(Board board, int generation, TimeSpan renderTime)
        {
            Console.Clear();
            var sb = new StringBuilder();

            for (int y = 0; y < board.Height; y++)
            {
                for (int x = 0; x < board.Width; x++)
                    Render(sb, board[x, y]);

                sb.AppendLine();
            }

            Console.WriteLine($"Generation: {generation}, Render Time: {renderTime.TotalMilliseconds}ms");
            Console.WriteLine(sb);
        }

        void Render(StringBuilder sb, CellState cell)
        {
            char c = cell == CellState.Alive ? 'x' : ' ';
            sb.Append(c);
        }
    }
}
