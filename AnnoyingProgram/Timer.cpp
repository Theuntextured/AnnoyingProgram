#include "Timer.h"

void Timer::tick(const double delta_time)
{
	(object_->*function_)();
	if(!loop_)
		delete this;
}

Timer* Timer::create_timer_by_function(GenericObject* object, void(GenericObject::* function)(), const double delay, bool loop)
{
	const auto t = new Timer;
	t->object_ = object;
	t->function_ = function;
	t->delay_ = delay;
	t->loop_ = loop;
	return t;
}
