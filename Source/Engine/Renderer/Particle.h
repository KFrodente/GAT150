#pragma once
#include "Core/Math/Color.h"
#include "Core/Math/Vector2.h"

namespace yogi
{
	struct ParticleData
	{
		Vector2 position;
		Vector2 prevPosition;
		Vector2 velocity;
		float damping = 0;

		Color color;

		float lifeTimer = 0;
		float lifeTime = 0;
	};

	class Particle
	{
	public:
		Particle() = default;

		void Initialize(ParticleData& data)
		{
			m_data = data;
			m_isActive = true;
		}
		void Update(float dt);
		void Draw(class Renderer& renderer);

			friend class ParticleSystem;
	private:
		ParticleData m_data;
		bool m_isActive = false;

	};

}