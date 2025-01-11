#pragma once
#include "../Common/CommonLib.h"

class FontManager
{
public:
    FontManager() = default;
    static const sf::Font& get_font_by_name(const sf::String& name, bool fallback = true);
    static const sf::Font& get_fallback_font();
private:
    std::map<sf::String, sf::Font> fonts_;
    static FontManager instance_;
};
