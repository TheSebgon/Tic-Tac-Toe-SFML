#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Game engine

class Game
{
private:
	//Variables
	sf::RenderWindow* window_ptr;
	sf::VideoMode video_mode;

	sf::Event event_1;


	//Private functions
	void initialize_Variable();
	void initialize_Window();

public:
	Game();
	~Game();
	const bool get_Window_Is_Open() const;	//Check if window is open

	void events_Pool();

	void update();
	void render();
};

