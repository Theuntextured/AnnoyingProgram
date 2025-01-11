#pragma once

#define EVENT_BODY() public:\
                     void start() override;\
                     void end() override;\
                     void tick() override;

class EventManager;

class Event : public GenericObject
{
    friend class EventManager;
public:
    virtual void start() {}
    void operator()() { start_internal(); }
    virtual void end() {}
    virtual void tick() {}
protected:
    void start_internal()
    {
        if(started_)
            return;
        started_ = true;
        start();
    }
    void end_internal()
    {
        if(!started_ || ended_)
            return;
        ended_ = true;
        end();
    }
    bool started_ = false;
    bool ended_ = false;
    
};
