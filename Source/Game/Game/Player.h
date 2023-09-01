#pragma once
#include "Framework/GameObject.h"
#include "Framework/Components/PhysicsComponent.h"

class Player : public yogi::GameObject 
{
public:

	virtual const char* GetClassName() {
		return "Player";
	}virtual void Read(const rapidjson::Value& value);virtual std::unique_ptr<Object> Clone() {
		return std::make_unique<Player>(*this);
	} class Register {
	public: Register() {
		yogi::Factory::Instance().Register<Player>("Player");
	}
	};

	Player() = default;
	Player(float speed, float turnRate, const yogi::Transform& transform) :
		GameObject{ transform },
		speed{ speed },
		m_turnRate{ turnRate }
	{
		health = m_maxHealth;
		m_damage = 0;
	}

	int GetHealth() { return health; }

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollisionEnter(GameObject* other) override;

private:

	float m_fireRate = 0.0f;
	float m_fireTimer = 0.0f;
	int m_maxHealth = 100;
	int m_yPos = 0;
	int m_xPos = 0;
	float speed = 0;
	float m_turnRate = 0;

	yogi::PhysicsComponent* m_physicsComponent = nullptr;
};
