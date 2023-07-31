#include <iostream>
#include <vector>

#include "Renderer/Text.h"
#include "Core/Core.h"
#include "Renderer/ModelManager.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Emitter.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"

#include "SpaceGame.h"

using namespace std;
using vec2 = yogi::Vector2;

class Star
{
public:
	Star(const vec2& pos, const vec2& vel):
		m_pos{ pos },
		m_vel{ vel }{}

	void Update()
	{
		m_pos += m_vel * yogi::g_time.GetDeltaTime();
		
	}
public:
	vec2 m_pos;
	vec2 m_vel;
};


int main(int argc, char* argv[])
{
	
	yogi::MemoryTracker::Initialize();
	yogi::seedRandom((unsigned int)time(nullptr));
	yogi::setFilePath("assets");

	yogi::g_renderer.Initialize();
	yogi::g_renderer.CreateWindow("CSC196", 800, 600);

	yogi::g_audioSystem.Initialize();
	yogi::g_inputSystem.Initialize();

	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Init();
	//input


	//renderer

	//text

	yogi::Model model;
	model.Load("ship.txt");

	yogi::Model enemyModel;
	enemyModel.Load("enemy.txt");

	//makes scene and player
	


	int r = 255;
	int g = 255;
	int b = 85;

	int score = 0;

	//main game loop
	bool quit = false;
	while (!quit) 
	{
		//update engine
		yogi::g_time.Tick();
		yogi::g_inputSystem.Update();

		yogi::g_audioSystem.Update();
		yogi::g_particleSystem.Update(yogi::g_time.GetDeltaTime());

		if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		if (yogi::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !yogi::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
		}

		//update game
		game->Update(yogi::g_time.GetDeltaTime());
		score++;
		//draw game


		yogi::g_renderer.SetColor(0, 0, 0, 0);
		yogi::g_renderer.BeginFrame();


		//text->Draw(yogi::g_renderer, 0, 0);
		yogi::g_renderer.SetColor(r, g, b, 0);
		yogi::g_renderer.SetColor(255, 200, 200, 0);


		game->Draw(yogi::g_renderer);
		yogi::g_particleSystem.Draw(yogi::g_renderer);

		yogi::g_renderer.EndFrame();
	}
	//scene.RemoveAll();
	return 0;
}