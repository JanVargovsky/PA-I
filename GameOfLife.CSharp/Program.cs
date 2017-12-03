using System;

namespace GameOfLife.CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            Game game = new Game(Console.WindowWidth - 1, Console.WindowHeight - 3);
            game.Run();
        }
    }
}
