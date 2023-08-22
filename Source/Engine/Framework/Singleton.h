#pragma once

namespace yogi
{
	template <typename T>
	class Singleton
	{
	public:
		Singleton(const Singleton& other) = delete;
		Singleton& operator = (const Singleton& other) = delete;

		static T& Instance()
		{
 			static T instance;
			return instance;
		}

	public:
		Singleton() = default;
	};
}