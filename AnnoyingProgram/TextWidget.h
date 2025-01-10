#pragma once
#include "Widget.h"
#include "FontManager.h"

class TextWidget : public Widget
{
public:
    TextWidget();
    void draw(sf::RenderWindow* window) override;
    void tick(const double delta_time) override {}
    sf::Text text;
};
