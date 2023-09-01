#pragma once
#include "CollisionComponent.h"

namespace yogi
{
	class CircleCollisionComponent : public CollisionComponent
	{
		// Inherited via CollisionComponent
	public:
		CLASS_DECLARATION(CircleCollisionComponent)

		virtual void Update(float dt) override;
		virtual bool CheckCollision(CollisionComponent* collision) override;
	};
}