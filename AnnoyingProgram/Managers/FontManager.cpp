#include "FontManager.h"

FontManager FontManager::instance_ = FontManager();

const sf::Font& FontManager::get_font_by_name(const sf::String& name, bool fallback)
{
    const auto f = instance_.fonts_.find(name);
    if(f == instance_.fonts_.end())
    {
        bool b = instance_.fonts_[name].loadFromFile("C:/WINDOWS/Fonts/" + name + ".ttf");
        if(!b)
        {
            instance_.fonts_.erase(name);
            if(fallback)
                return get_fallback_font();
            
            static sf::Font fo;
            return fo;
        }
    }
    return instance_.fonts_[name];
}

const sf::Font& FontManager::get_fallback_font()
{
    return get_font_by_name("Arial", false);
}

const sf::Font& FontManager::get_random_font()
{
    return get_font_by_name(instance_.font_names_[rand() % instance_.font_names_.size()], true);
}
