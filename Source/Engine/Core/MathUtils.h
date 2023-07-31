#pragma once
#include <cmath>

namespace yogi
{
	constexpr float Pi = 3.14159265359f;
	constexpr float TwoPi = 6.28318530718f;
	constexpr float HalfPi = 1.57079632679f;

	constexpr float Rad2Deg(float radians) { return radians * (180.0f / Pi); }
	constexpr float Deg2Rad(float degrees) { return degrees * (Pi / 180.0f); }

	inline float Wrap(float value, float max)
	{
		return std::fmod(value, max) + ((value < 0) ? max : 0);
	}

	template <typename T>
	inline T Max(T a, T b) 
	{
		return (a > b) ? a : b;
	}

	template <typename T>
	inline T Min(T a, T b) 
	{
		return (a > b) ? a : b;
	}

	template <typename T>
	inline T Clamp(T value, T min, T max)
	{
		if (min > max) {
			T placeHold = max;
			max = min;
			min = placeHold;
		}

		return (value < min) ? min : (value > max) ? max : value;
	}
}