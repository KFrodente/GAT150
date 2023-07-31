#pragma once
#include <list>
#include "GameObject.h"

namespace yogi
{
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;

		void Update(float deltaTime);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<GameObject> gameObject);
		void RemoveAll();

		template<typename T>
		T* GetGameObject();

		friend class GameObject;
	private:
		std::list<std::unique_ptr<GameObject>> m_gameObjects;
		

	};

	template<typename T>
	inline T* Scene::GetGameObject()
	{
		for (auto& gameObject : m_gameObjects)
		{
			T* result = dynamic_cast<T*>(gameObject.get());

			if (result) return result;
		}


		return nullptr;
	}
}