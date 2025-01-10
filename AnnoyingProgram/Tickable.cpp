#include "Tickable.h"

std::map<Tickable*, double> Tickable::tickables = std::map<Tickable*, double>();

Tickable::Tickable()
{
	tickables[this] = tick_interval_;
}

Tickable::~Tickable()
{
	tickables.erase(this);
}

void Tickable::set_tick_interval(const double interval)
{
	auto& t = tickables[this];
	t = std::min(t, interval);
	tick_interval_ = interval;
}
