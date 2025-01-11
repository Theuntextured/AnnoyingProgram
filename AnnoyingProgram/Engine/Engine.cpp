#include "Engine.h"
#include "../Timings/Tickable.h"

Engine::Engine()
{
	initialize();
	while(tick())
		__noop();
}

Engine::~Engine()
{
	delete event_manager_;
}

void Engine::initialize()
{
	event_manager_ = new EventManager();
	frame_time_clock_.restart();
}

bool Engine::tick()
{
	double dt = frame_time_clock_.restart().asSeconds();
	dt = std::min(dt, 0.1);
	total_time_ += dt;

	event_manager_->total_time = total_time_;
	event_manager_->tick(dt);

	std::vector<Tickable*> to_delete;

	for(auto& i : Tickable::tickables)
	{
		if(i.first->is_marked_for_deletion)
		{
			to_delete.push_back(i.first);
			continue;
		}
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
	
	for(const auto i : to_delete)
		delete i;
	
	return !event_manager_->should_stop;
}
