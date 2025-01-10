#pragma once

#include <set>

#include "CommonIncludes.h"

#define FORCEINLINE __forceinline
#define CHECK_RET_FALSE(expr, message) if(!(expr)) {std::cout << message << std::endl; return false;}
#define CHECK_RET(expr, message) if(!(expr)) {std::cout << message << std::endl; return;}
#define CHECK_RET_VAL(expr, message, val) if(!(expr)) {std::cout << message << std::endl; return val;}
#define INDEX_INVALID -1

template <typename T>
bool vector_contains(std::vector<T>& vec, T element)
{
	return std::find(vec.begin(), vec.end(), element) != vec.end();
}

class GenericObject
{
public:
	static std::set<GenericObject*> valid_objects;
	GenericObject()
	{
		valid_objects.insert(this);
	}
	virtual ~GenericObject()
	{
		valid_objects.erase(this);
	}
};

// ReSharper disable once CppParameterMayBeConstPtrOrRef
inline bool is_valid_object(GenericObject* const object)
{
	if(!object) return false;
	return GenericObject::valid_objects.find(object) != GenericObject::valid_objects.end();
} 

struct Delegate
{
public:
	Delegate() = default;
	explicit Delegate(GenericObject* object, void (GenericObject::*delegate_function)())
	{
		object_ = object;
		delegate_function_ = delegate_function;
	}
	FORCEINLINE void call() const
	{
		if(is_valid_object(object_) && delegate_function_)
			(object_->*delegate_function_)();
	}
	FORCEINLINE void operator()() const
	{
		call();
	}
private:
	GenericObject* object_ = nullptr;
	void (GenericObject::*delegate_function_)() = nullptr;
};