#include "quad.h"

Quad::Quad(Texture *texture) {
	m_texture = texture;
	m_xangle = 0.0f;
	m_yangle = 0.0f;
	m_xRotSpeed = 0.0f;
	m_yRotSpeed = 0.0f;
}

void Quad::OnAnimate(seconds_t seconds) {
	m_xangle += seconds*m_xRotSpeed;
	m_yangle += seconds*m_yRotSpeed;
	
	if(m_xangle >= 360.0f || m_xangle <= -360.0f)
		m_xangle = 0.0f;

	if(m_yangle >= 360.0f || m_yangle <= -360.0f)
		m_yangle = 0.0f;
		
	//m_xRotSpeed = 0.0f;
	//m_yRotSpeed = 0.0f;
}

void Quad::OnDraw() {
	glPushMatrix();
	glRotatef(m_xangle, 1.0, 0.0f, 0.0f);
	glRotatef(m_yangle, 0.0, 1.0f, 0.0f);

	if(m_texture)
		m_texture->Bind();
	else
		glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f); // Top left
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f); // Top right
		
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 0.0f); // Bottom right
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom left
	glEnd();
	glPopMatrix();
}

void Quad::SetXRotSpeed(float deg) {
	m_xRotSpeed = deg;
}
void Quad::SetYRotSpeed(float deg) {
	m_yRotSpeed = deg;
}
