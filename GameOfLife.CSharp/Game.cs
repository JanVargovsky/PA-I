using System;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;

namespace GameOfLife.CSharp
{
    public class Game
    {
        Board board;
        readonly Logic logic;
        readonly Renderer renderer;
        int generation = 0;

        public Game(int width, int height)
        {
            board = new Board(width, height);
            logic = new Logic();
            renderer = new Renderer();
            InitialSeed();
        }

        void InitialSeed()
        {
            void VertialBlinker(int x, int y)
            {
                board[x, y] = board[x, y + 1] = board[x, y + 2] = CellState.Alive;
            }

            void HorizontalBlinker(int x, int y)
            {
                board[x, y] = board[x + 1, y] = board[x + 2, y] = CellState.Alive;
            }

            void Block(int x, int y)
            {
                board[x, y] = board[x + 1, y] = board[x, y + 1] = board[x + 1, y + 1] = CellState.Alive;
            }

            void Beacon(int x, int y)
            {
                Block(x, y);
                Block(x + 2, y + 2);
            }

            Random r = new Random();

            int SafeX() => r.Next(board.Width - 3);
            int SafeY() => r.Next(board.Height - 3);

            for (int i = 0; i < 4; i++)
            {
                VertialBlinker(SafeX(), SafeY());
                HorizontalBlinker(SafeX(), SafeY());
                Block(SafeX(), SafeY());
                Beacon(SafeX(), SafeY());
            }
        }

        Board NextGeneration(out TimeSpan renderTime)
        {
            Board b = new Board(board.Width, board.Height);

            var sw = Stopwatch.StartNew();

            //for (int x = 0; x < board.Width; x++)
            //    for (int y = 0; y < board.Height; y++)
            //        b[x, y] = logic.NextState(x, y, board);

            Parallel.For(0, board.Height, y =>
            {
                Parallel.For(0, board.Width, x =>
                {
                    b[x, y] = logic.NextState(x, y, board);
                });
            });

            sw.Stop();
            renderTime = sw.Elapsed;

            return b;
        }

        public void Run()
        {
            TimeSpan renderTime = TimeSpan.Zero;
            do
            {
                renderer.Render(board, generation++, renderTime);

                board = NextGeneration(out renderTime);
                Thread.Sleep(500);
            } while (true);
            //} while (Console.ReadKey(true).Key != ConsoleKey.Q);
        }
    }
}
