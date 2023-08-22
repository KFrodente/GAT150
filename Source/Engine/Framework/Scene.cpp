#include "Scene.h"
#include "Framework/Components/CollisionComponent.h"

namespace yogi
{
	bool Scene::Initialize()
	{
		for (auto& gameObject : m_gameObjects) gameObject->Initialize();

		return true;
	}

	void Scene::Update(float deltaTime)
	{
		auto iter = m_gameObjects.begin();
		while (iter != m_gameObjects.end())
		{
			if ((*iter)->active) (*iter)->Update(deltaTime);
			//((*iter)->m_destroyed) ? iter = m_gameObjects.erase(iter) : ++iter;
			if ((*iter)->destroyed)
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
				CollisionComponent* collision1 = (*iter1)->GetComponent<CollisionComponent>();
				CollisionComponent* collision2 = (*iter2)->GetComponent<CollisionComponent>();

				if (collision1 == nullptr || collision2 == nullptr) continue;

				if (collision1->CheckCollision(collision2))
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
			if (gameObject->active) gameObject->Draw(renderer);
		}
	}
	void Scene::Add(std::unique_ptr<GameObject> gameObject)
	{
		gameObject->m_scene = this;
		m_gameObjects.push_back(std::move(gameObject));
	}

	void Scene::RemoveAll(bool force)
	{
		auto iter = m_gameObjects.begin();
		while (iter != m_gameObjects.end())
		{
			//((*iter)->m_destroyed) ? iter = m_gameObjects.erase(iter) : ++iter;
			if (!(*iter)->persistent || force)
			{
				iter = m_gameObjects.erase(iter);
			}
			else
			{
				iter++;
			}

		}
	}

	bool Scene::Load(const std::string& filename)
	{
		rapidjson::Document document;
		if (!Json::Load(filename, document))
		{
			ERROR_LOG("could not load scene file: " << filename);
			return false;
		}

		Read(document);

		return true;
	}

	void Scene::Read(const json_t& value)
	{
		if (HAS_DATA(value, gameobjects) && GET_DATA(value, gameobjects).IsArray()) {
			for (auto& gameobjectValue : GET_DATA(value, gameobjects).GetArray()) {
				std::string type;
				READ_DATA(gameobjectValue, type);

				auto gameObject = CREATE_CLASS_BASE(GameObject, type);
				gameObject->Read(gameobjectValue);

				if (gameObject->prototype)
				{
					std::string name = gameObject->name;
					Factory::Instance().RegisterPrototype(name, std::move(gameObject));
				}
				else
				{
					Add(std::move(gameObject));
				}

			}
		}
	}
}