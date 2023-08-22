#include "Weapon.h"
#include "SpaceGame.h"
#include "Framework/Framework.h"

namespace yogi
{
	CLASS_DEFINITION(Weapon)
	bool Weapon::Initialize()
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
	void Weapon::Update(float dt)
	{
		GameObject::Update(dt);
		m_timeTillDamage -= dt;
		yogi::vec2 forward = yogi::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * speed * yogi::g_time.GetDeltaTime();
	
		if (transform.position.x > 900 || transform.position.x < 0 ||transform.position.y < 0 || transform.position.y > 800)
		{
			health = 0;
		}
		//m_transform.position.x = yogi::Wrap(m_transform.position.x, yogi::g_renderer.GetWidth());
		//m_transform.position.y = yogi::Wrap(m_transform.position.y, yogi::g_renderer.GetHeight());
	}
	
	void Weapon::OnCollision(GameObject* other)
	{
		if (this->tag != "SpecialBullet")
		{
			if ((other->tag == "Enemy" && this->tag == "PlayerBullet") || (other->tag == "Player" && this->tag == "EnemyBullet") && this->m_timeTillDamage < 0)
				this->health = 0;
			if ((other->tag == "EnemyBullet" || other->tag == "PlayerBullet"))
			{
				m_game->AddPoints(50);
				this->health = 0;
			}
		}
		else if (this->tag == "SpecialBullet" && other->tag == "Player")
		{
			this->health = 0;
		}
	}

	void Weapon::Read(const json_t& value)
	{
		GameObject::Read(value);

		READ_DATA(value, speed);

	}
}
