#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Sprite.h"

enum class GameState {PLAY, PAUSE, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();
	
	void run();

private:
	void init_systems();
	void game_loop();
	void process_input();
	void draw_game();

	SDL_Window* _window;
	int _screen_width;
	int _screen_height;
	GameState _game_state;

	Sprite _sprite;
};

