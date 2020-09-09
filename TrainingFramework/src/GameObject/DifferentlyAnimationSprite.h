#pragma once

#include "Sprite2D.h"
#include <unordered_map>
#include <vector>

class Sprite2D;
class Sprite3D;
class BaseObject;
class Text;

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
	void		Draw() override;
	void		Update(GLfloat deltatime) override;
	//void		Update(GLfloat deltatime, int &x, int &y);
	void		Left(bool is_left);

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

//private:
	//void ChangePosition(GLfloat dw, GLfloat dh);
	//void CaculateWorldMatrix();
};