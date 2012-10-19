#include <iostream>
#include <SDL/SDL.h>
#include "engine.h"
 
using namespace std; 

int main(int argc, char * argv[])  {
	//freopen( "CON", "w", stdout );
	//freopen( "CON", "w", stderr );
	Engine * engine; 
	cout << "Initialising...\n";
	engine = new Engine();
	engine->Init();
	cout << "Done.\nStarting engine...\n";
	return engine->Run();
}
