#pragma once
#include "Core/Core.h"
#include <memory>
#include "Renderer/Model.h"

namespace yogi
{
	class GameObject
	{
	public:

		GameObject() = default;
		GameObject(const yogi::Transform& transform) :
			m_transform{ transform }
		{}
		GameObject(const yogi::Transform& transform, std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model }
		{}

		virtual void Update(float dt);
		virtual void Draw(yogi::Renderer& renderer);

		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }
		virtual void OnCollision(GameObject* other) {}

		void AddForce(const vec2 force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }

		class Scene* m_scene = nullptr;
		friend class Scene;

		yogi::Transform m_transform;
		std::string m_tag;

		class Game* m_game = nullptr;

		float m_timeTillDamage;
		int m_damage;
		float m_lifespan = -1.0f;

	protected:
		bool m_destroyed = false;
		int m_health = 1;

		std::shared_ptr<Model> m_model;

		vec2 m_velocity;
		float m_damping = 0;
	};
}