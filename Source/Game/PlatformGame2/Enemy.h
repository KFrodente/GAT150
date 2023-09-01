#pragma once
#include "Framework/GameObject.h"
#include "Framework/Components/PhysicsComponent.h"

namespace yogi
{

	class Enemy : public GameObject
	{
	public:
		CLASS_DECLARATION(Enemy)

			Enemy() = default;
		Enemy(float speed, float jump, const yogi::Transform& transform) :
			GameObject{ transform },
			speed{ speed },
			jump{ jump }
		{
			m_damage = 0;
		}

		int GetHealth() { return health; }

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(GameObject* other) override;
		void OnCollisionExit(GameObject* other) override;

	private:
		float speed = 0.0f;
		float jump = 0.0f;
		int groundCount = 0;

		yogi::PhysicsComponent* m_physicsComponent = nullptr;
	};
};
