#include "HitBox.h"
#include "GameManager/ResourceManagers.h"

HitBox::HitBox(int x, int y, int w, int h, int dmg, float duration, bool OfEnermy):
	m_x(x), m_y(y), m_w(w), m_h(h), m_dmg(dmg), m_duration(duration), m_ofEnermy(OfEnermy), m_halfDuration(duration/2), m_direction(0, 0)
{
	m_animation = nullptr;
	time = 0.0f;
	m_yClone = m_y;
}

HitBox::~HitBox()
{
}

int HitBox::GetDamage()
{
	return m_dmg;
}

void HitBox::Expire()
{
	m_duration = -1.0f;
}

bool HitBox::DetectCollision(int x, int y, int w, int h)
{
	if (m_x > x + w)
		return false;
	if (m_x + m_w < x)
		return false;
	if (m_y < y - h)
		return false;
	if (m_y - m_h > y)
		return false;
	return true;
}

void HitBox::Update(float deltaTime)
{
	if (IsAlive())
	{
		//std::cout << m_x << '-' << m_y << '\n';
		m_duration -= deltaTime;
		m_x += deltaTime * m_direction.x;
		//m_y += deltaTime * m_direction.y;
		// x= v0.t - gt^2 /2
		time += 10*deltaTime;
		float g = 10.0f;
		if (m_direction.y)
			m_y = m_yClone - m_direction.y * time + g * time * time / 2;
		
		if (m_animation)
		{
			//std::cout << "update in hit box\n";
			m_animation->Set2DPosition(m_x + m_w / 2, m_y - m_h / 2);
			m_animation->SetSize(m_w, m_h);
			m_animation->Update(deltaTime);
		}
	}
}

bool HitBox::IsAlive()
{
	return m_duration > 0.0f;
}

void HitBox::Draw()
{
	//std::cout << "draw\n";
	//std::cout << "draw wth\n";
	if (m_animation && IsAlive())
	{
		m_animation->Set2DPosition(m_x + m_w / 2, m_y - m_h / 2);
		m_animation->SetSize(m_w, m_h);
		//std::cout << "draw\n";
		//std::cout << "draw in hit box " << m_x << '-' <<m_y<< "\n";
		m_animation->Draw();
	}
}

void HitBox::loadAnimation(std::string name, int numFrames, int frameTime)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(name);

	m_animation = std::make_shared<AnimationSprite>(model, shader, texture, numFrames, frameTime);
	///m_animation->Set2DPosition(400, 400);
	//m_animation->SetSize(50, 50);
}


void HitBox::SetAnimation(std::shared_ptr<AnimationSprite> animation)
{
	m_animation = animation;
}

void HitBox::SetDirection(int x, int y)
{
	m_direction = Vector2(x, y);
}

void HitBox::SetDuration(float duration)
{
	m_duration = duration;
}