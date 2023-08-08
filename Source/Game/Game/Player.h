#pragma once
#include "Framework/GameObject.h"

class Player : public yogi::GameObject 
{
public:

	Player(float speed, float turnRate, const yogi::Transform& transform) :
		GameObject{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_health = m_maxHealth;
		m_damage = 0;
	}

	int GetHealth() { return m_health; }

	void Update(float dt) override;
	void OnCollision(GameObject* other) override;

private:

	float m_fireRate = 0.0f;
	float m_fireTimer = 0.0f;
	int m_maxHealth = 100;
	int m_yPos = 0;
	int m_xPos = 0;
	float m_speed = 0;
	float m_turnRate = 0;
};