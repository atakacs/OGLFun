/**
 * A class that represents one texture.
 */

#include <iostream>
#include "texture.h"

using namespace std;
Texture::~Texture() {
	SDL_FreeSurface(m_surface);
}

/**
 * Loads a texture from file and creates an OpenGL texture object.
 */
int Texture::LoadFromFile(char *fileName) {
	GLenum format = GL_RGBA;

	if(m_id)
		UnLoad();
	
	// Load image as SDL-surface.
	if(!(m_surface = IMG_Load(fileName))) {
		cout << "Error: Couldn't load texture from \"" << fileName << "\"" << cout;
		return -1; 
	}


	// Generate texture object and bind.
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	cout << "Texture data; Id: " << m_id << ", Width: " << m_surface->w << ", Height: " << m_surface->h << ", BytesPerPixel:  " << (int)(m_surface->format->BytesPerPixel) << ", Adress: " << m_surface->pixels<< ", BitsPerPixel:  " << (int)(m_surface->format->BitsPerPixel) << endl;
	
	// Set texture parameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	if(m_surface->format->BytesPerPixel == 3)
		format = GL_RGB;
	else  if(m_surface->format->BytesPerPixel == 4)
		format = GL_RGBA;
	// Load texture data into object.
	glTexImage2D(	GL_TEXTURE_2D,
					0,
					GL_RGBA,
					m_surface->w,
					m_surface->h,
					0,
					format,
					GL_UNSIGNED_BYTE,
					m_surface->pixels);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	//SDL_FreeSurface(surface);
	return 0;
}



void Texture::UnLoad() {
	if(m_id) {
		glDeleteTextures(1, &m_id);
		m_id = 0;
	}
}
