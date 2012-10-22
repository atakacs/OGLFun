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
	m_surfaceNormals = new CVector[width * height * 2];

	m_normals= new CVector[width * height];

	unsigned char * pixels = (unsigned char*)m_texture->GetPixels();

	float wstep = 1.0f/width;
	float hstep = 1.0f/height;

	for(int h = 0; h < height; ++h) {
		for(int w = 0; w < width; ++w) {
			m_heightfield[width*h + w].x = w*wstep;
			m_heightfield[width*h + w].y = (pixels[(h*width + w)*3] + pixels[(h*width + w)*3 + 1] + pixels[(h*width + w)*3 + 2])/768.0f;
			//m_heightfield[width*h + w].y = pixels[(h*width + w)*3]/256.0f;
			m_heightfield[width*h + w].z = -h*hstep;
		}
		glEnd();
	}

	// Calculate surface normals
	for(int h = 0; h < (height - 1); ++h) {
			for(int w = 0; w < (width - 1); ++w) {
				CVector a = m_heightfield[(h + 1)*width + w]; // Lower left
				CVector b = m_heightfield[h*width + w]; // Upper left
				CVector c = m_heightfield[(h + 1)*width + w + 1]; // Lower right
				CVector d = m_heightfield[h*width + w + 1]; // Upper right


				// Upper left
				m_surfaceNormals[(h*width + w)*2] = (b - a).CrossProduct(d - a);
				m_surfaceNormals[(h*width + w)*2].Normalize();
				//m_surfaceNormals[w * h] = -m_surfaceNormals[w * h];

				// Lower right
				m_surfaceNormals[(h*width + w)*2 + 1] = ((d - a).CrossProduct(c - a));
				m_surfaceNormals[(h*width + w)*2 + 1].Normalize();
				//m_surfaceNormals[w * h + 1] = -m_surfaceNormals[w * h + 1];
			}
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

	glTranslatef(-5.0f, 0.0f, 5.0f);

	glScalef(10.0f, 2.0f, 10.0f);

	/*if(m_texture)
		m_texture->Bind();
	else
		glBindTexture(GL_TEXTURE_2D, GL_NONE);*/

	glColor3f(0.0f, 1.0f, 0);

	int width = m_texture->GetWidth();
	int height = m_texture->GetHeight();

	for(int h = 0; h < (height - 1); ++h) {
		glBegin(GL_TRIANGLE_STRIP);

		for(int w = 0; w < width; ++w) {
			//glColor3f(1.0f, 0, 0);
			if(w)
				glNormal3f(m_surfaceNormals[(h*width + w - 1)*2].x, m_surfaceNormals[(h*width + w - 1)* 2].y, m_surfaceNormals[(h*width + w - 1)* 2].z );
			glVertex3f(m_heightfield[(h*width + w)].x, m_heightfield[(h*width + w)].y , m_heightfield[(h*width + w)].z);
			//glColor3f(0.0f, 1.0f, 0);
			if(w)
				glNormal3f(m_surfaceNormals[(h*width + w - 1)*2 + 1].x, m_surfaceNormals[(h*width + w - 1)*2 + 1].y, m_surfaceNormals[(h*width + w - 1)*2 + 1].z );
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
