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
		CLASS_DECLARATION(GameObject)
		GameObject() = default;
		GameObject(const yogi::Transform& transform) :
			transform{ transform }
		{}
		GameObject(const yogi::Transform& transform, std::shared_ptr<Model> model) :
			transform{ transform }
		{}

		virtual ~GameObject() {
			OnDestroy();
		}

		GameObject(const GameObject& other);

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(yogi::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();


		virtual void OnCollisionEnter(GameObject* other) {}
		virtual void OnCollisionExit(GameObject* other) {}

		

		class Scene* m_scene = nullptr;
		friend class Scene;

		yogi::Transform transform;
		std::string tag;

		class Game* m_game = nullptr;

		float m_timeTillDamage;
		int m_damage;
		float lifespan = -1.0f;

		bool persistent = false;
		bool prototype = false;
		bool destroyed = false;

	protected:
		std::vector<std::unique_ptr<Component>> components;

		int health = 1;

		
	};


	template<typename T>
	inline T* GameObject::GetComponent()
	{
		for (auto& component : components)
		{
			T* result = dynamic_cast<T*>(component.get());

			if (result) return result;
		}


		return nullptr;
	}
}