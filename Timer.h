#pragma once

import <chrono>; // #include can take a literal second...

class Timer
{
public:
	Timer()
	{
		reset();
	}

	inline void reset()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}

	inline float nanoseconds()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count();		
	}

	inline float microseconds()
	{
		return nanoseconds() * 0.001f;
	}

	inline float milliseconds()
	{
		return nanoseconds() * 0.001f * 0.001f;
	}

	inline float seconds()
	{
		return nanoseconds() * 0.001f * 0.001f * 0.001f;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
};