#pragma once


#include "CommonIncludes.h"
#include <set>

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

inline bool is_valid_object(GenericObject* const object);

class Delegate
{
public:
    Delegate() = default;
    explicit Delegate(GenericObject* object, void (GenericObject::*delegate_function)());
    explicit Delegate(void (*delegate_function)());
    
    Delegate& operator=(void (*delegate_function)());
    
    FORCEINLINE void call() const;
    void operator()() const;

private:
    GenericObject* object_ = nullptr;
    void (GenericObject::*delegate_function_)() = nullptr;
    void(* global_func_)() = nullptr;
};

template <typename T>
T square(const T& a) { return a * a; }

sf::Transform lerp(const sf::Transform& start, const sf::Transform& end, const float t);
