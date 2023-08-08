#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/GameObject.h"

namespace yogi
{
	void yogi::SpriteComponent::Update(float dt)
	{
	}
	
	void yogi::SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform.position.x, m_owner->m_transform.position.y, Rad2Deg(m_owner->m_transform.rotation));
	}
}
