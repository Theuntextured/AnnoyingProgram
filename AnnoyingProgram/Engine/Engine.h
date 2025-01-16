#pragma once

#include "../Managers/EventManager.h"
#include "../Common/CommonIncludes.h"
#include "../Managers/WindowManager.h"
#include "../WidgetBase/TextWidget.h"
#include "../Managers/AntiTaskManager.h"

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
#ifdef _DEBUG
	WindowManager* stat_window  = nullptr;
	TextWidget* stat_text = nullptr;
#endif
};
