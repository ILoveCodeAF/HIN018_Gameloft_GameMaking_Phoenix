#pragma once

#include "Sprite2D.h"
#include <unordered_map>
#include <vector>

class Sprite2D;
class Sprite3D;
class BaseObject;
class Text;

#define RUN		"run"
#define IDLE	"idle"
#define JUMP	"jump"
#define PUNCH	"punch"
#define KICK	"kick"
#define FALL	"fall"
#define DIE		"die"

struct Animation 
{
	std::string m_name;
	float m_frameTime;
	int m_loop;
	int m_velocity_x;
	int m_velocity_y;
	std::vector<int> m_width;
	std::vector<int> m_height;
	std::vector<float> m_vertices_x0;
	std::vector<float> m_vertices_x1;
	std::vector<float> m_vertices_y0;
	std::vector<float> m_vertices_y1;
	std::vector<int> m_delta_x;
	std::vector<int> m_delta_y;
};

class DifferentlyAnimationSprite : public Sprite2D
{
public:
	DifferentlyAnimationSprite();
	DifferentlyAnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	DifferentlyAnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color);
	~DifferentlyAnimationSprite();

	void		Init() override;
	void		loadAnimation(std::string path);
	void		SetAnimation(std::string animation_name);
	void		ResetAnimation(std::string animation_name);
	void		Draw() override;
	void		Update(GLfloat deltatime) override;
	//void		Update(GLfloat deltatime, int &x, int &y);
	void		Left(bool is_left);
	void		ChangeAnimation(int key);
	void		SetPosition(int x, int y);
	int			GetPositionX();
	int			GetPositionY();
	int			GetDirection() { return m_left; }
	int			GetHeight() { return m_currentAnimation->m_height[m_currentFrame]; }
	int			GetWidth() { return m_currentAnimation->m_width[m_currentFrame]; }
	int			GetCurrentFrame() { return m_currentFrame; }
	std::string GetState() { return m_currentAnimation->m_name; }

protected:
	int m_x;
	int m_y;
	int m_left;
	int m_numFrames;
	int m_currentFrame;
	float m_frameTime;
	float m_currentTime;
	Animation* m_currentAnimation;
	
	std::unordered_map<std::string, Animation>  m_mapAnimation;
	std::unordered_map<std::string, std::unordered_map<int, std::string>> m_stateGraph;

//private:
	//void ChangePosition(GLfloat dw, GLfloat dh);
	//void CaculateWorldMatrix();
};