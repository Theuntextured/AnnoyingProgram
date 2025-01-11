#pragma once

#include "../Managers/EventManager.h"
#include "../Common/CommonIncludes.h"

class Engine
{
public:
	Engine();
	~Engine();
	
private:
	void initialize();
	bool tick();

	EventManager* event_manager_;
	sf::Clock frame_time_clock_;
	double total_time_;
};
