//
// Created by beerd on 1/10/2022.
//

#include "InputManager.h"
using namespace std::chrono;
using namespace std::chrono_literals;

InputManager::InputManager(GLFWwindow *pWindow, EventBus *pEventBus)
    : m_pWindow{pWindow}
    , m_pEventBus{pEventBus}
{
}

bool InputManager::isKeyPressedForAction(EInputAction action)
{
    if (!m_pWindow) return false;

    bool pressed = false;

    auto keySet = m_keyMapping.find(action);
    if (keySet != m_keyMapping.end())
    {
        for (EInputKey key : keySet->second.keySet)
        {
            pressed = glfwGetKey(m_pWindow, static_cast<int>(key));
            if (pressed) break;
        }
    }

    return pressed;
}

void InputManager::mapActionToKey(EInputAction action, EInputKey key)
{
    m_keyMapping[action].keySet.insert(key);
}

ActionState InputManager::getActionState(EInputAction action)
{
    ActionState state;

    auto inputDef = m_keyMapping.find(action);
    if (inputDef != m_keyMapping.end())
    {
        ActionInfo &rActionInfo = inputDef->second;
        state.isActive = rActionInfo.keyPressed;
        state.stateDuration = steady_clock::now() - rActionInfo.stateTimePoint;
    }

    return state;
}

void InputManager::tick()
{
    if (!m_pWindow) return;

    for (auto &[rAction, rActionInfo] : m_keyMapping)
    {
        bool isPressed = false;
        for (EInputKey key : rActionInfo.keySet)
        {
            if (glfwGetKey(m_pWindow, static_cast<int>(key)))
            {
                isPressed = true;
                break;
            }
        }

        if (isPressed != rActionInfo.keyPressed)
        {
            rActionInfo.stateTimePoint = steady_clock::now();
            rActionInfo.keyPressed = isPressed;
        }

        if (m_pEventBus)
        {
            ActionState state;
            state.isActive = rActionInfo.keyPressed;
            state.stateDuration = steady_clock::now() - rActionInfo.stateTimePoint;

            m_pEventBus->triggerNow<ActionState>(state);
        }
    }
}
