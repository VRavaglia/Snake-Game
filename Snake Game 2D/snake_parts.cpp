#include "snake_parts.h"


snake_parts::snake_parts() 
{
	x = 0;
	y = 0;
}

snake_parts::snake_parts(int n_x_coordinate, int n_y_coordinate, char n_appearence)
{
	x = n_x_coordinate;
	y = n_y_coordinate;
	appearence = n_appearence;
}

snake_parts::~snake_parts()
{

}