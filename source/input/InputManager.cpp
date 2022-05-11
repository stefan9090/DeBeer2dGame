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

    void InputManager::updateKeyInput(int key, int scancode, int action, int mods)
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

    void InputManager::updateMouseButtonInput(int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            MouseButtonPressedEvent event;
            event.button = static_cast<EMouseButton>(button);
            m_rEventManager.publishEvent<MouseButtonPressedEvent>(event);
        }
        else
        {
            // Must be GLFW_RELEASE
            MouseButtonReleasedEvent event;
            event.button = static_cast<EMouseButton>(button);
            m_rEventManager.publishEvent<MouseButtonReleasedEvent>(event);
        }
    }

    void InputManager::updateScrollInput(double xOffset, double yOffset)
    {
        MouseScrollEvent event;
        event.xOffset = xOffset;
        event.yOffset = yOffset;
        m_rEventManager.publishEvent<MouseScrollEvent>(event);
    }

    void InputManager::updateCursorPos(double xPos, double yPos)
    {
        MouseMoveEvent event;
        event.newX = xPos;
        event.newY = yPos;
        event.deltaX = m_lastCursorXPos - xPos;
        event.deltaY = m_lastCursorYPos - yPos;
        m_rEventManager.publishEvent<MouseMoveEvent>(event);

        m_lastCursorXPos = xPos;
        m_lastCursorYPos = yPos;
    }
}