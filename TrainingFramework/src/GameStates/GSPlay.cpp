#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include <stdlib.h>
#include <time.h>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

#define KEY_W	1<<0
#define KEY_K	1<<1
#define KEY_J	1<<2
#define KEY_A	1<<3
#define KEY_D	1<<4

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	srand(time(NULL));
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
	m_mainCharacter = std::make_shared<Character>(model, shader, texture, 3000, 500);
	m_mainCharacter->loadAnimation("tohsaka_rin");
	//m_mainCharacter->Set2DPosition(Vector2(500, 300));
	//tohsaka_rin->SetSize(75, 112);

	texture = ResourceManagers::GetInstance()->GetTexture("thorny");
	auto thorny = std::make_shared<Character>(model, shader, texture, 3000, 10); 
	thorny->loadAnimation("thorny", 0.5f);
	thorny->SetPositionX(rand() % screenWidth);
	m_listEnemyCharacter.push_back(thorny);
	m_controlUnitCommand.push_back("");
	m_controlUnitDuration.push_back(0.0f);

	texture = ResourceManagers::GetInstance()->GetTexture("guard");
	auto guard = std::make_shared<Character>(model, shader, texture, 30000, 10);
	guard->loadAnimation("guard", 0.25f);
	guard->SetPositionX(rand() % screenWidth);
	m_listEnemyCharacter.push_back(guard);
	m_controlUnitCommand.push_back("");
	m_controlUnitDuration.push_back(0.0f);

	/*texture = ResourceManagers::GetInstance()->GetTexture("wave_attack");
	auto wave_attack = std::make_shared<AttackAnimation>(model, shader, texture, 200, Vector2(0, 0), 2);
	wave_attack->loadAnimation("wave_attack");
	m_mapAttackAnimation["wave_attack"] = wave_attack;

	texture = ResourceManagers::GetInstance()->GetTexture("light_ball_attack");
	auto light_ball_attack = std::make_shared<AttackAnimation>(model, shader, texture, 200, Vector2(0, 0), 2);
	light_ball_attack->loadAnimation("light_ball_attack");
	m_mapAttackAnimation["light_ball_attack"] = light_ball_attack;*/

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
	m_key = 0;
	m_jumpDuration = 0.0f;
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
			m_mainCharacter->SetStateAttacking(false);
			m_mainCharacter->Left(true);
			m_key |= KEY_A;
			break;
		case 'D':
			m_mainCharacter->SetStateAttacking(false);
			m_mainCharacter->Left(false);
			m_key |= KEY_D;
			break;
		case 'W':
			m_mainCharacter->SetStateAttacking(false);
			m_key |= KEY_W;
			break;
		case 'K':
			m_mainCharacter->SetStateAttacking(false);
			m_key |= KEY_K;
			break;

		case 'J':
			m_mainCharacter->SetStateAttacking(false);
			m_key |= KEY_J;
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
			m_key &= ~(KEY_A);
			break;
		case 'D':
			m_key &= ~(KEY_D);
			break;
		case 'W':
			m_key &= ~(KEY_W);
			break;
		case 'K':
			m_key &= ~(KEY_K);
			break;
		case 'J':
			m_key &= ~(KEY_J);
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

	Control(m_mainCharacter, m_key, deltaTime);
	ControlUnit(deltaTime);
	
	for (auto obj : m_listEnemyCharacter)
	{
		obj->Update(deltaTime);
	}
	DetectCollision();
	
	for (auto obj : m_listEnemyAttack)
	{
		if (obj->IsAlive())
			obj->Update(deltaTime);
	}

	for (auto obj : m_listMCAttack)
	{
		if (obj->IsAlive())
			obj->Update(deltaTime);
	}
	CleanUp();
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
	//m_score->Draw();
	
	
	for (auto obj : m_listEnemyCharacter)
	{
		obj->Draw();
	}

	m_mainCharacter->Draw();

	/*for (auto obj : m_listEnemyAttack)
	{
		if (obj->Alive())
			obj->Draw();
	}

	for (auto obj : m_listMCAttack)
	{
		if(obj->Alive())
			obj->Draw();
	}*/
}

