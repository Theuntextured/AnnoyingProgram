#pragma once
#include "Tickable.h"

class Timer final : public Tickable
{
public:
	void tick(const double delta_time) override;
	static Timer* create_timer_by_function(GenericObject* object, void(GenericObject::* function)(), const double delay, bool loop = false);

private:
	Timer() = default;
	double delay_ = 0;
	bool loop_ = false;
	void(GenericObject::*function_)() = nullptr;
	GenericObject* object_ = nullptr;
};