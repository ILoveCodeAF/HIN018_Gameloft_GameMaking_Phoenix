#include "GSHelp.h"

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

GSHelp::GSHelp()
{}

GSHelp::~GSHelp()
{}

void GSHelp::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_credit");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);


	//play OK
	texture = ResourceManagers::GetInstance()->GetTexture("btn_ok");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, screenHeight - 55);
	button->SetSize(100, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");

	char* info = "W : Jump";
	auto text = std::make_shared< Text>(shader, font, info, TEXT_COLOR::WHITE, 1.0);
	text->Set2DPosition(Vector2(100, 200));
	m_listHelp.push_back(text);

	char* info1 = "A : Run/Jump to the left";
	text = std::make_shared< Text>(shader, font, info1, TEXT_COLOR::WHITE, 1.0);
	text->Set2DPosition(Vector2(100, 220));
	m_listHelp.push_back(text);
	
	char* info2 = "D : Run/Jump to the right";
	text = std::make_shared< Text>(shader, font, info2, TEXT_COLOR::WHITE, 1.0);
	text->Set2DPosition(Vector2(100, 240));
	m_listHelp.push_back(text);

	char* info4 = "J : Punch";
	text = std::make_shared< Text>(shader, font, info4, TEXT_COLOR::WHITE, 1.0);
	text->Set2DPosition(Vector2(100, 280));
	m_listHelp.push_back(text);

	char* info3 = "K : Kick";
	text = std::make_shared< Text>(shader, font, info3, TEXT_COLOR::WHITE, 1.0);
	text->Set2DPosition(Vector2(100, 260));
	m_listHelp.push_back(text);
}

void GSHelp::Exit()
{}

void GSHelp::Pause()
{}

void GSHelp::Resume()
{}

void GSHelp::HandleEvents()
{}

void GSHelp::HandleKeyEvents(int key, bool bIsPressed)
{}

void GSHelp::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSHelp::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSHelp::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listHelp)
	{
		it->Draw();
	}
}

