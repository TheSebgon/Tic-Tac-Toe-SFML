#include "Engine.h"

//Initialize class variables
void Game::initialize_Variable()
{
	this->window_ptr = nullptr;
	srand(static_cast<unsigned int>(time(NULL)));
	this->player_turn = rand() % (2 - 1 + 1) + (1);
}

//Rendering Window
void Game::initialize_Window()
{
	this->video_mode.width = 600;
	this->video_mode.height = 800;
	this->window_ptr = new sf::RenderWindow(this->video_mode, "SFML window");
	this->window_ptr->setFramerateLimit(60);
}

//Music initialization
void Game::initialize_Music()
{
	if (!this->music.openFromFile("sound.ogg"))
		exit(1);
}

//texture initialization 
void Game::initialize_Grid()
{
	// Load textures
	if (!this->texture_background.loadFromFile("1.png"))
		exit(1);

	if (!this->texture_o.loadFromFile("2.png"))
		exit(1);

	if (!this->texture_x.loadFromFile("3.png"))
		exit(1);



	float x = 15.f, y = 15.f;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)		//Set every square position,size,color and outline
		{
			this->grid[i][j].setPosition(x, y);
			this->grid[i][j].setSize(sf::Vector2f(170.f, 170.f));
			this->grid[i][j].setFillColor(sf::Color(162, 162, 162, 0));

			this->grid[i][j].setOutlineThickness(1.f);					//Debug only (position check)
			this->grid[i][j].setOutlineColor(sf::Color(0, 0, 0, 255));
			
			y += 200;
		}
		y = 15.f;		//set valuses for nex loop
		x += 200.f;
	}


	// Create a sprite of grid
	this->background.setTexture(texture_background);

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
}

////////////////////	Constructor/Destructor	////////////////////

Game::Game()
{
	this->initialize_Variable();
	this->initialize_Window();
	this->initialize_Music();
	this->music.play();
	this->initialize_Grid();
	initialize_UI();
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

void Game::place_Shape()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //if button pressed
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)		//loop for grid
			{
				if (this->grid[i][j].getGlobalBounds().contains(this->mouse_pos_view))		//Check if in that grid
				{
					this->grid[i][j].setFillColor(sf::Color(sf::Color::White));				//Set grid as visable

					if (this->player_turn == 1)		//set texture of X or O
					{
						this->grid[i][j].setTexture(&texture_o);
						player_turn = 2;
					}
					else
					{
						this->grid[i][j].setTexture(&texture_x);
						player_turn = 1;
					}

				}
			}
		}
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
				this->place_Shape();	//Place shape on board click
				this->update_Player_Move();
				break;
		}
	}
}

//Update			//game logic
void Game::update()
{
	this->events_Pool();	//Handle events
	this->update_Mouse_Position();	//Get mouse pos 

	//relative to the screen
	std::cout << "Mouse position: " << sf::Mouse::getPosition(*this->window_ptr).x << " "
		<< sf::Mouse::getPosition(*this->window_ptr).y << std::endl;
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

	this->window_ptr->display();
}