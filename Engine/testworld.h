#ifndef _F_TESTWORLD_H_
#define _F_TESTWORLD_H_

#include "texture.h"
#include "quad.h"
#include "world.h"
#include "hft.h"

//class World;

class TestWorld:World{
	public:
		TestWorld(Engine *engine):World(engine) {}
		~TestWorld() {}
		void Init();
		void UnInit();
		
		void Animate(seconds_t seconds);
		void Draw();
		
	private:
		Texture *m_texture;
		Quad *m_quad, *m_quad2;
		HFT *m_hft;
};
#endif /*TESTWORLD_H_*/
