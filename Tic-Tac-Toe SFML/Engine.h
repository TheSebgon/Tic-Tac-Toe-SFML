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
	sf::Music sound_placing;			// to do: sound of placing shapes insted background miusic
	sf::Music sound_restart;
	sf::Music sound_victory;
	sf::Music sound_draw;

	//Background
	sf::Texture texture_background;
	sf::Sprite background;

	//Shapes
	sf::Texture texture_o;
	sf::Texture texture_x;
	sf::RectangleShape grid[3][3];
	
	//Game logic
	bool game_state_draw;
	bool game_state_end;
	int moves;
	int player_turn;
	int placed_shapes[3][3];

	//UI
	sf::Texture texture_restart_button;
	sf::RectangleShape next_move;
	sf::RectangleShape restart_button;

	//Mouse positions
	sf::Vector2i mouse_pos_window;
	sf::Vector2f mouse_pos_view;

	//Private functions
	void initialize_Variables();
	void initialize_Window();
	void initialize_Resources();
	void initialize_Grid();
	void initialize_UI();

public:
	Game();
	~Game();
	const bool get_Window_Is_Open() const;	//Check if window is open

	void end_Of_Game();
	void restart_game();
	void win_cond_check();
	void place_Shape();
	void events_Pool();
	void update_Mouse_Position();
	void update_Player_Move();
	void update();
	void render();
};