#include "Weapon.h"
#include "SpaceGame.h"
void Weapon::Update(float dt)
{
	GameObject::Update(dt);
	m_timeTillDamage -= dt;
	yogi::vec2 forward = yogi::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * yogi::g_time.GetDeltaTime();

	if (m_transform.position.x > 900 || m_transform.position.x < 0 ||m_transform.position.y < 0 || m_transform.position.y > 800)
	{
		m_health = 0;
	}
	//m_transform.position.x = yogi::Wrap(m_transform.position.x, yogi::g_renderer.GetWidth());
	//m_transform.position.y = yogi::Wrap(m_transform.position.y, yogi::g_renderer.GetHeight());
}

void Weapon::OnCollision(GameObject* other)
{
	if (this->m_tag != "SpecialBullet")
	{
		if ((other->m_tag == "Enemy" && this->m_tag == "PlayerBullet") || (other->m_tag == "Player" && this->m_tag == "EnemyBullet") && this->m_timeTillDamage < 0)
			this->m_health = 0;
		if ((other->m_tag == "EnemyBullet" || other->m_tag == "PlayerBullet"))
		{
			m_game->AddPoints(50);
			this->m_health = 0;
		}
	}
	else if (this->m_tag == "SpecialBullet" && other->m_tag == "Player")
	{
		this->m_health = 0;
	}
}
