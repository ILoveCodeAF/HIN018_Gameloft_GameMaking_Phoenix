#include "DifferentlyAnimationSprite.h"
#include "Shaders.h"
#include "Models.h"
#include "Texture.h"

#include <filesystem>
#include <fstream>
#include <utility>

namespace fs = std::filesystem;

extern GLint screenWidth;
extern GLint screenHeight;

DifferentlyAnimationSprite::DifferentlyAnimationSprite()
{}

DifferentlyAnimationSprite::DifferentlyAnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture) :
	Sprite2D(model, shader, texture), m_numFrames(0), m_frameTime(0.0f), m_currentTime(0.0f), m_currentFrame(0), m_left(1)
{
	m_x = screenWidth / 2;
	m_y = screenHeight * 7 / 8;
	m_currentAnimation = nullptr;
}

DifferentlyAnimationSprite::DifferentlyAnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color) :
	Sprite2D(model, shader, color), m_numFrames(0), m_frameTime(0.0f), m_currentTime(0.0f), m_currentFrame(0), m_left(1)
{
	m_currentAnimation = nullptr;
}

DifferentlyAnimationSprite::~DifferentlyAnimationSprite()
{
	m_currentAnimation = nullptr;
}

void DifferentlyAnimationSprite::Init()
{
	Sprite2D::Init();
}

void DifferentlyAnimationSprite::loadAnimation(std::string path)
{
	std::string dataPath = "..\\Data\\Objects\\";
	std::string animationsPath = dataPath + path + "\\animations";

	int width, height;
	int x = 0, y = 0, w = 0, h = 0, dx = 0, dy = 0, loop = 0, velocity_x, velocity_y;
	float frameTime = 0.0f;
	std::ifstream infile;

	for (const auto& entry : fs::directory_iterator(animationsPath))
	{
		std::cout << entry.path() << std::endl;
		infile.open(entry.path());

		infile >> width >> height >> frameTime >> loop >> velocity_x >> velocity_y;

		Animation animation;
		animation.m_name = entry.path().filename().u8string();
		animation.m_frameTime = frameTime;
		animation.m_loop = loop;
		animation.m_velocity_x = velocity_x;
		animation.m_velocity_y = velocity_y;

		while (infile >> x >> y >> w >> h >> dx >> dy)
		{
			dx = (dx == 0) ? 0 : (x - dx)/3;
			dy = (dy == 0) ? 0 : (y - dy)/3;
			std::cout << x << " - " << y << " - " << w << " - " << h << std::endl;
			animation.m_width.push_back(w);
			animation.m_height.push_back(h);
			animation.m_vertices_x0.push_back(float(x) / width);
			animation.m_vertices_x1.push_back(float(x + w) / width);
			animation.m_vertices_y0.push_back(float(height-h-y) / height);
			animation.m_vertices_y1.push_back(float(height-y) / height);
			animation.m_delta_x.push_back(dx);
			animation.m_delta_y.push_back(dy);
		}
		m_mapAnimation.insert(std::make_pair(animation.m_name, animation));

		infile.close();
	}
	this->SetAnimation(IDLE);
	//this->Set2DPosition(m_x, m_y - m_currentAnimation->m_height[m_currentFrame] / 2);

	std::unordered_map<int, std::string> temp;
	std::string temp_state = "", state = "";
	char key;
	std::string nextState = "";
	std::string statePath = dataPath + path + "\\state.txt";
	infile.open(statePath);
	while (infile >> state >> key >> nextState)
	{
		std::cout << key << '-';
		if (state != temp_state)
		{
			temp_state = state;
			m_stateGraph[state] = temp;
		}
		m_stateGraph[state][key] = nextState;
	}
	infile.close();
}

void DifferentlyAnimationSprite::SetAnimation(std::string animation_name)
{	
	if (m_currentAnimation != nullptr && m_currentAnimation->m_name == DIE)
		return;
	if (m_currentAnimation == nullptr || m_currentAnimation->m_name != animation_name || m_currentFrame == m_numFrames)
	{
		m_currentAnimation = &m_mapAnimation[animation_name];
		this->m_currentFrame = 0;
		this->Set2DPosition(m_x, m_y - m_currentAnimation->m_height[m_currentFrame] / 2);
		this->SetSize(m_currentAnimation->m_width[m_currentFrame], m_currentAnimation->m_height[m_currentFrame]);
		this->m_numFrames = m_currentAnimation->m_width.size();
		this->m_frameTime = m_currentAnimation->m_frameTime;
		//this->ChangePosition(m_currentAnimation->m_delta_x[m_currentFrame], m_currentAnimation->m_delta_y[m_currentFrame]);
		this->Draw();
	}
}

void DifferentlyAnimationSprite::ResetAnimation(std::string animation_name)
{
	if (m_currentAnimation != nullptr && m_currentAnimation->m_name == DIE)
		return;
	m_currentAnimation = &m_mapAnimation[animation_name];
	this->m_currentFrame = 0;
	this->Set2DPosition(m_x, m_y - m_currentAnimation->m_height[m_currentFrame] / 2);
	this->SetSize(m_currentAnimation->m_width[m_currentFrame], m_currentAnimation->m_height[m_currentFrame]);
	this->m_numFrames = m_currentAnimation->m_width.size();
	this->m_frameTime = m_currentAnimation->m_frameTime;
	//this->ChangePosition(m_currentAnimation->m_delta_x[m_currentFrame], m_currentAnimation->m_delta_y[m_currentFrame]);
	this->Draw();
}

void DifferentlyAnimationSprite::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

int DifferentlyAnimationSprite::GetPositionX()
{
	return m_x;
}

int DifferentlyAnimationSprite::GetPositionY()
{
	return m_y;
}

