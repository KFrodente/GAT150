#pragma once
#include "Core/Core.h"
#include "Framework/Resource/Resource.h"
#include <vector>

namespace yogi
{
	class Renderer;

	class Model : public Resource
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {}

		bool Load(const std::string& filename);

		virtual bool Create(std::string filename, ...) override;

		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale, bool connect);
		void Draw(Renderer& renderer, const Transform& transform);

		float GetRadius();

	private:
		std::vector<vec2> m_points;
		Color m_color;
		float m_radius = 0;
	};
}