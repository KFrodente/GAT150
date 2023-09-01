#pragma once
#include <memory>
namespace yogi
{
	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual bool Init() = 0;
		virtual void Shutdown() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(class Renderer& renderer) = 0;

		int GetScore() const { return m_score; }
		void AddPoints(int points) { m_score += points; }

		int GetLives() const { return m_health; }
		void SetHealth(int lives) { m_health = lives; }
		void AddHealth(int lives) { m_health += lives; }

		float GetFireRate() { return m_playerFireRate; }

		bool heal = false;
		bool win = false;

	protected:
		std::unique_ptr<class Scene> m_scene;

		float m_playerFireRate = 20.0f;

		int m_score = 0;
		int m_health = 0;
	};
}