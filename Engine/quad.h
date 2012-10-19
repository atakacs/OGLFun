#ifndef _F_QUAD_H
#define _F_QUAD_H

#include "wobject.h"
#include "texture.h"

class Quad : public WObject{
	//friend class TestWorld;
	public:
		Quad(Texture *texture);
		
		void OnAnimate(seconds_t seconds);
		void OnDraw();
		
		void SetXRotSpeed(float deg);
		void SetYRotSpeed(float deg);
	private:
		Texture *m_texture;
		float m_xangle, m_yangle;
		float m_xRotSpeed, m_yRotSpeed;
};

#endif /*QUAD_*/
