/**
 * The engine's main-class
 */

#ifndef _F_ENGINE_H
#define _F_ENGINE_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>

#include "types.h"

#include "texture.h"
#include "testworld.h"

class Engine {
	public:
		void Init();
		int Run();
		void Uninit();

		bool IsDown(int key) {
			return m_keyStates[key] == 1;
		}
	private:
		Uint8 *m_keyStates;
		int m_keySize;
		bool m_quit, m_fullscreen;
		SDL_Surface *dcontext;
		
		TestWorld *m_world;

		void InitWindow();
		void InitGL();
		void Resize(int width, int height, bool fullscreen); 
		void HandleEvents();
		
		// Returns the state of the specified key.

		void Draw();
		void Animate(seconds_t seconds);
};

#endif
