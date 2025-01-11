#include "TextWidget.h"

TextWidget::TextWidget()
{
    setString("Hello World!");
    setFont(FontManager::get_fallback_font());
    setCharacterSize(24);
}

void TextWidget::draw_widget(sf::RenderWindow* window)
{
    window->draw(*this, get_transform());
}
