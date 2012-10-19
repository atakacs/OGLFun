#ifndef _F_CAMERA_H
#define _F_CAMERA_H

class Camera {
public:
	// Constructors.
	Camera(Vector pos, Vector ori, Vector vel) {
		m_position = pos;
		m_orientation = ori;
		m_velocity = vel;
	}
	Camera(Vector pos) {
		WObject(pos, Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f));
	}
	Camera() {
		WObject(Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f));
	}

	// Setters.
	void SetPos(Vector pos) { m_position = pos; }
	void SetOri(Vector ori) { m_orientation = ori; }
	void SetVel(Vector vel) {  m_velocity = vel; }

	// Getters.
	Vector GetPos() { return m_position; }
	Vector GetOri() { return m_orientation; }
	Vector GetVel() { return m_velocity; }

	// Prepare camera, set position and orientation
	void Prepare(seconds_t seconds) {
		m_position = m_position + seconds*m_velocity;

	}
protected:
	// Note: Velocity is change of position per second.
	Vector m_position, m_orientation, m_velocity;

};

#endif
