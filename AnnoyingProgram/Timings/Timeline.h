#pragma once
#include "Tickable.h"
#include <assert.h>

template <typename T>
struct TimelinePoint
{
public:
    TimelinePoint(const double time, const T& data);
    bool operator<(const TimelinePoint<T>& other) const;
    T data;
    double time;    
};

enum class TimelinePlayType : sf::Int8
{
    Forward = 0,
    Reverse = 1,
    PingPong = 2,
    Invalid = INDEX_INVALID
};

template <typename T>
TimelinePoint<T>::TimelinePoint(const double time, const T& data)
{
    this->time = std::max(0., time);
    this->data = data;
}

template <typename T>
bool TimelinePoint<T>::operator<(const TimelinePoint<T>& other) const
{
    return this->time < other.time;
}

template <typename T>
class Timeline : Tickable
{
public:
    explicit Timeline(GenericObject* owner, const std::vector<TimelinePoint<T>> points, bool destroy_on_finish = true)
    {
        if(points.empty()) return;
        this->points_ = points;
        std::sort(points_.begin(), points_.end());
        max_time_ = points_.back().time;
        min_time_ = points_.front().time;
        destroy_on_finish_ = destroy_on_finish;
        owner_ = owner;
    }

    void bind_property(T& property)
    {
        bound_property_ = &property;
    }
    
    void tick(const double delta_time) override
    {
        if(!is_valid_object(owner_))
        {
            mark_for_deletion();
            return;
        }
        bool finish = false;
        if(points_.empty()) return;
        switch (play_type_)
        {
        case TimelinePlayType::Forward:
            current_time_ += delta_time;
            if (current_time_ >= max_time_)
            {
                current_time_ = max_time_;
                play_type_ = TimelinePlayType::Invalid;
                finished();
                if(destroy_on_finish_) finish = true;
            }
            break;
        case TimelinePlayType::Reverse:
            current_time_ -= delta_time;
            if (current_time_ <= 0)
            {
                current_time_ = 0;
                play_type_ = TimelinePlayType::Invalid;
                finished();
                if(destroy_on_finish_) finish = true;
            }
            break;
        case TimelinePlayType::PingPong:
            if(ping_pong_reverse_)
            {
                current_time_ -= delta_time;
                if (current_time_ <= 0)
                {
                    current_time_ = -current_time_;
                    ping_pong_reverse_ = false;
                    bounced();
                }
                break;
            }
            current_time_ += delta_time;
            if (current_time_ >= max_time_)
            {
                current_time_ = max_time_ - (current_time_ - max_time_);
                ping_pong_reverse_ = true;
                bounced();
            }
            break;
        default:
            return;
        }

        if(bound_property_ != nullptr)
        {
            *bound_property_ = get_current_data();
        }
        
        if(finish)
            mark_for_deletion();
    }
    
    void play(const TimelinePlayType play_type = TimelinePlayType::Forward)
    {
        if(points_.empty()) return;
        play_type_ = play_type;
        if(play_type == TimelinePlayType::Reverse)
            current_time_ = max_time_;
    }
    
    T get_current_data() const
    {
        if(points_.empty()) return T();
        if(current_time_ <= min_time_) return points_.front().data;
        if(current_time_ >= max_time_) return points_.back().data;

        for(size_t i = 1; i < points_.size(); i++)
        {
            if(current_time_ <= points_[i].time && current_time_ >= points_[i - 1].time)
            {
                const float lerp_factor = static_cast<float>((current_time_ - points_[i - 1].time) / (points_[i].time - points_[i - 1].time));
                return lerp(points_[i - 1].data, points_[i].data, lerp_factor);
            }
        }
        assert(0);
        return T();
    }

    Delegate finished;
    Delegate bounced;
private:
    std::vector<TimelinePoint<T>> points_;
    TimelinePlayType play_type_ = TimelinePlayType::Invalid;
    double current_time_ = 0.0;
    bool ping_pong_reverse_ = false;
    double max_time_ = 0.0;
    double min_time_ = 0.0;
    T* bound_property_ = nullptr;
    bool destroy_on_finish_ = false;
    GenericObject* owner_ = nullptr;
};


using TransformTimeline = Timeline<sf::Transform>;
using ColorTimeline = Timeline<sf::Color>;
using FloatTimeline = Timeline<double>;