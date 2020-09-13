#pragma once
#include "gamestatebase.h"
#include "AnimationSprite.h"
#include "DifferentlyAnimationSprite.h"
#include "ScrollAnimationSprite.h"
#include "Character.h"
#include "StageMap.h"
#include "HitBox.h"
#include "GameButton.h"


class Sprite2D;
class Sprite3D;
class Text;
class AnimationSprite;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	void Control(std::shared_ptr<Character> ch, int key, float deltaTime, bool isEnemy = false);
	//void CreateAttack(std::shared_ptr<Character> character, bool isEnery, std::string type);
	void SetNewPostionForBullet();
	void DetectCollision();
	

private:
	void GenStage();
	void DetectCollision(std::shared_ptr<Character> character, std::vector < std::shared_ptr<HitBox>>& attacks);
	void CleanUp();
	void CleanUp(std::vector < std::shared_ptr<HitBox>> &attacks);

	void Control(std::shared_ptr<Character> character, std::string command, float deltaTime, bool isEnemy);
	void ControlUnit(float deltaTime);
	bool IsCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

	//std::vector <std::shared_ptr<Sprite2D>> m_listBackGround;
	int m_key;
	std::shared_ptr<StageMap> m_map;
	std::shared_ptr<Text>  m_score;
	float m_jumpDuration;
	std::shared_ptr<Character> m_mainCharacter;
	//::vector<std::shared_ptr<DifferentlyAnimationSprite>> m_listAnimation;
	std::vector<std::shared_ptr<Character>> m_listEnemyCharacter;
	std::vector < std::shared_ptr<HitBox>> m_listMCAttack;
	std::vector < std::shared_ptr<HitBox>> m_listEnemyAttack;
	int m_lv;
	int m_numEnemies;
	std::vector<float> m_controlUnitDuration;
	std::vector<std::string> m_controlUnitCommand;

	//std::unordered_map<std::string, std::shared_ptr<AttackAnimation>> m_mapAttackAnimation;
	std::shared_ptr<HitBox> Attack(std::shared_ptr<Character> character, int w, int h, int duration, float posibility = 0.0f, std::string ability = "");

	//test
	//std::shared_ptr<HitBox> m_test;
	std::unordered_map<std::string, std::shared_ptr<AnimationSprite>> m_mapAttackAnimation;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
};

