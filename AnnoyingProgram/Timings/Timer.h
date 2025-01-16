#pragma once
#include "Tickable.h"

class Timer final : public Tickable
{
public:
	void tick(const double delta_time) override;
	template <typename T, typename F>
	static Timer* create_timer_by_function(T* object, F&& function, const double delay, bool loop = false)
	{
		const auto t = new Timer;
		t->callback_.bind(object, function);
		t->delay_ = delay;
		t->loop_ = loop;
		return t;
	}


private:
	Timer() = default;
	double current_ = 0;
	double delay_ = 0;
	bool loop_ = false;
	Delegate callback_;
};