#include "Scene.h"

namespace yogi
{
	void Scene::Update(float deltaTime)
	{
		/*for (auto& gameObject : m_gameObjects)
		{
			gameObject->Update(deltaTime);
		}*/

		auto iter = m_gameObjects.begin();
		while (iter != m_gameObjects.end())
		{
			(*iter)->Update(deltaTime);
			//((*iter)->m_destroyed) ? iter = m_gameObjects.erase(iter) : ++iter;
			if ((*iter)->m_destroyed)
			{
				iter = m_gameObjects.erase(iter);
			}
			else
			{
				iter++;
			}

		}

		// check collisions
		for (auto iter1 = m_gameObjects.begin(); iter1 != m_gameObjects.end(); iter1++)
		{
			for (auto iter2 = std::next(iter1, 1); iter2 != m_gameObjects.end(); iter2++)
			{
				float distance = (*iter1)->m_transform.position.Distance((*iter2)->m_transform.position);
				float radius = (*iter1)->GetRadius() + (*iter2)->GetRadius();

				if (distance <= radius)
				{
					(*iter1)->OnCollision(iter2->get());
					(*iter2)->OnCollision(iter1->get());
				}
			}
		}
	}
	void Scene::Draw(Renderer& renderer)
	{
		for (auto& gameObject : m_gameObjects)
		{
			gameObject->Draw(renderer);
		}
	}
	void Scene::Add(std::unique_ptr<GameObject> gameObject)
	{
		gameObject->m_scene = this;
		m_gameObjects.push_back(std::move(gameObject));
	}

	void Scene::RemoveAll()
	{
		m_gameObjects.clear();
	}
}