#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Game engine

class Game
{
private:
	//Window 
	sf::RenderWindow* window_ptr;
	sf::VideoMode video_mode;
	sf::Event event_1;

	//Music
	sf::Music music;

	//Background
	sf::Texture texture_background;
	sf::Sprite background;

	//Shapes
	sf::Texture texture_o;
	sf::Texture texture_x;
	sf::RectangleShape grid[3][3];
	
	//Game logic
	bool game_row;
	bool game_end;
	int moves;
	int player_turn;
	int placed_shapes[3][3]; //////////

	//UI
	sf::RectangleShape next_move;

	//Mouse positions
	sf::Vector2i mouse_pos_window;
	sf::Vector2f mouse_pos_view;

	//Private functions
	void initialize_Variable();
	void initialize_Window();
	void initialize_Music();
	void initialize_Grid();
	void initialize_UI();

public:
	Game();
	~Game();
	const bool get_Window_Is_Open() const;	//Check if window is open

	void win_cond_check();
	void place_Shape();
	void events_Pool();
	void update_Mouse_Position();
	void update_Player_Move();
	void update();
	void render();
};