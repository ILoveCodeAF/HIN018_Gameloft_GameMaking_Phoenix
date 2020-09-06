#include "ScrollAnimationSprite.h"
#include "Shaders.h"
#include "Models.h"
#include "Texture.h"

ScrollAnimationSprite::ScrollAnimationSprite()
{}

ScrollAnimationSprite::ScrollAnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int width, int height, float velocity) :
	Sprite2D(model, shader, texture), m_width(width), m_height(height), m_velocity(velocity), m_offset(0)
{}

ScrollAnimationSprite::ScrollAnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color, int width, int height, float velocity) :
	Sprite2D(model, shader, color), m_width(width), m_height(height), m_velocity(velocity), m_offset(0)
{}

ScrollAnimationSprite::~ScrollAnimationSprite()
{}

void ScrollAnimationSprite::Init()
{
	Sprite2D::Init();
}

void ScrollAnimationSprite::Draw()
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
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_width");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float)m_width);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_offset");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float)m_offset);

	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ScrollAnimationSprite::Update(GLfloat deltatime)
{
	int offset = m_offset;
	offset += m_velocity * deltatime;
	if (offset + m_width / 2 > m_width)
	{
		offset -= m_width / 2;
	}
	m_offset = offset;
}
