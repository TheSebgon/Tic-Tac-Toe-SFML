#pragma once

#include <iostream>
#include <vector>
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
	bool player_turn;


	//Mouse positions
	sf::Vector2i mouse_pos_window;
	sf::Vector2f mouse_pos_view;


	//Private functions
	void initialize_Variable();
	void initialize_Window();
	void initialize_Music();
	void initialize_Grid();


public:
	Game();
	~Game();
	const bool get_Window_Is_Open() const;	//Check if window is open

	void place_Shape();
	void events_Pool();
	void update_Mouse_Position();
	void update();
	void render();
};

