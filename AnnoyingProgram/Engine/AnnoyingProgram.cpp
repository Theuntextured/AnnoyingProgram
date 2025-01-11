#include <iostream>
#include <functional>

class go {
public:
    virtual void commonFunction() {
        std::cout << "GenericObject function\n";
    }
    virtual ~go() = default;
};

class fe : public go {
public:
    void child_function()
    {
        std::cout << "FirstEvent function\n";

    }
};

int main() {
    go* event = new fe;

    // Using std::function to store the member function
    std::function<void()> func = [&event]() { event->child_function(); };

    func(); // Calls FirstEvent's function
    return 0;
}
/*
#include "Engine.h"

int main()
{
    Engine e;
    
    return 0;
}
*/