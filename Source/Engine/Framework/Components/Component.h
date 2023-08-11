#pragma once
#include "Framework/Object.h"
namespace yogi
{
	class Component : public Object
	{
	public:
		virtual void Update(float dt) = 0;

		friend class GameObject;

	protected:
		class GameObject* m_owner = nullptr;
	};
}