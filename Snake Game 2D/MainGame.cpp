#include "MainGame.h"
#include <iostream>
#include <string>
#include "Errors.h"

MainGame::MainGame()
{
	_window = nullptr;
	_screen_width = 600;
	_screen_height = 800;
	_game_state = GameState::PLAY;
}


MainGame::~MainGame()
{
}

void MainGame::run() 
{
	init_systems();

	_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);

	game_loop();
}

void MainGame::init_systems()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Snake Game 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screen_width, _screen_height, SDL_WINDOW_OPENGL);
	
	if (_window == nullptr)
	{
		fatal_error("Window could not be created!");
	}

	SDL_GLContext gl_context = SDL_GL_CreateContext(_window);
	if (gl_context == nullptr)
	{
		fatal_error("SDL_GL context could not be created!");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatal_error("Could not initialize glew!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void MainGame::game_loop()
{
	while (_game_state != GameState::EXIT)
	{
		process_input();
		draw_game();
	}
}

void MainGame::process_input()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_game_state = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				std::cout << evnt.motion.x << " , " << evnt.motion.y << std::endl;
				break;
		}
	}
}

void MainGame::draw_game()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_sprite.draw();

	SDL_GL_SwapWindow(_window);
}
