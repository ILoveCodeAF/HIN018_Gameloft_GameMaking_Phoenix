#pragma once

#include "Sprite2D.h"

class Sprite2D;
class Sprite3D;
class BaseObject;
class Text;

class AnimationSprite : public Sprite2D
{
public:
	AnimationSprite();
	AnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	AnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color, int numFrames, float frameTime);
	~AnimationSprite();

	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;


protected:
	int m_numFrames;
	int m_currentFrame;
	float m_frameTime;
	float m_currentTime;

};