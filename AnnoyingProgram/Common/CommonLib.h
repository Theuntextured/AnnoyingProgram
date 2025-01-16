#pragma once

#include "CommonIncludes.h"
#include <set>
#include <functional>

#define CHECK_RET_FALSE(expr, message) if(!(expr)) {std::cout << (message) << std::endl; return false;}
#define CHECK_RET(expr, message) if(!(expr)) {std::cout << (message) << std::endl; return;}
#define CHECK_RET_VAL(expr, message, val) if(!(expr)) {std::cout << (message) << std::endl; return val;}
#define LOG(message) std::cout << (message) << std::endl

#define INDEX_INVALID (-1)
#define FORCEINLINE __forceinline

template <typename T>
bool vector_contains(std::vector<T>& vec, T element)
{
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

class GenericObject
{
public:
    static std::set<GenericObject*> valid_objects;
    GenericObject();

    virtual ~GenericObject();
};

bool is_valid_object(GenericObject* const object);

struct Delegate {
public:
    Delegate() = default;

    // Template function to set the delegate to any callable
    template <typename T, typename F>
    void bind(T* object, F&& func) {
        // Store the callable
        callable_ = [object, func = std::forward<F>(func)]() {
            if(is_valid_object(object))
                (object->*func)(); // Call the member function
        };
    }

    // Call the stored function
    void call() const {
        if (callable_) {
            callable_(); // Invoke the stored callable
        }
    }

    // Overload operator() for convenience
    void operator()() const {
        call(); // Simply call the call function
    }

private:
    std::function<void()> callable_; // Store any callable
};

template <typename T>
T square(const T& a) { return a * a; }

sf::Transform lerp(const sf::Transform& start, const sf::Transform& end, const float t);

sf::Color lerp(const sf::Color& start, const sf::Color& end, const float t);

template <typename T>
T lerp(const T& start, const T& end, const float t)
{
    return start + static_cast<T>((end - start) * t);
}

template <typename T>
T rand_range(const T lo, const T hi)
{
    return lo + static_cast <T> (rand()) /( static_cast <T> (RAND_MAX/(hi-lo)));
}

template <typename T>
sf::Vector2<T> rand_vec2(const sf::Vector2<T>& lo, const sf::Vector2<T>& hi)
{
    return sf::Vector2<T>(rand_range(lo.x, hi.x), rand_range(lo.y, hi.y));
}

sf::Color rand_color(const bool random_alpha = false);

template <typename T>
T clamp(const T& value, const T& lo, const T& hi)
{
    return std::max(lo, std::min(hi, value));
}

template <typename T>
T len_squared(const sf::Vector2<T>& vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

template <typename T>
T len(const sf::Vector2<T>& vec)
{
    return std::sqrt(len_squared(vec));
}

template <typename T>
std::string vec_to_string(const sf::Vector2<T>& vec)
{
    return "{ " + std::to_string(vec.x) + ", " + std::to_string(vec.y) + " }";
}

int get_task_bar_height();