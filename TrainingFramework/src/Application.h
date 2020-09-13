#pragma once
#include "Singleton.h"
#include "GameConfig.h"
#include "soloud.h"
#include "soloud_wav.h"


class Application : public CSingleton<Application>
{
public:
	Application();
	~Application();
	void		Init();
	void		Update( GLfloat deltaTime);
	void		Render();
	void		HandleKeyEvent(unsigned char key, bool bIsPresseded);
	void		HandleTouchEvent(GLint x, GLint y, bool bIsPresseded);
	void		Exit();
	void		Play(std::string songName);

private:
	// Declare some variables
	SoLoud::Soloud soloud; // Engine core
	SoLoud::Wav sample;    // One sample
};

