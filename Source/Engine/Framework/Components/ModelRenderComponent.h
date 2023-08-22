#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Renderer/Model.h"

namespace yogi
{
	class ModelRenderComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(ModelRenderComponent)

		bool Initialize();
		void Update(float dt) override;

		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_model->GetRadius(); }


	public:
		std::string modelName;
		res_t<Model> m_model;
	};
}