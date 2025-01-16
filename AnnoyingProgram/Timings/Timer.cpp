#include "Timer.h"

void Timer::tick(const double delta_time)
{
	current_ += delta_time;
	if(current_ < delay_)
		return;

	current_ -= delay_;
	
	callback_();
	if(!loop_)
		mark_for_deletion();
}