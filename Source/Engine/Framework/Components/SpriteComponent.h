#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"

namespace yogi
{
	class SpriteComponent : public RenderComponent
	{
	public:


		// Inherited via RenderComponent
		void Update(float dt) override;

		void Draw(class Renderer& renderer) override;

	public:
		res_t<Texture> m_texture;
	};
}