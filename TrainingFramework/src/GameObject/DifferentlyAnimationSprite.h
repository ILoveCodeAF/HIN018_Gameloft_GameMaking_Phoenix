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
	float m_frameTime;
	std::vector<int> m_width;
	std::vector<int> m_height;
	std::vector<float> m_vertices_x0;
	std::vector<float> m_vertices_x1;
	std::vector<float> m_vertices_y0;
	std::vector<float> m_vertices_y1;
};

class DifferentlyAnimationSprite : public Sprite2D
{
public:
	DifferentlyAnimationSprite();
	DifferentlyAnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	DifferentlyAnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color, int numFrames, float frameTime);
	~DifferentlyAnimationSprite();

	void		Init() override;
	void		loadAnimation(std::string path);
	void		setAnimation(std::string animation_name);
	void		Draw() override;
	void		Update(GLfloat deltatime) override;


protected:
	int m_numFrames;
	int m_currentFrame;
	float m_frameTime;
	float m_currentTime;
	Animation* m_currentAnimation;
	
	std::unordered_map<std::string, Animation>  m_mapAnimation;
};