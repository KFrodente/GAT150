#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"
#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"


SpaceGame g_spaceGame;
const int g_gridYSpots[6] = { 75, 175, 275, 375, 475, 575 };
const int g_gridXSpots[6] = { 25, 175, 325, 475, 625, 775 };
float g_moveEnemyTimer = 50.0f;

bool SpaceGame::Init()
{
	//text
	//m_font = yogi::g_resources.Get<yogi::Font>("BodoniFLF-Bold.ttf", 24);

	m_scoreText = std::make_unique<yogi::Text>(yogi::g_resources.Get<yogi::Font>("BodoniFLF-Bold.ttf", 24));
	m_scoreText->Create(yogi::g_renderer, "SCORE 0000", yogi::Color{0.5f, 0.8f, .1f, 1});

	m_neededScoreText = std::make_unique<yogi::Text>(yogi::g_resources.Get<yogi::Font>("BodoniFLF-Bold.ttf", 24));
	m_neededScoreText->Create(yogi::g_renderer, "NEXT CHANGE", yogi::Color{1.0f, 0.8f, .1f, 1});
	

	m_titleText = std::make_unique<yogi::Text>(yogi::g_resources.Get<yogi::Font>("BodoniFLF-Bold.ttf", 24));
	m_titleText->Create(yogi::g_renderer, "DODGE GAME [SPACE] TO START", yogi::Color{0.7f, 0.25f, 1, 1});
	
	m_healthText = std::make_unique<yogi::Text>(yogi::g_resources.Get<yogi::Font>("BodoniFLF-Bold.ttf", 24));
	m_healthText->Create(yogi::g_renderer, "HEALTH: ", yogi::Color{0.8f, 1, 0.8f, 1});
	
	m_gameOverText = std::make_unique<yogi::Text>(yogi::g_resources.Get<yogi::Font>("BodoniFLF-Bold.ttf", 24));
	m_gameOverText->Create(yogi::g_renderer, "YOU DIED [R] TO RESTART", yogi::Color{1, 0, 0, 1});

	//audio
	yogi::g_audioSystem.AddAudio("hitSound1", "hitSound1.wav");
	yogi::g_audioSystem.AddAudio("moveUp", "Selection3.wav");
	yogi::g_audioSystem.AddAudio("moveDown", "Selection1.wav");
	yogi::g_audioSystem.AddAudio("playerDied", "PlayerDeath.wav");
	yogi::g_audioSystem.AddAudio("playerHeal", "HealSound.wav");
	yogi::g_audioSystem.AddAudio("enemySpawn", "ESelection1.wav");
	yogi::g_audioSystem.AddAudio("enemyDied", "HurtSound.wav");

	//player and scene
	m_scene = std::make_unique<yogi::Scene>();



	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	
	switch (m_state)
	{
	case eState::TITLE:
	{
		yogi::EmitterData data;
		data.burst = false;
		data.burstCount = 1;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = yogi::Pi;
		data.lifetimeMin = 10.0f;
		data.lifetimeMin = 15.0f;
		data.speedMin = 25;
		data.speedMax = 100;
		data.damping = 0.5f;

		float r = yogi::randomf(0, 1);
		float g = yogi::randomf(0, 1);
		float b = yogi::randomf(0, 1);
		data.color = yogi::Color{ r, g, b, 1 };

		if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_E))
		{
			
			yogi::Transform transform{ { yogi::g_inputSystem.GetMousePosition() }, 0, 1 };
			auto emitter = std::make_unique<yogi::Emitter>(transform, data);
			emitter->m_lifespan = 1.0f;
			m_scene->Add(std::move(emitter));
		}
	}


		if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) m_state = eState::STARTGAME;
		break;
	case eState::STARTGAME:
		//m_health = 10;
		m_score = 0;
		m_neededScore = 500;
		m_state = eState::STARTLEVEL;
		break;
	case eState::STARTLEVEL:
		m_scene->RemoveAll();
	{
			//create player
			std::unique_ptr<Player> player = std::make_unique<Player>(0.5f, yogi::Rad2Deg(.0025f), yogi::Transform{ { g_gridXSpots[0], g_gridYSpots[0]}, yogi::Deg2Rad(0), 2.0f });
		player->m_tag = "Player";
		player->m_game = this;
		//player->SetDamping(0.25f);

		//create components
		auto renderComponent = std::make_unique<yogi::SpriteComponent>();
		renderComponent->m_texture = yogi::g_resources.Get<yogi::Texture>("Duck.png", yogi::g_renderer);
		player->AddComponent(std::move(renderComponent));

		auto physicsComponent = std::make_unique<yogi::EnginePhysicsComponent>();
		player->AddComponent(std::move(physicsComponent));

		m_scene->Add(move(player));

		m_state = eState::GAME;
	}
		break;
	case eState::GAME:
		if (m_score >= m_neededScore)
		{
			yogi::g_audioSystem.PlayOneShot("playerHeal", false);
			g_moveEnemyTimer *= 0.95f;
			m_playerFireRate *= 0.8f;
			heal = true;
			m_neededScore += 5000;
		}
		m_spawnTimer += dt;
		if (m_spawnTimer >= g_moveEnemyTimer)
		{
			m_spawnTimer = 0;
			yogi::g_audioSystem.PlayOneShot("enemySpawn", false);
			int randomYPos = yogi::random(6);
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(yogi::randomf(1.0f, 5.0f), yogi::Pi, yogi::Transform{{g_gridXSpots[5], g_gridYSpots[randomYPos]}, yogi::Deg2Rad(-90), 3});
			enemy->SetYPos(randomYPos);
			enemy->m_tag = "Enemy";
			enemy->m_game = this;

			std::unique_ptr<yogi::SpriteComponent> component = std::make_unique<yogi::SpriteComponent>();
			component->m_texture = yogi::g_resources.Get<yogi::Texture>("Duck.png", yogi::g_renderer);

			enemy->AddComponent(std::move(component));
			m_scene->Add(move(enemy));
		}
		break;
	case eState::PLAYERDEADSTART:
		
			m_state = eState::GAMEOVERSTART;
			m_stateTimer = 10.0f;
		
		//else m_state = eState::PLAYERDEAD;
		//m_stateTimer = 10.0f;
		break;


	case eState::PLAYERDEAD:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::STARTLEVEL;
		}
		break;


	case eState::GAMEOVERSTART:
		m_deathTextFlickerTimer = 10.0f;
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			yogi::g_audioSystem.PlayOneShot("playerDied", false);
			m_state = eState::GAMEOVER;
		}
		break;


	case eState::GAMEOVER:
		m_deathTextFlickerTimer -= dt;
		if (m_deathTextFlickerTimer <= 0)
		{
			m_showDeathText = !m_showDeathText;
			m_deathTextFlickerTimer = 10.0f;
		}
		if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_R))
			m_state = eState::STARTGAME;
		break;
	default:
		break;
	}

	//if (m_health <= 0) m_state = eState::PLAYERDEADSTART;

	m_healthText->Create(yogi::g_renderer, "HEALTH: " + std::to_string(m_health), yogi::Color{0.6f, 1, 0.6f, 1});

	m_neededScoreText->Create(yogi::g_renderer, "NEXT CHANGE: " + std::to_string(m_neededScore), yogi::Color{1.0f, 0.8f, .1f, 1});

	m_scoreText->Create(yogi::g_renderer, "SCORE: " + std::to_string(m_score), yogi::Color{0.85f, 0.6f, 0.35f, 1});
	m_scene->Update(dt);
}

void SpaceGame::Draw(yogi::Renderer& renderer)
{
	if (m_state == eState::TITLE)
	{
		m_titleText->Draw(renderer, 200, 300);
	}
	else if (m_state == eState::GAMEOVER && m_showDeathText)
	{
		m_gameOverText->Draw(renderer, 235, 300);
	}

	m_neededScoreText->Draw(renderer, 250, 20);
	m_scoreText->Draw(renderer, 15, 20);
	m_healthText->Draw(renderer, 600, 20);
	m_scene->Draw(renderer);
}
