#pragma once
#include "../../Engine/Framework/Game.h"
#include "../../Engine/Framework/Event/EventManager.h"
#include "../../Engine/Renderer/Text.h"

class PlatformGame : public yogi::Game, yogi::IEventListener
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

	void OnAddPoints(const yogi::Event& event);
	void OnPlayerDead(const yogi::Event& event);


private:
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

	//std::shared_ptr<yogi::Font> m_font;
	//std::unique_ptr<yogi::Text> m_scoreText;
	//std::unique_ptr<yogi::Text> m_neededScoreText;
	//std::unique_ptr<yogi::Text> m_healthText;
	//std::unique_ptr<yogi::Text> m_titleText;
	//std::unique_ptr<yogi::Text> m_gameOverText;
};
extern PlatformGame g_spaceGame;