void GSPlay::Control(std::shared_ptr<Character> character, int key, float deltaTime, bool isEnemy)
{
	int x = character->GetPositionX();
	int y = character->GetPositionY();
	int velocityX = 160;
	int velocityY = 180;

	float jumpDuration = character->GetJumpDuration();

	if (jumpDuration > 0.0f || y < screenHeight * 7 / 8)
	{
		/*if (!character->JumpCauseDamage() && key & KEY_W)
		{
			character->SetJumpCauseDamage(true);
			jumpDuration = 1.2f;
			character->ResetAnimation(JUMP);
		}*/
		if (key & KEY_A && !(key & KEY_D))
		{
			x -= deltaTime * velocityX;

		}
		else if (key & KEY_D && !(key & KEY_A))
		{
			x += deltaTime * velocityX;
		}
		if (jumpDuration > 0.6f)
		{
			y -= deltaTime * velocityY;
		}
		else
		{
			y += deltaTime * velocityY;
		}
		jumpDuration -= deltaTime;
		character->SetJumpDuration(jumpDuration);
	}
	else if (key & KEY_W)
	{
		character->SetJumpCauseDamage(true);
		character->ResetAnimation(JUMP);
		character->SetJumpDuration(1.2f);
	}
	else if (key & KEY_K && !(key & KEY_J))
	{
		m_mainCharacter->SetStateAttacking(true);
		character->SetAnimation(KICK);
		if (character->Attack())
		{
			m_listMCAttack.push_back(Attack(character, character->GetWidth() / 2, character->GetHeight(), 1.0f));
		}
		//CreateAttack(character, isEnemy, "wave_attack");
		
	}
	else if (key & KEY_J && !(key & KEY_K))
	{
		m_mainCharacter->SetStateAttacking(true);
		//if (rand() % 2)
		//character->SetAnimation(PUNCH);
		//else
		character->SetAnimation(PUNCH);
		if (character->Attack())
		{
			m_listMCAttack.push_back(Attack(character, character->GetWidth() / 2, character->GetHeight(), 1.0f));
		}
	}
	else if (key & KEY_A && !(key & KEY_D))
	{
		x -= deltaTime * velocityX;
		character->SetAnimation(RUN);
	}
	else if (key & KEY_D && !(key & KEY_A))
	{
		x += deltaTime * velocityX;
		character->SetAnimation(RUN);
	}
	else
	{
		if(!m_mainCharacter->Attacking())
			character->SetAnimation(IDLE);
	}

	if (x < 0)
		x = 0;
	if (x > screenWidth)
		x = screenWidth;
	if (y > screenHeight * 7 / 8)
		y = screenHeight * 7 / 8;
	character->Set2DPosition(x, y);
	character->Update(deltaTime);

}

/*void GSPlay::CreateAttack(std::shared_ptr<Character> character, bool isEnemy, std::string type)
{
	if (character->Attack())
	{
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto shader = ResourceManagers::GetInstance()->GetShader("DifferentlyAnimationShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture(type);

		auto attack = std::make_shared<AttackAnimation>(model, shader, texture, 200, Vector2(0, 0), 2);
		attack->loadAnimation(type);
		attack->SetDirection(200 * character->GetDirection(), 0);
		attack->SetDuration(4.0f);
		attack->Left(character->GetDirection() == -1);
		attack->SetPosition(character->GetPositionX(), character->GetPositionY());
		if (isEnemy)
		{
			m_listEnemyAttack.push_back(attack);
		}
		else
		{
			m_listMCAttack.push_back(attack);
		}
	}
}*/





void GSPlay::SetNewPostionForBullet()
{
}

bool GSPlay::IsCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	if (x1 < x2 && x1 + w1 < x2)
		return false;
	if (x2 < x1 && x2 + w2 < x1)
		return false;
	if (y1 > y2 && y1 - h1 > y2)
		return false;
	if (y2 > y1 && y2 - h2 > y1)
		return false;
	return true;
}

