#include "PlatformGame.h"

#include "../../Engine/Framework/Scene.h"
#include "../../Engine/Framework/Framework.h"

#include "../../Engine/Audio/AudioSystem.h"
#include "../../Engine/Input/InputSystem.h"
#include "../../Engine/Renderer/Renderer.h"



PlatformGame g_PlatformGame;

bool PlatformGame::Init()
{
	
}

void PlatformGame::Shutdown()
{
}

void PlatformGame::Update(float dt)
{

	switch (m_state)
	{
	case eState::TITLE:
		break;
	case eState::STARTGAME:
		
		break;
	case eState::STARTLEVEL:
		
		break;
	case eState::GAME:
		
		break;
	case eState::PLAYERDEADSTART:

		break;


	case eState::PLAYERDEAD:
		
		break;


	case eState::GAMEOVERSTART:
		
		break;


	case eState::GAMEOVER:
		
		break;
	default:
		break;
	}

}

void PlatformGame::Draw(yogi::Renderer& renderer)
{
	
}
