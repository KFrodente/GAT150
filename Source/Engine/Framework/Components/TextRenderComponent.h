#pragma once
#include "RenderComponent.h"

namespace yogi
{
	class Text;

	class TextRenderComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(TextRenderComponent)

		TextRenderComponent() = default;
		TextRenderComponent(const TextRenderComponent& other);
		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
		void SetText(const std::string& string);
	public:
		std::string text;
		std::string fontName;
		int fontSize = 0;
		Color color{ 1, 1, 1, 1 };

	private:
		bool m_changed = true;
		std::unique_ptr<yogi::Text> m_text;
	};
}