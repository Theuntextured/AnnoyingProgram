#include "TextWidget.h"

TextWidget::TextWidget()
{
    text = sf::Text("Hello World!", FontManager::get_font_by_name("SCRIPTBL"));
    text.setCharacterSize(24);

    const auto b = text.getLocalBounds();
    text.setOrigin(b.width/2, b.height/2);
}

void TextWidget::draw(sf::RenderWindow* window)
{
    window->draw(text, get_transform());
}
