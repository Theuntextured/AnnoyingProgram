#pragma once
#include "Widget.h"
#include "../Managers/FontManager.h"

class TextWidget : public Widget, public sf::Text
{
public:
    TextWidget();
    void draw_widget(sf::RenderWindow* window) override;
};
