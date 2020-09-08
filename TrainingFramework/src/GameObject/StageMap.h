#pragma once

#include <vector>
#include "U_Math.h"
#include <utilities.h>
#include "Sprite2D.h"
#include "BaseObject.h"

class StageMap
{
public:
	StageMap();
	StageMap(int width, int height);
	~StageMap();
	
	void Generate();
	void Draw();
	void Update(float deltaTime);

private:
	int m_width;
	int m_height;
	bool isDraw;
	
	std::vector<std::pair<Vector2, Vector2>> m_listLanding;
	std::vector<std::shared_ptr<Sprite2D>> m_listBackground;
};