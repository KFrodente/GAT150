#include <iostream>
#include <vector>
#include <cassert>
#include <array>
#include <map>

#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"

#include "SpaceGame.h"

using namespace std;
using vec2 = yogi::Vector2;


void zero(int v)
{
	v = 0;
}

void zero(int* v)
{
	*v = 0;
}

void zero_ref(int& v)
{
	v = 0;
}

int main(int argc, char* argv[])
{
	int i = 5;
	zero(i);
	cout << i << endl;

	zero(&i);
	cout << i << endl;

	i = 3;
	cout << i << endl;
	zero_ref(i);
	cout << i << endl;

	INFO_LOG("Hello World");



	yogi::MemoryTracker::Initialize();
	yogi::seedRandom((unsigned int)time(nullptr));
	yogi::setFilePath("assets");

	yogi::g_renderer.Initialize();
	yogi::g_renderer.CreateWindow("CSC196", 800, 600);

	yogi::g_audioSystem.Initialize();
	yogi::g_inputSystem.Initialize();

	//yogi::res_t<yogi::Texture> texture = yogi::g_resources.Get<yogi::Texture>("Duck.png", yogi::g_renderer);

	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Init();
	


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


		yogi::g_renderer.SetColor(200, 180, 255, 1);
		yogi::g_renderer.BeginFrame();


		//text->Draw(yogi::g_renderer, 0, 0);
		yogi::g_renderer.SetColor(r, g, b, 0);
		yogi::g_renderer.SetColor(255, 200, 200, 0);


		game->Draw(yogi::g_renderer);
		yogi::g_particleSystem.Draw(yogi::g_renderer);

		//yogi::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

		yogi::g_renderer.EndFrame();
	}
	//scene.RemoveAll();
	return 0;
}