//
// Created by beerd on 1/10/2022.
//

#include "InputManager.h"

#include <Logger.h>

#include <CoreEvents.h>

using namespace std::chrono;
using namespace std::chrono_literals;

namespace Beer::internal
{
    InputManager::InputManager(Beer::internal::EventManager &rEventManager)
        : m_rEventManager(rEventManager)
    {
    }

    void InputManager::update(int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            KeyPressedEvent event;
            event.key = static_cast<EInputKey>(key);
            m_rEventManager.publishEvent<KeyPressedEvent>(event);
        }
        else if(action == GLFW_RELEASE)
        {
            KeyReleaseEvent event;
            event.key = static_cast<EInputKey>(key);
            m_rEventManager.publishEvent<KeyReleaseEvent>(event);
        }
        else if (action == GLFW_REPEAT)
        {
            KeyRepeatEvent event;
            event.key = static_cast<EInputKey>(key);
            m_rEventManager.publishEvent<KeyRepeatEvent>(event);
        }
        else
        {
            LOG_WARNING("Unknown key action");
        }
    }
}