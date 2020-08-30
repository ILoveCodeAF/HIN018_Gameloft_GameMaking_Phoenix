#pragma once

#include "GameStatebase.h"

class GSCredit : public GameStateBase
{
public:
	GSCredit();
	~GSCredit();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

private:
};