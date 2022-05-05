//
// Created by stefan on 5/5/22.
//

#include "EventManager.h"

namespace Beer::internal
{
    void EventManager::pushBack(EventEndPoint *pNewBus)
    {
        m_busses.push_back(pNewBus);
    }

    void EventManager::pushFront(EventEndPoint *pNewBus)
    {
        m_busses.insert(m_busses.begin(), pNewBus);
    }

    void EventManager::popFront()
    {
        m_busses.pop_back();
    }

    void EventManager::popBack()
    {
        m_busses.erase(m_busses.begin());
    }
}


