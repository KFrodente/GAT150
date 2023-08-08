#pragma once
#include "Component.h"

namespace yogi
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}