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

#include "Physics/PhysicsSystem.h"
#include <functional>

using namespace std;
using vec2 = yogi::Vector2;

void print(int i)
{
	cout << i << endl;
}

int Add(int i1, int i2)
{
	return i1 + i2;
}

int Sub(int i1, int i2)
{
	return i1 - i2;
}

class A
{
public:
	int Add(int i1, int i2)
	{
		return i1 + i2;
	}
};

union Data
{
	int i;
	char c[6];
	bool b;
};


int main(int argc, char* argv[])
{
	void (*func_ptr)(int) = &print;
	func_ptr(2);

	int (*op_ptr)(int, int);
	op_ptr = Sub;

	func_ptr(op_ptr(7, 3));

	std::function<int(int, int)> op;
	/*
	std::function<int(int, int)> op = Sub;
	func_ptr(op(10, 21));*/

	A a;
	op = std::bind(&A::Add, &a, std::placeholders::_1, std::placeholders::_2);

	func_ptr(op(7, 3));

	Data data;
	data.b = true;

	INFO_LOG("Hello World");

	yogi::setFilePath("assets");
	yogi::MemoryTracker::Initialize();
	yogi::seedRandom((unsigned int)time(nullptr));
	
	yogi::PhysicsSystem::Instance().Initialize();

	yogi::g_renderer.Initialize();
	yogi::g_renderer.CreateWindow("CSC196", 800, 600);

	yogi::g_audioSystem.Initialize();
	yogi::g_inputSystem.Initialize();


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
		yogi::PhysicsSystem::Instance().Update(yogi::g_time.GetDeltaTime());

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