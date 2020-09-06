#include "GSPlay.h"

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

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto backGround = std::make_shared<Sprite2D>(model, shader, texture);
	backGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	backGround->SetSize(screenWidth, screenHeight);
	m_listBackGround.push_back(backGround);

	//foregound
	shader = ResourceManagers::GetInstance()->GetShader("ScrollAnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("cloud");
	auto cloud = std::make_shared<ScrollAnimationSprite>(model, shader, texture, 2000, 496, 50);
	cloud->Set2DPosition(screenWidth / 2, screenHeight / 2);
	cloud->SetSize(screenWidth, screenHeight);
	m_listBackGround.push_back(cloud);

	//Tohsaka Rin
	shader = ResourceManagers::GetInstance()->GetShader("DifferentlyAnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("sprite_sheet_tohsaka_rin");
	auto tohsaka_rin = std::make_shared<DifferentlyAnimationSprite>(model, shader, texture);
	tohsaka_rin->loadAnimation("tohsaka_rin");
	tohsaka_rin->Set2DPosition(Vector2(500, 300));
	//tohsaka_rin->SetSize(75, 112);
	m_listAnimation.push_back(tohsaka_rin);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	std::cout << char(key) << std::endl;
	if (bIsPressed)
	{
		switch (key)
		{
		case 'A':
			m_listAnimation[0]->Left(true);
			m_listAnimation[0]->SetAnimation("run");
			break;
		case 'D':
			m_listAnimation[0]->Left(false);
			m_listAnimation[0]->SetAnimation("run");
			break;
		case 'K':
			m_listAnimation[0]->SetAnimation("kick");
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case 'A':
			m_listAnimation[0]->SetAnimation("idle");
			break;
		case 'D':
			m_listAnimation[0]->SetAnimation("idle");
			break;
		case 'K':
			break;
		default:
			break;
		}
	}
	
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
	for (auto bg : m_listBackGround)
	{
		bg->Update(deltaTime);
	}

	for (auto obj : m_listAnimation)
	{
		obj->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	for (auto obj : m_listBackGround)
	{
		obj->Draw();
	}

	for (auto obj : m_listAnimation)
	{
		obj->Draw();
	}
	m_score->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}