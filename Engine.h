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

	std::vector<sf::Sprite> shape_b;		//fun tworz¹ca x y pobieraj¹ca pozycje myszy i ³¹cz¹ca j¹ z przestrzeni¹
	std::vector<sf::Sprite> shape_c;
	sf::RectangleShape grid[3][3];

	sf::Sprite shape_x;
	sf::Sprite shape_o;

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

