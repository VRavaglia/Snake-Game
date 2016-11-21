#include <windows.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "snake_parts.h"
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "MainGame.h"




int main(int argc, char *args[])
{
	MainGame main_game;

	main_game.run();

	return 0;
}




