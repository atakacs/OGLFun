/*
 * camera.cpp
 *
 *  Created on: Oct 22, 2012
 *      Author: atakacs
 */

#include "camera.h"

void Camera::Position() {
	glPushMatrix();
	glTranslatef(-m_position.x, -m_position.y, -m_position.z);
}

void Camera::Restore() {
	glPopMatrix();
}



