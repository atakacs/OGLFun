#ifndef _F_WORLD_H
#define _F_WORLD_H

#include "types.h"

class Engine;

class World {
	public:
		World(Engine *engine) {
			m_engine = engine;
		}
		
		virtual ~World() {}
		
		virtual void Init() {}
		virtual void UnInit() {}
		virtual void Animate(seconds_t seconds) {}
		virtual void Draw() {}
		
		Engine *GetEngine() { return m_engine; }
	private:
		Engine *m_engine;
};
#endif
