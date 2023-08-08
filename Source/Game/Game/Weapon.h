#pragma once
#include "Framework/GameObject.h"

class Weapon : public yogi::GameObject
{
public:

	Weapon(float speed, const yogi::Transform& transform) :
		GameObject{ transform },
		m_speed{ speed }
	{
		m_lifespan = -1.0f;
		m_timeTillDamage = 3.0f;
		m_damage = 50;
		m_health = 1;
	}

	void Update(float dt) override;
	void OnCollision(GameObject* other) override;

private:
	float m_speed = 0;
};