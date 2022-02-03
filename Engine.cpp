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
	this->video_mode.height = 600;
	this->window_ptr = new sf::RenderWindow(this->video_mode, "SFML window");
	this->window_ptr->setFramerateLimit(60);
}


////////////////////	Constructor/Destructor	////////////////////

Game::Game()
{
	this->initialize_Variable();
	this->initialize_Window();
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

//Update 
void Game::update()
{
	this->events_Pool();
}


//Clearing old frame -> drawing objects -> displaying new frame
void Game::render()
{
	this->window_ptr->clear();		

	//Draw here

	this->window_ptr->display();
}
