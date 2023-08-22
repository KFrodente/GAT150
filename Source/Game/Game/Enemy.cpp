#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Framework/Emitter.h"
#include "Audio/AudioSystem.h"

#include "Framework/Components/SpriteComponent.h"
#include "Framework/Framework.h"
bool Enemy::Initialize()
{
	GameObject::Initialize();
	auto collisionComponent = GetComponent<yogi::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<yogi::RenderComponent>();
		if (renderComponent)
		{
			float scale = transform.scale;
			collisionComponent->m_radius = renderComponent->GetRadius() * scale;
		}
	}
	return true;

}
void Enemy::Update(float dt)
{
	GameObject::Update(dt);

	m_moveTimer -= dt;

	if (m_moveTimer <= 0)
	{
		m_moveTimer = g_moveEnemyTimer;
		m_xPos--;
		this->transform.position.x = (float)g_gridXSpots[m_xPos];
	}
	//yogi::vec2 forward = yogi::vec2{ 0, -1 }.Rotate(m_transform.rotation);

	if (m_xPos == 0)
	{
		//g_spaceGame.DoDamage(m_damage);
		/*yogi::Transform transform1{ {m_transform.position.x, m_transform.position.y + 5}, yogi::Deg2Rad(0), .5f};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(10.0f, transform1);
		weapon->m_tag = "SpecialBullet";
		weapon->m_damage = 100;*/

		std::unique_ptr<yogi::SpriteComponent> component = std::make_unique<yogi::SpriteComponent>();
		component->m_texture = GET_RESOURCE(yogi::Texture, "EnemyBullet.png", yogi::g_renderer);

		/*weapon->AddComponent(std::move(component));
		auto collisionComponent = std::make_unique<yogi::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		weapon->AddComponent(std::move(collisionComponent));

		weapon->Initialize();
		m_scene->Add(std::move(weapon));
		yogi::Transform transform2{ {m_transform.position.x, m_transform.position.y + 5}, yogi::Deg2Rad(180), .5f};
		std::unique_ptr<Weapon> weapon2 = std::make_unique<Weapon>(10.0f, transform2);
		weapon2->m_tag = "SpecialBullet";
		weapon2->m_damage = 100;
		std::unique_ptr<yogi::SpriteComponent> component2 = std::make_unique<yogi::SpriteComponent>();
		component2->m_texture = GET_RESOURCE(yogi::Texture, "EnemyBullet.png", yogi::g_renderer);

		weapon2->AddComponent(std::move(component2));

		auto collisionComponent2 = std::make_unique<yogi::CircleCollisionComponent>();
		collisionComponent2->m_radius = 30.0f;
		weapon2->AddComponent(std::move(collisionComponent2));

		weapon2->Initialize();*/
		//m_scene->Add(std::move(weapon2));
		health = 0;
	}
	//m_transform.position += forward * m_speed * yogi::g_time.GetDeltaTime();
	//m_transform.position.x = yogi::Wrap(m_transform.position.x, yogi::g_renderer.GetWidth());
	//m_transform.position.y = yogi::Wrap(m_transform.position.y, yogi::g_renderer.GetHeight());

	m_fireTimer -= dt;

	/*if (m_fireTimer <= 0 && m_health > 0) {
		m_fireTimer = m_fireRate;
		yogi::Transform transform1{ m_transform.position, m_transform.rotation, .5f};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(10.0f, transform1);
		weapon->m_tag = "EnemyBullet";
		weapon->m_game = this->m_game;
		weapon->m_damage = 10;
		std::unique_ptr<yogi::SpriteComponent> component = std::make_unique<yogi::SpriteComponent>();
		component->m_texture = GET_RESOURCE(yogi::Texture, "EnemyBullet.png", yogi::g_renderer);

		weapon->AddComponent(std::move(component));
		auto collisionComponent = std::make_unique<yogi::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		weapon->AddComponent(std::move(collisionComponent));
		weapon->Initialize();
		m_scene->Add(std::move(weapon));
	}*/
}

void Enemy::OnCollision(GameObject* other)
{
	if (other->tag == "PlayerBullet" /*&& other->m_timeTillDamage < 0*/)
	{
		this->health -= other->m_damage;
		m_game->AddPoints(100 * (int)m_speed);
		yogi::g_audioSystem.PlayOneShot("enemyDied", false);
		//do particles
		yogi::EmitterData data;
		data.burst = false;
		data.burstCount = 10;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = yogi::Pi;
		data.lifetimeMin = 10.0f;
		data.lifetimeMin = 15.0f;
		data.speedMin = 10;
		data.speedMax = 20;
		data.damping = 0.5f;

		float r = yogi::randomf(0, 1);
		float g = yogi::randomf(0, 1);
		float b = yogi::randomf(0, 1);
		data.color = yogi::Color{ r, g, b, 1 };

		yogi::Transform transform{ this->transform};
		auto emitter = std::make_unique<yogi::Emitter>(transform, data);
		emitter->lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
}
