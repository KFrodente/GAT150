#include "GameObject.h"
#include "Components/RenderComponent.h"

namespace yogi
{
	void GameObject::Update(float dt)
	{
		if (m_lifespan != -1.0f) 
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		for (auto& component : m_components)
		{
			component->Update(dt);
		}

		if (m_health <= 0)
			m_destroyed = true;

		//m_transform.position += m_velocity * dt;
		//m_velocity *= std::pow(1 - m_damping, dt);
	}

	void GameObject::Draw(yogi::Renderer& renderer)
	{
		//m_model->Draw(renderer, m_transform);
		for (auto& component : m_components)
		{
			RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component.get());
			if (renderComponent)
			{
				renderComponent->Draw(renderer);
			}
		}
	}
	void GameObject::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}
}
