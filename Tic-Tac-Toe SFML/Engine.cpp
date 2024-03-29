#include "Engine.h"

//Initialize class variables
void Game::initialize_Variables()
{
	this->game_state_end = false;
	this->game_state_draw = false;
	this->moves = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	this->player_turn = rand() % (2 - 1 + 1) + (1);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)	
		{
			this->placed_shapes[i][j] = 0;
		}
	}
}

//Rendering Window
void Game::initialize_Window()
{
	this->video_mode.width = 600;
	this->video_mode.height = 800;
	this->window_ptr = new sf::RenderWindow(this->video_mode, "Tic-Tac-Toe");
	this->window_ptr->setFramerateLimit(60);
}

void Game::initialize_Resources()
{
	// Load textures
	if (!this->texture_background.loadFromFile("Assets\\Background.png"))	//Background
		exit(1);

	if (!this->texture_o.loadFromFile("Assets\\OShape.png"))				//O shape
		exit(1);

	if (!this->texture_x.loadFromFile("Assets\\XShape.png"))				//Xshape
		exit(1);

	if (!this->texture_restart_button.loadFromFile("Assets\\Restart.png"))	// Restart button texture
		exit(1);


	//Music initialization
	if (!this->sound_placing.openFromFile("Assets\\Placing.ogg"))		//Placing shape sound
		exit(1);

	if (!this->sound_victory.openFromFile("Assets\\Victory.ogg"))		//Victory sound
		exit(1);

	if (!this->sound_draw.openFromFile("Assets\\Draw.ogg"))				//Draw sound
		exit(1);

	if (!this->sound_restart.openFromFile("Assets\\Restart.ogg"))		//Restart button sound
		exit(1);

	this->sound_restart.setVolume(50.f);
	this->sound_placing.setVolume(75.f);
	this->sound_victory.setVolume(75.f);
}

//Grid initialization 
void Game::initialize_Grid()
{
	this->background.setTexture(texture_background);

	float x = 15.f, y = 15.f;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)		//Set every square position,size,color and outline
		{
			this->grid[i][j].setTexture(NULL);
			this->grid[i][j].setPosition(x, y);
			this->grid[i][j].setSize(sf::Vector2f(170.f, 170.f));
			this->grid[i][j].setFillColor(sf::Color(162, 162, 162, 0));
			y += 200;
		}
		y = 15.f;		//set valuses for nex loop
		x += 200.f;
	}
}

//UI initialization
void Game::initialize_UI()
{
	this->next_move.setPosition(445.f, 605.f);
	this->next_move.setSize(sf::Vector2f(170.f, 170.f));
	this->next_move.setScale(0.5,0.5);

	if (this->player_turn == 1)
		this->next_move.setTexture(&texture_o);
	else
		this->next_move.setTexture(&texture_x);

	this->restart_button.setPosition(200.f, 728.f);
	this->restart_button.setSize(sf::Vector2f(200.f, 53.f));
	this->restart_button.setTexture(&texture_restart_button);
}

////////////////////	Constructor/Destructor	////////////////////

Game::Game()
{
	this->window_ptr = nullptr;
	this->initialize_Variables();
	this->initialize_Window();
	this->initialize_Resources();
	this->initialize_Grid();
	this->initialize_UI();
}

Game::~Game()
{
	delete this->window_ptr;
}

////////////////////	Functions	////////////////////

//Check if window is running
const bool Game::get_Window_Is_Open() const
{
	return this->window_ptr->isOpen();
}

//Update mouse position relative to window
void Game::update_Mouse_Position()
{
	this->mouse_pos_window = sf::Mouse::getPosition(*this->window_ptr);
	this->mouse_pos_view = this->window_ptr->mapPixelToCoords(this->mouse_pos_window); //Convert mouse pos(int) to (float)
}

//Update "next move" UI
void Game::update_Player_Move()
{
	if (this->player_turn == 1)
		this->next_move.setTexture(&texture_o);
	else
		this->next_move.setTexture(&texture_x);
}

//End of game view 
void Game::end_Of_Game()
{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (this->grid[i][j].getFillColor() != sf::Color::Green)
					this->grid[i][j].setFillColor(sf::Color(255, 255, 255, 100));
			}
		}

		this->restart_button.setFillColor(sf::Color::Green);
		this->next_move.setFillColor(sf::Color::Transparent);
		this->background.setColor(sf::Color(255, 255, 255, 100));

		if (!this->game_state_draw)
			this->sound_victory.play();
		else 
			this->sound_draw.play();
}

//Game reset
void Game::restart_game()
{
	this->sound_draw.stop();
	this->sound_victory.stop();
	this->initialize_Variables();
	this->initialize_Grid();
	this->background.setColor(sf::Color::White);
	this->next_move.setFillColor(sf::Color::White);
	this->restart_button.setFillColor(sf::Color::White);
}

