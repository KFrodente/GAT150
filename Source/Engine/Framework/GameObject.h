#pragma once
#include "Core/Core.h"
#include "Components/Component.h"
#include <memory>
#include "Renderer/Model.h"
#include "Object.h"

namespace yogi
{
	class GameObject : public Object
	{
	public:

		GameObject() = default;
		GameObject(const yogi::Transform& transform) :
			m_transform{ transform }
		{}
		GameObject(const yogi::Transform& transform, std::shared_ptr<Model> model) :
			m_transform{ transform }
		{}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(yogi::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		float GetRadius() { return 20.0f; }
		virtual void OnCollision(GameObject* other) {}

		

		class Scene* m_scene = nullptr;
		friend class Scene;

		yogi::Transform m_transform;
		std::string m_tag;

		class Game* m_game = nullptr;

		float m_timeTillDamage;
		int m_damage;
		float m_lifespan = -1.0f;

	protected:
		std::vector<std::unique_ptr<Component>> m_components;

		bool m_destroyed = false;
		int m_health = 1;

		
	};


	template<typename T>
	inline T* GameObject::GetComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*>(component.get());

			if (result) return result;
		}


		return nullptr;
	}
}