#include "Engine.h"

//Initialize class variables
void Game::initialize_Variable()
{
	this->window_ptr = nullptr;
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



	float x = 0.f, y = 0.f;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)		//Set every square position,size,color and outline
		{
			this->grid[i][j].setPosition(x, y);
			this->grid[i][j].setSize(sf::Vector2f(200.f, 200.f));
			this->grid[i][j].setFillColor(sf::Color(162, 162, 162, 0));
			//this->grid[i][j].setOutlineThickness(1.f);					Debug only (position check)
			//this->grid[i][j].setOutlineColor(sf::Color(0, 0, 0, 255));
			y += 200;
		}
		y = 0.f;		//set valuses for nex loop
		x += 200.f;
	}


	// Create a sprite of grid
	this->background.setTexture(texture_background);


	///  create x/o vector?
	this->shape_o.setTexture(texture_o);
	this->shape_x.setTexture(texture_x);

	this->shape_o.setPosition(20.f, 410.f);
	this->shape_x.setPosition(20.f, 210.f);

}

////////////////////	Constructor/Destructor	////////////////////

Game::Game()
{
	this->initialize_Variable();
	this->initialize_Window();
	this->initialize_Music();
	this->music.play();
	this->initialize_Grid();
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
	this->mouse_pos_w = sf::Mouse::getPosition(*this->window_ptr);
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
		}
	}
}

//Update			//game logic
void Game::update()
{
	this->events_Pool();	//handle events
	this->update_Mouse_Position();	//get mouse pos 

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
	this->window_ptr->draw(shape_x);
	this->window_ptr->draw(shape_o);


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->window_ptr->draw(grid[i][j]);
		}
	}


	this->window_ptr->display();
}