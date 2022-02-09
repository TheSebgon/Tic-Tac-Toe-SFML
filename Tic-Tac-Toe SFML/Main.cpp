#include "Engine.h"


int main()
{
	Game g1;

	//Window loop
	while (g1.get_Window_Is_Open())
	{
		//Event handling
		g1.events_Pool();

		//Update
		g1.update();

		//Clearing old frame -> drawing objects -> displaying new frame
		g1.render();
	}
}