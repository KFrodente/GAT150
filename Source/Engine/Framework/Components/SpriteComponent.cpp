#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/GameObject.h"
#include "Framework/Resource/ResourceManager.h"

namespace yogi
{
	CLASS_DEFINITION(SpriteComponent)

	bool SpriteComponent::Initialize()
	{
		if (!textureName.empty()) m_texture = GET_RESOURCE(Texture, textureName, yogi::g_renderer);

		return true;
	}

	void SpriteComponent::Update(float dt)
	{
	}


	void SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->transform);
	}

	void SpriteComponent::Read(const json_t& value)
	{
		READ_DATA(value, textureName);
	}
}
