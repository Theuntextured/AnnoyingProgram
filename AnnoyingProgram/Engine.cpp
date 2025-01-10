#include "Engine.h"

#include "Button.h"
#include "TextWidget.h"
#include "Tickable.h"
#include "Timeline.h"
#include "WindowManager.h"

Engine::Engine()
{
	initialize();
	frame_time_clock_.restart();
	while(tick())
		__noop();
}

void Engine::initialize()
{
	const auto w = new WindowManager(sf::VideoMode(800, 600), "Annoying Program", sf::Style::Default);

	const auto b = new Button();
	
	b->add_to_window(w);
	b->shape.setFillColor(sf::Color::Green);
	const auto t = new TextWidget();
	t->add_to_parent(b);
}

bool Engine::tick()
{
	const double dt = frame_time_clock_.restart().asSeconds();
	total_time_ += dt;

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
