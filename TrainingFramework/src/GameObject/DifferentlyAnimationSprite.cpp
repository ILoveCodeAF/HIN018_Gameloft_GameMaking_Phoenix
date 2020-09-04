#include "DifferentlyAnimationSprite.h"
#include "Shaders.h"
#include "Models.h"
#include "Texture.h"

#include <filesystem>
#include <fstream>
#include <utility>

namespace fs = std::filesystem;

DifferentlyAnimationSprite::DifferentlyAnimationSprite()
{}

DifferentlyAnimationSprite::DifferentlyAnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime) :
	Sprite2D(model, shader, texture), m_numFrames(numFrames), m_frameTime(frameTime), m_currentTime(0.0f), m_currentFrame(0)
{}

DifferentlyAnimationSprite::DifferentlyAnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color, int numFrames, float frameTime) :
	Sprite2D(model, shader, color), m_numFrames(numFrames), m_frameTime(frameTime), m_currentTime(0.0f), m_currentFrame(0)
{}

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
	std::string dataPath = "..\\Data\\Vertices\\";
	path = dataPath + path;

	int width, height;
	int x, y, w, h;
	std::ifstream infile;

	for (const auto& entry : fs::directory_iterator(path))
	{
		std::cout << entry.path() << std::endl;
		infile.open(entry.path());

		infile >> width >> height;

		Animation animation;
		animation.m_frameTime = 0.1f;

		while (infile >> x >> y >> w >> h)
		{
			std::cout << x << " - " << y << " - " << w << " - " << h << std::endl;
			animation.m_width.push_back(w);
			animation.m_height.push_back(h);
			animation.m_vertices_x0.push_back(float(x) / width);
			animation.m_vertices_x1.push_back(float(x + w) / width);
			animation.m_vertices_y0.push_back(float(height-h-y) / height);
			animation.m_vertices_y1.push_back(float(height-y) / height);
		}
		m_mapAnimation.insert(std::make_pair(entry.path().filename().u8string(), animation));

		infile.close();
	}
	m_currentAnimation = &m_mapAnimation["run"];
	this->SetSize(m_currentAnimation->m_width[m_currentFrame], m_currentAnimation->m_width[m_currentFrame]);
}

void DifferentlyAnimationSprite::setAnimation(std::string animation_name)
{}

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

	if (m_currentTime > m_frameTime)
	{
		m_currentFrame++;
		
		if (m_currentFrame == m_numFrames)
		{
			m_currentFrame = 4;
		}
		this->SetSize(m_currentAnimation->m_width[m_currentFrame], m_currentAnimation->m_height[m_currentFrame]);

		m_currentTime -= m_frameTime;
	}
}
