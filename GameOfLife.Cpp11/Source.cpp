#include "Board.h"
#include "Renderer.h";
#include "Game.h";

int main()
{
	Renderer r;
	Logic l;
	Game g = Game(79, 19, r, l);
	g.Run();
	return 0;
}