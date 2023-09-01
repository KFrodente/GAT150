#include "PlatformGame2/PlatformGame2.h"

#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"
#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"


PlatformGame2 g_PlatformGame2;

bool PlatformGame2::Init()
{
	//text
	m_font = GET_RESOURCE(yogi::Font, "BodoniFLF-Bold.ttf", 24);


	//audio
	//yogi::g_audioSystem.AddAudio("hitSound1", "hitSound1.wav");

	//player and scene
	m_scene = std::make_unique<yogi::Scene>();
	m_scene->Load("Scene/scene.json");
	m_scene->Load("Scene/tilemap.json");
	m_scene->Initialize();
	//add events
	yogi::EventManager::Instance().Subscribe("OnAddPoints", this, std::bind(&PlatformGame2::OnAddPoints, this, std::placeholders::_1));
	yogi::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&PlatformGame2::OnPlayerDead, this, std::placeholders::_1));

	m_state = eState::TITLE;
	return true;
}

void PlatformGame2::Shutdown()
{
}

void PlatformGame2::Update(float dt)
{

	switch (m_state)
	{
	case eState::TITLE:
	{
		if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) m_state = eState::STARTGAME;
		m_scene->GetGameObjectByName("Reticle")->active = false;
		m_scene->GetGameObjectByName("HoleInOne")->active = false;
		m_scene->GetGameObjectByName("Birdie")->active = false;
		m_scene->GetGameObjectByName("OnPar")->active = false;
		m_scene->GetGameObjectByName("Bogey")->active = false;
		m_scene->GetGameObjectByName("DoubleBogey")->active = false;
		m_scene->GetGameObjectByName("TripleBogey")->active = false;
		m_scene->GetGameObjectByName("QuadBogey")->active = false;
	}
	break;
	case eState::STARTGAME:
	{
		m_scene->GetGameObjectByName("Title")->active = false;
		auto player = INSTANTIATE(Player, "Player");
		player->m_game = this;
		player->Initialize();
		m_scene->Add(std::move(player));
		auto hole = INSTANTIATE(Enemy, "Hole");
		hole->m_game = this;
		hole->Initialize();
		m_scene->Add(std::move(hole));
		m_state = eState::STARTLEVEL1;

	}
		break;
	case eState::STARTLEVEL1:
	{
		m_scene->GetGameObjectByName("Reticle")->active = true;

		//m_scene->GetGameObjectByName("World1")->active = true;
		m_scene->GetGameObjectByName("Player")->transform.position = {50, 50};
		m_state = eState::LEVEL1;
	}
		break;
	case eState::LEVEL1:
	{
		m_scene->GetGameObjectByName("Reticle")->transform.rotation = yogi::Deg2Rad(m_scene->GetGameObject<yogi::Player>()->aimAngle);
		m_scene->GetGameObjectByName("Reticle")->transform.position = m_scene->GetGameObject<yogi::Player>()->transform.position;
		m_scene->GetGameObjectByName("Reticle")->transform.scale = m_scene->GetGameObject<yogi::Player>()->hitStrength / 7;

		m_scene->GetGameObjectByName("PowerText")->GetComponent<yogi::TextRenderComponent>()->text = "Power: " + std::to_string(m_scene->GetGameObject<yogi::Player>()->hitStrength);

	}
		break;
	case eState::GAMEOVER:
	{
		int hits = m_scene->GetGameObject<yogi::Player>()->hits;
		m_scene->GetGameObjectByName("Reticle")->active = false;
		switch (hits) {
		case 1:
			m_scene->GetGameObjectByName("HoleInOne")->active = true;

			break;
		case 2:
			m_scene->GetGameObjectByName("Birdie")->active = true;
			break;
		case 3:
			m_scene->GetGameObjectByName("OnPar")->active = true;
			break;
		case 4:
			m_scene->GetGameObjectByName("Bogey")->active = true;
			break;
		case 5:
			m_scene->GetGameObjectByName("DoubleBogey")->active = true;
			break;
		case 6:
			m_scene->GetGameObjectByName("TripleBogey")->active = true;
			break;
		case 7:
			m_scene->GetGameObjectByName("QuadBogey")->active = true;
			break;
		default:
			break;
		m_scene->GetGameObjectByName("Player")->active = false;
		}
	}
		break;
	default:
		break;
	}

	if (win) m_state = eState::GAMEOVER;
	m_scene->Update(dt);
}

void PlatformGame2::Draw(yogi::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void PlatformGame2::OnAddPoints(const yogi::Event& event)
{
}


void PlatformGame2::OnPlayerDead(const yogi::Event& event)
{
}