#pragma once
#include "Framework/GameObject.h"
#include "Framework/Components/PhysicsComponent.h"

namespace yogi
{
	class Weapon : public GameObject
	{
	public:
		CLASS_DECLARATION(Weapon)

		Weapon() = default;
		/*Weapon(float speed, const yogi::Transform& transform) :
			GameObject{ transform },
			speed{ speed }
		{
			lifespan = -1.0f;
			m_timeTillDamage = 3.0f;
			m_damage = 50;
			health = 1;
		}*/
	
		bool Initialize() override;
	
		void Update(float dt) override;
		void OnCollisionEnter(GameObject* other) override;
	
	private:
		float speed = 0;

		PhysicsComponent* m_physicsComponent = nullptr;
	};
}