#pragma once
#include <cstdint>
#include <functional>

/// <summary>
/// 時限発動
/// </summary>
class TimedCall {
public:
	TimedCall(std::function<void()> callbackFunc, uint32_t time);
	void Update();
	inline bool IsFinished() const { return m_isFinished; }

private:
	std::function<void()> m_callbackFunc;
	uint32_t m_time;
	bool m_isFinished = false;
};
