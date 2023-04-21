#include "TimedCall.h"

TimedCall::TimedCall(std::function<void()> callbackFunc, uint32_t time)
    : m_callbackFunc(callbackFunc), m_time(time) {}

void TimedCall::Update() { 
    if (m_isFinished) {
		return;
    }
    --m_time;
	if (m_time <= 0) {
		m_isFinished = true;
		m_callbackFunc();
    }
}
