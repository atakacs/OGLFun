/**
 * A base-class that represents an object in the game world.
 */

#ifndef _F_WOBJECT_H_
#define _F_WOBJECT_H_


#include "vector.h"
#include "node.h"
#include "types.h"

class WObject : public Node {
	public:
		// Constructors.
		WObject(Vector pos, Vector ori, Vector vel) {
			m_position = pos;
			m_orientation = ori;
			m_velocity = vel;
		}
		WObject(Vector pos) {
			WObject(pos, Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f));
		}
		WObject() {
			WObject(Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f));
		}
		
		virtual ~WObject() {}
		
		// Setters.
		void SetPos(Vector pos) { m_position = pos; }
		void SetOri(Vector ori) { m_orientation = ori; }
		void SetVel(Vector vel) {  m_velocity = vel; }
		
		// Getters.
		Vector GetPos() { return m_position; }
		Vector GetOri() { return m_orientation; }
		Vector GetVel() { return m_velocity; }
		
		// Animate performs object-related calculations.
		void Animate(seconds_t seconds) {
			m_position = m_position + seconds*m_velocity;
			
			OnAnimate(seconds);
			
			if(HasChild())
				((WObject *)m_child)->Animate(seconds);
			if(HasNext())
				((WObject *)m_next)->Animate(seconds);
		}
		
		virtual void OnAnimate(seconds_t seconds) {
			
		}
		// Draw handles drawing of the object, may or may not follow a call to Animate().
		virtual void Draw() {
			glPushMatrix();
			glTranslatef(m_position.x, m_position.y, m_position.z);
			OnDraw();
			
			if(HasChild())
				((WObject *)m_child)->Draw();
			if(HasNext())
				((WObject *)m_next)->Draw();
			glPopMatrix();
		}
		
		virtual void OnDraw() {}
	protected:
		// Note: Velocity is change of position per second.
		Vector m_position, m_orientation, m_velocity;
};

#endif
