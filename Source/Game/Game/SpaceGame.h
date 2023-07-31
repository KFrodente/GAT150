#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

class SpaceGame : public yogi::Game
{
public:
	enum class eState
	{
		TITLE, STARTGAME, STARTLEVEL, GAME, PLAYERDEAD, PLAYERDEADSTART, GAMEOVER, GAMEOVERSTART
	};


public:

	// Inherited via Game
	virtual bool Init() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(yogi::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

	//inline void DoDamage(int amount) { this->m_health -= amount; }

	//int m_gridYSpots[6] = { 75, 125, 175, 225, 275, 325 };
	//int m_gridXSpots[6] = { 50, 100, 150, 200, 250, 300 };


private:
	//std::unique_ptr<Player> m_player;
	int m_neededScore = 500;
	eState m_state = eState::TITLE;
	float m_spawnTimer = 0;
	float m_spawnTime = 30.0f;

	float m_stateTimer = 0;
	float m_deathTextFlickerTimer = 0;
	bool m_showDeathText = true;

	//int m_health = 10;
	//std::list<int> m_gridYSpots = { 75, 125, 175, 225, 275, 325 };
	//std::list<int> m_gridXSpots = { 50, 100, 150, 200, 250, 300 };

	std::shared_ptr<yogi::Font> m_font;
	std::unique_ptr<yogi::Text> m_scoreText;
	std::unique_ptr<yogi::Text> m_neededScoreText;
	std::unique_ptr<yogi::Text> m_healthText;
	std::unique_ptr<yogi::Text> m_titleText;
	std::unique_ptr<yogi::Text> m_gameOverText;
};
extern SpaceGame g_spaceGame;
extern const int g_gridYSpots[6];
extern const int g_gridXSpots[6];
extern float g_moveEnemyTimer;
