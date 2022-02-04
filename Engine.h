#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

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

	//Mouse position
	sf::Vector2i mouse_pos_w;

	//Private functions
	void initialize_Variable();
	void initialize_Window();
	void initialize_Music();
	void initialize_Grid();


public:
	Game();
	~Game();
	const bool get_Window_Is_Open() const;	//Check if window is open

	void events_Pool();
	void update_Mouse_Position();
	void update();
	void render();
};

