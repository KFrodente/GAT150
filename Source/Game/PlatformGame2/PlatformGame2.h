#pragma once
#include "Framework/Game.h"
#include "Framework/Event/EventManager.h"
#include "Renderer/Text.h"

class PlatformGame2 : public yogi::Game, yogi::IEventListener
{
public:
	enum class eState
	{
		TITLE, STARTGAME, STARTLEVEL1, LEVEL1, GAME, PLAYERDEAD, GAMEOVER
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
	eState m_state = eState::TITLE;

private:
	//std::unique_ptr<Player> m_player;
	int m_neededScore = 500;
	float m_spawnTimer = 0;
	float m_spawnTime = 30.0f;

	std::shared_ptr<yogi::Font> m_font;
};
extern PlatformGame2 g_PlatformGame2;
