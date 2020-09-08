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
	//auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	////BackGround
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//auto backGround = std::make_shared<Sprite2D>(model, shader, texture);
	//backGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	//backGround->SetSize(screenWidth, screenHeight);
	//m_listBackGround.push_back(backGround);

	m_map = std::make_shared<StageMap>(screenWidth, screenHeight);
	m_map->Generate();

	//foregound
	/*shader = ResourceManagers::GetInstance()->GetShader("ScrollAnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("cloud");
	auto cloud = std::make_shared<ScrollAnimationSprite>(model, shader, texture, 2000, 496, 50);
	cloud->Set2DPosition(screenWidth / 2, screenHeight / 2);
	cloud->SetSize(screenWidth, screenHeight);
	m_listBackGround.push_back(cloud);*/

	//Tohsaka Rin
	auto shader = ResourceManagers::GetInstance()->GetShader("DifferentlyAnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("sprite_sheet_tohsaka_rin");
	//auto tohsaka_rin = std::make_shared<DifferentlyAnimationSprite>(model, shader, texture);
	//tohsaka_rin->loadAnimation("tohsaka_rin");
	//tohsaka_rin->Set2DPosition(Vector2(500, 300));
	////tohsaka_rin->SetSize(75, 112);
	//m_listAnimation.push_back(tohsaka_rin);
	m_mainCharacter = std::make_shared<Character>(model, shader, texture, 3000, 10);
	m_mainCharacter->loadAnimation("tohsaka_rin");
	//m_mainCharacter->Set2DPosition(Vector2(500, 300));
	//tohsaka_rin->SetSize(75, 112);


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
	std::cout << char(key);
	if (bIsPressed)
	{
		switch (key)
		{
		case 'A':
			m_mainCharacter->Left(true);
			m_mainCharacter->SetAnimation("run");
			break;
		case 'D':
			m_mainCharacter->Left(false);
			m_mainCharacter->SetAnimation("run");
			break;
		case 'W':
			m_mainCharacter->SetAnimation("jump");
			break;
		case 'K':
			m_mainCharacter->SetAnimation("kick");
			break;
		case 'J':
			m_mainCharacter->SetAnimation("punch");
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
			m_mainCharacter->SetAnimation("idle");
			break;
		case 'D':
			m_mainCharacter->SetAnimation("idle");
			break;
		case 'K':
			break;
		case 'J':
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
	/*for (auto bg : m_listBackGround)
	{
		bg->Update(deltaTime);
	}*/
	m_map->Update(deltaTime);

	/*for (auto obj : m_listAnimation)
	{
		obj->Update(deltaTime);
	}*/
	m_mainCharacter->Update(deltaTime);
}

void GSPlay::Draw()
{
	/*for (auto obj : m_listBackGround)
	{
		obj->Draw();
	}*/

	m_map->Draw();

	/*for (auto obj : m_listAnimation)
	{
		obj->Draw();
	}*/
	m_score->Draw();
	m_mainCharacter->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}