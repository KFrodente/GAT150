#pragma once
#include "Framework/GameObject.h"

class Enemy : public yogi::GameObject
{
public:

	Enemy(float speed, float turnRate, const yogi::Transform& transform) :
		GameObject{ transform},
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireRate = 100.0f;
		m_fireTimer = m_fireRate;
		m_damage = 25;
	}

	bool Initialize() override;

	void SetYPos(int yPos) {
		m_yPos = yPos;
	}

	void SetMoveTimer(float time) {
		m_moveTimer = time;
	}

	void Update(float dt) override;
	void OnCollision(GameObject* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;

	float m_moveTimer = 100.0f;

	int m_xPos = 5;
	int m_yPos = 0;

};