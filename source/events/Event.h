//
// Created by beerd on 12/21/2021.
//

#ifndef DEBEER2D_EVENT_H
#define DEBEER2D_EVENT_H

#include <entt.hpp>
#include <cstdint>

class EventBus
{
private:
    entt::dispatcher m_dispatcher{};

public:
    void update();

    template<typename EventType, auto CallBackType, typename InstanceType>
    void listenTo(const InstanceType &&rInstance ...)
    {
        m_dispatcher.sink<EventType>().template connect<CallBackType>(rInstance);
    }

    template<typename EventType>
    void triggerNow()
    {
        m_dispatcher.trigger<EventType>();
    }

    template<typename EventType, typename T>
    void triggerNow(const T &rVars ...)
    {
        m_dispatcher.trigger<EventType>(rVars);
    }

    template<typename EventType>
    void triggerLater()
    {
        m_dispatcher.enqueue<EventType>();
    }

    template<typename EventType, typename T>
    void triggerLater(const T &rVars ...)
    {
        m_dispatcher.enqueue<EventType>(rVars);
    }

};

#endif //DEBEER2D_EVENT_H
