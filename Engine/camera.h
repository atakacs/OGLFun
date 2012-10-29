#ifndef _F_CAMERA_H
#define _F_CAMERA_H

#include "vector.h"
#include "types.h"

class Camera {
public:
	// Constructors.
	Camera(CVector pos, CVector ori, CVector vel) {
		m_position = pos;
		m_orientation = ori;
		m_velocity = vel;
	}
	Camera(CVector pos) {
		Camera(pos, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f));
	}
	Camera() {
		Camera(CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f));
	}

	// Setters.
	void SetPos(CVector pos) { m_position = pos; }
	void SetOri(CVector ori) { m_orientation = ori; }
	void SetVel(CVector vel) {  m_velocity = vel; }

	// Getters.
	CVector GetPos() { return m_position; }
	CVector GetOri() { return m_orientation; }
	CVector GetVel() { return m_velocity; }

	// Prepare camera, set position and orientation
	void Prepare(seconds_t seconds) {
		m_position = m_position + seconds*m_velocity;

	}

	void Position();
	void Restore();
protected:
	// Note: Velocity is change of position per second.
	CVector m_position, m_orientation, m_velocity;

};

#endif
