#include "ModelRenderComponent.h"
#include "Framework/GameObject.h"

void yogi::ModelRenderComponent::Update(float dt)
{
}

void yogi::ModelRenderComponent::Draw(Renderer& renderer)
{
	m_model->Draw(renderer, m_owner->m_transform);
}
