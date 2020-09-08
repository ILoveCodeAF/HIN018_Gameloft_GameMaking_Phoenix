#include "StageMap.h"
#include <stdlib.h>
#include <time.h>
#include "GameManager/ResourceManagers.h"
#include "ScrollAnimationSprite.h"

StageMap::StageMap():
	m_width(496), m_height(1000)
{}

StageMap::StageMap(int width, int height):
	m_width(width), m_height(height)
{}

StageMap::~StageMap()
{}

void StageMap::Generate()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	auto backGround = std::make_shared<Sprite2D>(model, shader, texture);
	backGround->Set2DPosition(m_width / 2, m_height / 2);
	backGround->SetSize(m_width, m_height);
	m_listBackground.push_back(backGround);


	shader = ResourceManagers::GetInstance()->GetShader("ScrollAnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("cloud");
	auto cloud = std::make_shared<ScrollAnimationSprite>(model, shader, texture, 2000, 496, 50);
	cloud->Set2DPosition(m_width / 2, m_height / 2);
	cloud->SetSize(m_width, m_height);
	m_listBackground.push_back(cloud);



	texture = ResourceManagers::GetInstance()->GetTexture("hanging");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto hanging = std::make_shared<Sprite2D>(model, shader, texture);


	m_listLanding.clear();

	srand(time(NULL));
	int len = m_width / 5;
	int x = rand() % (m_width-len);
	int y = m_height * 2 / 3;
	
	m_listLanding.push_back(std::make_pair(Vector2(x, y), Vector2(x+len, y)));
	hanging->SetSize(len, len/6);
	hanging->Set2DPosition(x+ len/2, y+ len/12);
	m_listBackground.push_back(hanging);

	y = m_height * 7 / 8;
	m_listLanding.push_back(std::make_pair(Vector2(0, y), Vector2(m_width, y)));
	texture = ResourceManagers::GetInstance()->GetTexture("land");
	
	len /= 4;
	for (int i = 0; i < m_width / len + 1; ++i)
	{
		auto land = std::make_shared<Sprite2D>(model, shader, texture);
		land->SetSize(len, len);
		land->Set2DPosition(i * len + len / 2, y + len / 2);
		m_listBackground.push_back(land);
	}
}

void StageMap::Draw()
{
	for (auto obj : m_listBackground)
	{
		obj->Draw();
	}
}

void StageMap::Update(float deltaTime)
{
	for (auto obj : m_listBackground)
	{
		obj->Update(deltaTime);
	}
}