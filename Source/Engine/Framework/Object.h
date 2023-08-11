#pragma once
#include <string>
namespace yogi
{
	class Object
	{
	public:
		Object() = default;
		Object(std::string name) { m_name = name; };
		virtual ~Object() { OnDestroy(); }

		virtual bool Initialize() {}
		virtual void OnDestroy() {}

	protected:
		std::string m_name;
	};
}