#include "CommonLib.h"

#include <windows.h>


std::set<GenericObject*> GenericObject::valid_objects = std::set<GenericObject*>();

GenericObject::GenericObject()
{
    valid_objects.insert(this);
}

GenericObject::~GenericObject()
{
    valid_objects.erase(this);
}

bool is_valid_object(GenericObject* const object)
{
    if(!object) return false;
    return GenericObject::valid_objects.find(object) != GenericObject::valid_objects.end();
}

sf::Transform lerp(const sf::Transform& start, const sf::Transform& end, const float t)
{
    sf::Transform result;
    const float* a = reinterpret_cast<const float*>(&start);
    const float* b = reinterpret_cast<const float*>(&end);
    float* c = reinterpret_cast<float*>(&result);
    
    for(size_t i = 0; i < 16; i++)
        c[i] = std::lerp(a[i], b[i], t);
    
    return result;
}

sf::Color lerp(const sf::Color& start, const sf::Color& end, const float t)
{
    return sf::Color(lerp(start.r, end.r, t), lerp(start.g, end.g, t), lerp(start.b, end.b, t), lerp(start.a, end.a, t));
}

sf::Color rand_color(const bool random_alpha)
{
    return {
        static_cast<sf::Uint8>(rand() % 255),
        static_cast<sf::Uint8>(rand() % 255),
        static_cast<sf::Uint8>(rand() % 255),
        random_alpha ? static_cast<sf::Uint8>(rand() % 255) : static_cast<sf::Uint8>(255)
    };
}

int get_task_bar_height()
{
    RECT rect;
    HWND taskBar = FindWindow(L"Shell_traywnd", NULL);
    if(taskBar && GetWindowRect(taskBar, &rect)) {
        return rect.bottom - rect.top;
    }
}
