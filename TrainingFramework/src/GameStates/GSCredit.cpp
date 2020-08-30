#include "GSCredit.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSCredit::GSCredit()
{}

GSCredit::~GSCredit()
{}

void GSCredit::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");

	char* info = "LE CONG HIEU - HVCNBCVT";
	m_profile = std::make_shared< Text>(shader, font, info, TEXT_COLOR::WHITE, 1.0);
	m_profile->Set2DPosition(Vector2(100, 200));
}

void GSCredit::Exit()
{}

void GSCredit::Pause()
{}

void GSCredit::Resume()
{}

void GSCredit::HandleEvents()
{}

void GSCredit::HandleKeyEvents(int key, bool bIsPressed)
{}

void GSCredit::HandleTouchEvents(int x, int y, bool bIsPressed)
{}

void GSCredit::Update(float deltaTime)
{}

void GSCredit::Draw()
{
	m_BackGround->Draw();
	m_profile->Draw();
}
