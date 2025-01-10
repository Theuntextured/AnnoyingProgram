#pragma once

#include "Button.h"
#include "CommonIncludes.h"

class Engine
{
public:
	Engine();
	~Engine() = default;
	
private:
	void initialize();
	bool tick();

	sf::Clock frame_time_clock_;

	double total_time_;
};
