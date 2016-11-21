#include "Errors.h"
#include <iostream>
#include <SDL/SDL.h>

void fatal_error(std::string error_string)
{
	std::cout << error_string << std::endl;
	std::cout << "Enter any key to quit" << std::endl;
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(1);
}