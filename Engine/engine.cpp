/**
 * The engine's main-class
 */

#include "engine.h"
#include <iostream>

using namespace std;

void Engine::Init() {
	m_quit = false;
	m_fullscreen = false;
	
	InitWindow();
	InitGL();
	
	m_camera = new Camera();
	m_camera->SetPos(CVector(0.0f, 0.0f, 10.0f));
	//m_camera->SetVel(CVector(0.0, 0.0f, -0.5f));

	m_world = new TestWorld(this);
	m_world->Init();
}

int Engine::Run() {
	static Uint32 oldTicks = 10;
	
	while(!m_quit) {
		Uint32 newTicks = SDL_GetTicks();
		seconds_t seconds = (newTicks - oldTicks)/1000.0f;
		oldTicks = newTicks;
		HandleEvents();
		Animate(seconds);
		Draw();
	}
	Uninit();
	return 0;
}
 
void Engine::Resize(int width, int height, bool fullscreen) {
	Uint32 flags = SDL_OPENGL | SDL_HWSURFACE | SDL_HWACCEL | (fullscreen?SDL_FULLSCREEN:0);
	dcontext = SDL_SetVideoMode(width, height, 0, flags);
	if(!dcontext)
		cout << "Error: Unable to set video mode." << endl;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f, (float)width/(float)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}

void Engine::InitWindow() {
	int error;
	error = SDL_Init(SDL_INIT_EVERYTHING);

	m_keyStates = SDL_GetKeyState(&m_keySize);
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
	//SDL_ShowCursor(SDL_DISABLE);
	Resize(1024, 768, m_fullscreen);
}

void Engine::InitGL() {
	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	GLfloat light_position[] = { 0.0, 4.0f, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glMatrixMode(GL_MODELVIEW);
}

void Engine::Uninit() {
	SDL_Quit();
}

void Engine::HandleEvents() {
	SDL_Event event;

	while(SDL_PollEvent(&event))
		{
			if(IsDown(SDLK_ESCAPE) || IsDown('q'))
				m_quit = true; // Signal program quit.
			switch(event.type)
			{
				case SDL_VIDEORESIZE:
					Resize(event.resize.w, event.resize.h, m_fullscreen);
				break;
				case SDL_QUIT:
					m_quit = true; // Signal program quit
				break;
				/*case SDL_KEYDOWN:
					//cout << "SDL_KEYDOWN: " << event.key.keysym.sym << endl;
					m_keys[event.key.keysym.sym] = true;
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						case 'q':
							m_quit = true;
							return;
						default:
						break;
					}
				break;
				case SDL_KEYUP:
					cout << "SDL_KEYUP: " << event.key.keysym.sym << endl;
					m_keys[event.key.keysym.sym] = false;
				break;*/
				default:
				break;
			}
			
		}
}

void Engine::Draw() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	// Camera stuff goes here
	//glTranslatef(0.0f, 0.0f, -5.0f);
	m_camera->Position();

	m_world->Draw();

	SDL_GL_SwapBuffers();
}

void Engine::Animate(seconds_t seconds) {
	scalar_t x = 0, y = 0, z = 0;
	if(IsDown('w'))
		z = -2.0f;
	else if(IsDown('s'))
		z = 2.0f;


	if(IsDown('a'))
			x = -2.0f;
	else if(IsDown('d'))
			x = 2.0f;

	m_camera->SetVel(CVector(x, y, z));

	m_camera->Prepare(seconds);
	m_world->Animate(seconds);
}
