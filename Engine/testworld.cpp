#include "testworld.h"
#include "engine.h"
#include "world.h"

void TestWorld::Init() {
	m_texture = new Texture("heightmap.bmp");
	//m_quad = new Quad(m_texture);
	//m_quad2 = new Quad(0);
	m_hft = new HFT(m_texture);
	m_hft->SetPos(Vector(0.0f, -2.0f, 0.0f));
	//m_quad->Attach(m_quad2);

	//((WObject *)m_quad)->SetVel(CVector(0.1f, 0.1f, 0.1f));
}

void TestWorld::UnInit() {
	//m_texture->
}

void TestWorld::Animate(seconds_t seconds) {


	if(GetEngine()->IsDown(SDLK_UP))
		m_hft->SetXRotSpeed(-90.0f);
	else if(GetEngine()->IsDown(SDLK_DOWN))
		m_hft->SetXRotSpeed(90.0f);
	else
		m_hft->SetXRotSpeed(0.0f);

/*
	if(GetEngine()->IsDown(SDLK_RIGHT))
		m_quad->SetYRotSpeed(90.0f);
	else if(GetEngine()->IsDown(SDLK_LEFT))
		m_quad->SetYRotSpeed(-90.0f);
	else
		m_quad->SetYRotSpeed(0.0f);

	if(GetEngine()->IsDown('w'))
		m_quad->SetVel(CVector(0.0f, 0.3f, 0.0f));
	else if(GetEngine()->IsDown('s'))
		m_quad->SetVel(CVector(0.0f, -0.3f, 0.0f));
	else
		m_quad->SetVel(CVector(0, 0, 0));



	((WObject *)m_quad)->Animate(seconds);*/
	//m_bft->SetXRotSpeed(0.1f);

	((WObject *)m_hft)->Animate(seconds);

	//((WObject *)m_quad2)->Animate(seconds);
}

void TestWorld::Draw() {

//((WObject *)m_quad)->Draw();
//((WObject *)m_quad2)->Draw();
	((WObject *)m_hft)->Draw();
}
