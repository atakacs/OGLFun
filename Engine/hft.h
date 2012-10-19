#ifndef _F_HFT_H
#define _F_HFT_H

#include "wobject.h"
#include "texture.h"

class HFT : public WObject{
	//friend class TestWorld;
	public:
		HFT(Texture *texture);
		~HFT();

		void OnAnimate(seconds_t seconds);
		void OnDraw();

		void SetXRotSpeed(float deg);
		void SetYRotSpeed(float deg);
	private:
		Texture *m_texture;
		CVector * m_heightfield;
		CVector * m_normals;
		float m_xangle, m_yangle;
		float m_xRotSpeed, m_yRotSpeed;

		void BuildHeightfield();
};

#endif /*QUAD_*/
