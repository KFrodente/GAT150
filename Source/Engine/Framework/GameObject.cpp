#include "GameObject.h"

namespace yogi
{
	void GameObject::Update(float dt)
	{
		if (m_lifespan != -1.0f) 
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		if (m_health <= 0)
			m_destroyed = true;

		//m_transform.position += m_velocity * dt;
		//m_velocity *= std::pow(1 - m_damping, dt);
	}

	void GameObject::Draw(yogi::Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}
}
