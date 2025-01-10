#pragma once

#include "CommonIncludes.h"

class Engine
{
public:
	Engine();
	bool tick();

private:
	sf::Clock frame_time_clock_;
};