//Check if win
void Game::win_cond_check()	
{
	if (this->moves == 9) this->game_state_draw = this->game_state_end = true;

	//Columns
	for (int i = 0; i < 3; i++)
	{
		if (this->placed_shapes[i][0] == this->placed_shapes[i][1] && this->placed_shapes[i][1] == this->placed_shapes[i][2]
			&& this->placed_shapes[i][0] != 0)
		{
			this->grid[i][0].setFillColor(sf::Color::Green);
			this->grid[i][1].setFillColor(sf::Color::Green);
			this->grid[i][2].setFillColor(sf::Color::Green);
			this->game_state_end = true;
			this->game_state_draw = false;
		}
	}

	//Rows
	for (int i = 0; i < 3; i++)
	{
		if (this->placed_shapes[0][i] == this->placed_shapes[1][i] && this->placed_shapes[1][i] == this->placed_shapes[2][i]
			&& this->placed_shapes[0][i] != 0)
		{
			this->grid[0][i].setFillColor(sf::Color::Green);
			this->grid[1][i].setFillColor(sf::Color::Green);
			this->grid[2][i].setFillColor(sf::Color::Green);
			this->game_state_end = true;
			this->game_state_draw = false;
		}
	}

	//Vertical
	if (this->placed_shapes[0][0] == this->placed_shapes[1][1] && this->placed_shapes[1][1] == this->placed_shapes[2][2]
		&& this->placed_shapes[0][0] != 0)
	{
		this->grid[0][0].setFillColor(sf::Color::Green);
		this->grid[1][1].setFillColor(sf::Color::Green);
		this->grid[2][2].setFillColor(sf::Color::Green);
		this->game_state_end = true;
		this->game_state_draw = false;
	}

	if (this->placed_shapes[0][2] == this->placed_shapes[1][1] && this->placed_shapes[1][1] == this->placed_shapes[2][0]
		&& this->placed_shapes[0][2] != 0)
	{
		this->grid[0][2].setFillColor(sf::Color::Green);
		this->grid[1][1].setFillColor(sf::Color::Green);
		this->grid[2][0].setFillColor(sf::Color::Green);
		this->game_state_end = true;
		this->game_state_draw = false;
	}
	if (this->game_state_end)
		this->end_Of_Game();
}

void Game::place_Shape()
{
	for (int i = 0; i < 3; i++)		//loop for grid
	{
		for (int j = 0; j < 3; j++)		
		{
			if (this->grid[i][j].getGlobalBounds().contains(this->mouse_pos_view) &&	//Click on Grid piece 
				 !this->game_state_end && this->placed_shapes[i][j]==0) 
			{
				this->grid[i][j].setFillColor(sf::Color(sf::Color::White));		//Set grid as visable

				if (this->player_turn == 1)		//Set texture of that grid as X or O
				{
					this->grid[i][j].setTexture(&texture_o);
					this->placed_shapes[i][j] = 1;
					this->moves++;
					this->sound_placing.stop();
					this->sound_placing.play();
					player_turn = 2;						//swap turn
				}
				else
				{
					this->grid[i][j].setTexture(&texture_x);
					this->placed_shapes[i][j] = 2;
					this->sound_placing.stop();
					this->sound_placing.play();
					this->moves++;
					player_turn = 1;
				}
				this->update_Player_Move();		//Update "next move" after placing

				if (this->moves > 4)			//After 4 placed shapes begin checking win con
					this->win_cond_check();
			}
		}
	}

	if (this->restart_button.getGlobalBounds().contains(this->mouse_pos_view))	//Click on restart button
	{
		this->sound_restart.stop();
		this->sound_restart.play();
		this->restart_game();
	}
}

//Events handling 
void Game::events_Pool()
{
	while (this->window_ptr->pollEvent(this->event_1))
	{
		switch (this->event_1.type)
		{
		case sf::Event::Closed:				//Pressing x on window
			this->window_ptr->close();
			break;
		case sf::Event::EventType::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //if button pressed
			{
				this->place_Shape();	//Place shape on board click
				break;
			}	
		}
	}
}

//Update			
void Game::update()
{
	this->events_Pool();	//Handle events
	this->update_Mouse_Position();	//Get mouse pos 
}


//Clearing old frame -> drawing objects -> displaying new frame
void Game::render()
{
	this->window_ptr->clear();

	//Draw here
	this->window_ptr->draw(background);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->window_ptr->draw(grid[i][j]);
		}
	}
	this->window_ptr->draw(next_move);
	this->window_ptr->draw(restart_button);
	this->window_ptr->display();
}