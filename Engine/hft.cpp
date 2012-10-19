#include "hft.h"
#include <iostream>

HFT::HFT(Texture *texture) {
	m_texture = texture;
	m_xangle = 0.0f;
	m_yangle = 0.0f;
	m_xRotSpeed = 0.0f;
	m_yRotSpeed = 0.0f;

	BuildHeightfield();
}

HFT::~HFT() {

}

void HFT::BuildHeightfield() {
	int width = m_texture->GetWidth();
	int height = m_texture->GetHeight();

	m_heightfield = new CVector[width * height];
	//m_surfaceNormals = new CVector[width * height];

	m_normals= new CVector[width * height];

	char * pixels = (char*)m_texture->GetPixels();

	float wstep = 1.0f/width;
	float hstep = 1.0f/height;

	for(int h = 0; h < height; ++h) {
		for(int w = 0; w < width; ++w) {
			m_heightfield[width*h + w].x = w*wstep;
			m_heightfield[width*h + w].y = (pixels[(h*width + w)*3] + pixels[(h*width + w)*3 + 1] + pixels[(h*width + w)*3 + 2])/775.0f;
			m_heightfield[width*h + w].z = -h*hstep;
		}
		glEnd();
	}
}


void HFT::OnAnimate(seconds_t seconds) {
	m_xangle += seconds*m_xRotSpeed;
	m_yangle += seconds*m_yRotSpeed;

	if(m_xangle >= 360.0f || m_xangle <= -360.0f)
		m_xangle = 0.0f;

	if(m_yangle >= 360.0f || m_yangle <= -360.0f)
		m_yangle = 0.0f;

	//m_xRotSpeed = 0.0f;
	//m_yRotSpeed = 0.0f;
}

void HFT::OnDraw() {
	glPushMatrix();

	glRotatef(m_xangle, 1.0, 0.0f, 0.0f);
	glRotatef(m_yangle, 0.0, 1.0f, 0.0f);

	glTranslatef(-50.0f, 0.0f, 50.0f);

	glScalef(100.0f, 1.0f, 100.0f);

	/*if(m_texture)
		m_texture->Bind();
	else
		glBindTexture(GL_TEXTURE_2D, GL_NONE);*/

	glColor3f(1.0f, 0, 0);

	int width = m_texture->GetWidth();
	int height = m_texture->GetHeight();

	for(int h = 0; h < (height - 1); ++h) {
		glBegin(GL_TRIANGLE_STRIP);

		for(int w = 0; w < width; ++w) {
			glColor3f(1.0f, 0, 0);
			glVertex3f(m_heightfield[(h*width + w)].x, m_heightfield[(h*width + w)].y , m_heightfield[(h*width + w)].z);
			glColor3f(0.0f, 1.0f, 0);
			glVertex3f(m_heightfield[((h + 1)*width + w)].x, m_heightfield[((h + 1)*width + w)].y , m_heightfield[((h + 1)*width + w)].z);
		}
		glEnd();
	}

		//glTexCoord2f(0.0f, 0.0f);
	glPopMatrix();
}

void HFT::SetXRotSpeed(float deg) {
	m_xRotSpeed = deg;
}
void HFT::SetYRotSpeed(float deg) {
	m_yRotSpeed = deg;
}
