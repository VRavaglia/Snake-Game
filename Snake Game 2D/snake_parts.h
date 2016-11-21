#include <iostream>
using namespace std;


#ifndef SNAKE_PARTS_H

#define SNAKE_PARTS_H

	class snake_parts
	{
	public:
		//default consntructor
		snake_parts();
		//overload constructor
		snake_parts(int, int, char);
		//destructor
		~snake_parts();
		//variables
		int x;
		int y;
		char appearence;

	private:
		
	};


#endif