void DifferentlyAnimationSprite::Draw()
{
	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;

	matrixWVP = m_WorldMat;//* m_pCamera->GetLookAtCamera();

	if (m_pTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
		if (m_pShader->iTextureLoc[0] != -1)
			glUniform1i(m_pShader->iTextureLoc[0], 0);
	}
	else
	{
		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_color");
		if (iTempShaderVaribleGLID != -1)
			glUniform4f(iTempShaderVaribleGLID, m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	}


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_uv");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_UV);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_alpha");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, 1.0);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_matMVP");
	if (iTempShaderVaribleGLID != -1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, matrixWVP.m[0]);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_left");
	if (iTempShaderVaribleGLID != -1)
		glUniform1i(iTempShaderVaribleGLID, m_left);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_numFrames");
	if (iTempShaderVaribleGLID != -1)
		glUniform1i(iTempShaderVaribleGLID, m_numFrames);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentFrame");
	if (iTempShaderVaribleGLID != -1)
		glUniform1i(iTempShaderVaribleGLID, m_currentFrame);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_vertices_x0");
	if (iTempShaderVaribleGLID != -1)
		glUniform1fv(iTempShaderVaribleGLID, m_currentAnimation->m_vertices_x0.size(), &(m_currentAnimation->m_vertices_x0)[0]);
	
	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_vertices_x1");
	if (iTempShaderVaribleGLID != -1)
		glUniform1fv(iTempShaderVaribleGLID, m_currentAnimation->m_vertices_x1.size(), &(m_currentAnimation->m_vertices_x1)[0]);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_vertices_y0");
	if (iTempShaderVaribleGLID != -1)
		glUniform1fv(iTempShaderVaribleGLID, m_currentAnimation->m_vertices_y0.size(), &(m_currentAnimation->m_vertices_y0)[0]);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_vertices_y1");
	if (iTempShaderVaribleGLID != -1)
		glUniform1fv(iTempShaderVaribleGLID, m_currentAnimation->m_vertices_y1.size(), &(m_currentAnimation->m_vertices_y1)[0]);

	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void DifferentlyAnimationSprite::Update(GLfloat deltatime)
{
	m_currentTime += deltatime;
	
	//todo

	if (m_currentTime > m_frameTime)
	{
		m_currentFrame++;
		
		if (m_currentFrame == m_numFrames)
		{
			if (m_currentAnimation->m_loop == -1)
			{
				m_currentTime -= m_frameTime;
				if (m_currentAnimation->m_name == DIE)
				{
					m_currentFrame = m_numFrames - 1;
					return;
				}
				//m_currentFrame = 0;
				this->SetAnimation(IDLE);
				//this->Set2DPosition(m_x, m_y - m_currentAnimation->m_height[m_currentFrame] / 2);
				
				return;
			}
			else
			{
				m_currentFrame = m_currentAnimation->m_loop;
			}
			
		}
		//this->ChangePosition(m_currentAnimation->m_delta_x[m_currentFrame], m_currentAnimation->m_delta_y[m_currentFrame]);
		this->SetSize(m_currentAnimation->m_width[m_currentFrame], m_currentAnimation->m_height[m_currentFrame]);
		this->Set2DPosition(m_x, m_y - m_currentAnimation->m_height[m_currentFrame] / 2);
		m_currentTime -= m_frameTime;
	}
}
/*
void DifferentlyAnimationSprite::Update(GLfloat deltatime, int &x, int &y)
{
	m_currentTime += deltatime;

	
		
	if (m_currentTime > m_frameTime)
	{
		m_currentFrame++;

		if (m_currentFrame == m_numFrames)
		{
			if (m_currentAnimation->m_loop == -1)
			{
				this->SetAnimation("idle");
				m_currentTime -= m_frameTime;
				return;
			}
			else
			{
				m_currentFrame = m_currentAnimation->m_loop;
			}

		}
		//todo
		//this->ChangePosition(m_currentAnimation->m_delta_x[m_currentFrame], m_currentAnimation->m_delta_y[m_currentFrame]);
		this->SetSize(m_currentAnimation->m_width[m_currentFrame], m_currentAnimation->m_height[m_currentFrame]);

		m_currentTime -= m_frameTime;
	}
}
*/

/*void DifferentlyAnimationSprite::ChangePosition(GLfloat delta_width, GLfloat delta_height)
{
	if (delta_width || delta_height)
	{
		m_Vec2DPos = m_Vec2DPos + Vector2(delta_width, delta_height);
		float xx = (2.0 * (m_Vec2DPos.x + delta_width)) / screenWidth - 1.0;
		float yy = 1.0 - (2.0 * (m_Vec2DPos.y + delta_height)) / screenHeight;
		m_Vec3Position = Vector3(xx, yy, 1.0);

		CaculateWorldMatrix();
	}
	
}

void DifferentlyAnimationSprite::CaculateWorldMatrix()
{
	Matrix m_Sc, m_T;
	m_Sc.SetScale(m_Vec3Scale);
	m_T.SetTranslation(m_Vec3Position);
	m_WorldMat = m_Sc * m_T;
}
*/
void  DifferentlyAnimationSprite::Left(bool is_left)
{
	if (is_left) 
	{
		m_left = -1;
	}
	else
	{
		m_left = 1;
	}
}

void DifferentlyAnimationSprite::ChangeAnimation(int key)
{
	if (m_stateGraph.find(m_currentAnimation->m_name) != m_stateGraph.end())
	{
		if (m_stateGraph[m_currentAnimation->m_name].find(key) != m_stateGraph[m_currentAnimation->m_name].end())
		{
			if (m_stateGraph[m_currentAnimation->m_name][key] != "none")
			{
				this->SetAnimation(m_stateGraph[m_currentAnimation->m_name][key]);
			}
		}
	}
		
}