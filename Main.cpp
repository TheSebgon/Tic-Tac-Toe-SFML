#include "Engine.h"


int main()
{
	Game g1;

	//Window loop
	while (g1.get_Window_Is_Open())
	{

		//event handling
		g1.events_Pool();

		//update
		g1.update();

		//render
		g1.render();

	}
}