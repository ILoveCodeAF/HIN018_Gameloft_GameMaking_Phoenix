#pragma once

#include "Sprite2D.h"

class Sprite2D;
class Sprite3D;
class BaseObject;
class Text;

class ScrollAnimationSprite : public Sprite2D
{
public:
	ScrollAnimationSprite();
	ScrollAnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int width, int height, float velocity);
	ScrollAnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color, int width, int height, float velocity);
	~ScrollAnimationSprite();

	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;


protected:
	float m_velocity;
	int m_width;
	int m_height;
	int m_offset;
};