void GSPlay::DetectCollision(std::shared_ptr<Character> character, std::vector < std::shared_ptr<HitBox>>& attacks)
{
	if (character->Alive())
		for (auto hitBox : attacks)
		{
			if (hitBox->IsAlive())
			{
				int w = character->GetWidth();
				int h = character->GetHeight();
				int y = character->GetPositionY();
				int x = character->GetPositionX() - w / 2;
				if (hitBox->DetectCollision(x, y, w, h))
				{
					character->GotAttacked(hitBox->GetDamage());
					hitBox->Expire();
				}
			}

		}
}
void GSPlay::DetectCollision()
{
	DetectCollision(m_mainCharacter, m_listEnemyAttack);
	for (auto enemy : m_listEnemyCharacter)
	{
		if (enemy->Alive())
		{
			DetectCollision(enemy, m_listMCAttack);
			if (!enemy->Alive())
			{
				m_mainCharacter->GotAttacked(-enemy->GetMaxHP() / 10);
			}
		}
		
	}
	if (m_mainCharacter->GetState() == JUMP)
	{
		int w1 = m_mainCharacter->GetWidth();
		int h1 = m_mainCharacter->GetHeight();
		int x1 = m_mainCharacter->GetPositionX() - w1 / 2;
		int y1 = m_mainCharacter->GetPositionY();
		for (auto enemy : m_listEnemyCharacter)
		{
			int w2 = enemy->GetWidth();
			int h2 = enemy->GetHeight();
			int x2 = enemy->GetPositionX() - w2 / 2;
			int y2 = enemy->GetPositionY() - h2 * 3 / 4;
			if (m_mainCharacter->JumpCauseDamage() && IsCollision(x1, y1, w1, h1, x2, y2, w2, h2))
			{
				enemy->GotAttacked(300);
				m_mainCharacter->SetJumpCauseDamage(false);
			}
		}
	}
}

std::shared_ptr<HitBox> GSPlay::Attack(std::shared_ptr<Character> character, int w, int h, int duration)
{
	int x = character->GetPositionX();
	int y = character->GetPositionY();
	if (character->GetDirection() == -1) {
		x -= w;
	}
	return std::make_shared<HitBox>(x, y, w, h, character->GetAttackDamage(), duration);
}

void GSPlay::ControlUnit(float deltaTime)
{
	for (int i = 0; i < m_listEnemyCharacter.size(); ++i)
	{
		if (m_listEnemyCharacter[i]->Alive())
		{
			m_controlUnitDuration[i] -= deltaTime;
			if (m_controlUnitDuration[i] <= 0.0f)
			{
				m_controlUnitDuration[i] = rand() % 5;
				switch (rand() % 4)
				{
				case 0:
					m_controlUnitCommand[i] = IDLE;
					break;
				case 1:
					m_listEnemyCharacter[i]->Left(true);
					m_controlUnitCommand[i] = RUN;
					break;
				case 2:
					m_listEnemyCharacter[i]->Left(false);
					m_controlUnitCommand[i] = RUN;
					break;
				case 3:
					m_controlUnitCommand[i] = ATTACK;
					break;
				default:
					break;
				}
			}
			else 
			{
				Control(m_listEnemyCharacter[i], m_controlUnitCommand[i], deltaTime, true);
			}
		}
	}
}

void GSPlay::Control(std::shared_ptr<Character> character, std::string command, float deltaTime, bool isEnemy)
{
	character->SetAnimation(command);
	int x = character->GetPositionX();
	int y = character->GetPositionY();
	int velocityX = rand() %150 + 50;
	int velocityY = rand() % 150 + 50;

	if (command == IDLE)
	{
		return;
		//do nothing
	}
	else if (command == RUN)
	{
		x += velocityX * deltaTime * character->GetDirection();
		if (x < 0)
			x = 0;
		if (x > screenWidth)
			x = screenWidth;
		if (y > screenHeight * 7 / 8)
			y = screenHeight * 7 / 8;
		character->Set2DPosition(x, y);
	}
	else if (command == ATTACK)
	{
		if (character->Attack())
		{
			m_listEnemyAttack.push_back(Attack(character, character->GetWidth() / 2, character->GetHeight(), 1.0f));
		}
	}	
	character->Update(deltaTime);
}

void GSPlay::CleanUp(std::vector < std::shared_ptr<HitBox>> &attacks)
{
	int left = 0, right = attacks.size() - 1;
	while (left <= right)
	{
		if (!attacks[left]->IsAlive())
		{
			if (left < right)
			{
				auto temp = attacks[left];
				attacks[left] = attacks[right];
				attacks[right] = temp;
			}
			right--;
		}
		else
		{
			left++;
		}
	}
	while (right < attacks.size())
		attacks.pop_back();
}
void GSPlay::CleanUp()
{
	CleanUp(m_listEnemyAttack);
	CleanUp(m_listMCAttack);
}