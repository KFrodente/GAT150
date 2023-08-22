#pragma once
#include "Framework/Singleton.h"
#include "box2d/include/box2d/b2_world.h"
#include <memory>

namespace yogi
{
	class PhysicsSystem : public Singleton<PhysicsSystem>
	{
	public:
		bool Initialize();
		void Update(float dt);

		friend class Singleton;
		//<make singleton a friend class to access private constructor>
	private:
		PhysicsSystem() = default;
		//<declare default constructor>
	private:
		std::unique_ptr<b2World> m_world;
	};
}