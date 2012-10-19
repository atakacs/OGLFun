/**
 * A class that represents one texture.
 */

#ifndef _F_TEXTURE_H
#define _F_TEXTURE_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <exception>

class Texture {
	public:
		//Texture() : m_id(0) {}
		Texture(char * fileName) {
			m_id = 0;
			LoadFromFile(fileName);
		}
		~Texture();
		
		GLuint GetID() {
			return m_id;
		}
		
		int GetHeight() {
			return m_surface->h;
		}

		int GetWidth() {
			return m_surface->w;
		}

		SDL_Surface * GetSDLSurface() {
			return m_surface;
		}
		
		void * GetPixels() {
			return m_surface->pixels;
		}

		int LoadFromFile(char * fileName);
		void UnLoad();
		void Bind() {
			if(m_id)
				glBindTexture(GL_TEXTURE_2D, m_id);
		}
	private:
		GLuint m_id;
		SDL_Surface *m_surface;
};
#endif
