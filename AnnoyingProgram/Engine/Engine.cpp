#include "Engine.h"

#include "../Managers/AntiTaskbar.h"
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
	delete anti_task_manager_;
}

void Engine::initialize()
{
	srand(static_cast<int>(time(nullptr)));
	event_manager_ = new EventManager();
	frame_time_clock_.restart();
	anti_task_manager_ = new AntiTaskManager;

#ifdef _DEBUG
	stat_window = new WindowManager({200, 150}, "Stats", sf::Style::Titlebar);
	stat_text = new TextWidget();

	stat_text->local_transform.translate(static_cast<sf::Vector2f>(stat_window->getSize()) / 2.f);
	centre_drawable(stat_text);
	stat_text->add_to_parent(stat_window);
#endif
}

bool Engine::tick()
{
	double dt = frame_time_clock_.restart().asSeconds();
	dt = std::min(dt, 0.1);
	total_time_ += dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		return false;
	
#ifdef _DEBUG
	stat_text->setString("Total time: " + std::to_string(static_cast<int>(total_time_)) +
		"\nFPS: " + std::to_string(static_cast<int>(1 / dt))
	);
	centre_drawable(stat_text);
#endif
	
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
