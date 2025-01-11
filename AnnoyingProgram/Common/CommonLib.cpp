#include "CommonLib.h"

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

Delegate::Delegate(GenericObject* object, void(GenericObject::* delegate_function)())
{
    object_ = object;
    delegate_function_ = delegate_function;
}

Delegate::Delegate(void(* delegate_function)())
{
    global_func_ = delegate_function;
}

Delegate& Delegate::operator=(void(* delegate_function)())
{
    global_func_ = delegate_function;
    return *this;
}

void Delegate::call() const
{
    if(is_valid_object(object_) && delegate_function_)
        (object_->*delegate_function_)();
    else if(global_func_)
        (*global_func_)();
}

void Delegate::operator()() const
{
    call();
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
