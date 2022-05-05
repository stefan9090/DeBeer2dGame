//
// Created by stefan on 5/5/22.
//

#ifndef DEBEER2D_EVENTMANAGER_H
#define DEBEER2D_EVENTMANAGER_H

#include <vector>

#include "Event.h"

namespace Beer::internal
{
    class EventManager
    {
    private:
        using EventBusVec_t = std::vector<EventEndPoint*>;

        EventBusVec_t m_busses;

    public:
        void pushBack(EventEndPoint *pNewBus);
        void pushFront(EventEndPoint *pNewBus);

        void popFront();
        void popBack();

        template<typename EventType>
        void publishEvent(EventType &rEvent)
        {
            for (auto i = m_busses.rbegin(); i != m_busses.rend(); i++)
            {
                if (!(*i)->publishEvent(rEvent))
                {
                    break;
                }
            }
        }
    };
}

#endif//DEBEER2D_EVENTMANAGER_H
