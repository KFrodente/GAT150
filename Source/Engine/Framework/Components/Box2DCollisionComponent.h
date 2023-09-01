#pragma once
#include "CollisionComponent.h"
#include "Physics/PhysicsSystem.h"
#include <functional>

namespace yogi
{
	class Box2DCollisionComponent : public CollisionComponent
	{
	public:
		using collisionFunction = std::function<void(GameObject*)>;

	public:
		CLASS_DECLARATION(Box2DCollisionComponent)

		virtual bool Initialize() override;
		virtual void Update(float dt) override;

	private:
		PhysicsSystem::CollisionData data;
		vec2 scaleOffset = vec2{ 1, 1 };
	};
}