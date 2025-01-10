#include "Engine.h"
#include "Tickable.h"

Engine::Engine()
{
	frame_time_clock_.restart();
	while(tick())
		__noop();
}

bool Engine::tick()
{
	const double dt = frame_time_clock_.restart().asSeconds();

	for(auto& i : Tickable::tickables)
	{
		if(i.first->get_tick_interval() < .0)
			continue;
		
		if(i.first->get_tick_interval() == .0)
			i.first->tick(dt);
		else if ((i.second -= dt) <= 0.0)
		{
			i.second += i.first->get_tick_interval();
			i.first->tick(i.first->get_tick_interval());
		}
	}
	return true;
}
