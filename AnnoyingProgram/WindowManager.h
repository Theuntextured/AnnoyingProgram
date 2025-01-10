#pragma once
#include "Widget.h"
#include "Tickable.h"

class WindowManager : public Tickable, sf::RenderWindow
{
public:
	std::vector<Widget*> widgets;
};
