//
// Created by beerd on 1/10/2022.
//

#include "InputManager.h"

#include <Logger.h>

using namespace std::chrono;
using namespace std::chrono_literals;

//bool InputManager::isKeyPressedForAction(EInputAction action)
//{
//    if (!m_pWindow) return false;
//
//    bool pressed = false;
//
//    auto keySet = m_keyMapping.find(action);
//    if (keySet != m_keyMapping.end())
//    {
//        for (EInputKey key : keySet->second.keySet)
//        {
//            pressed = glfwGetKey(m_pWindow, static_cast<int>(key));
//            if (pressed) break;
//        }
//    }
//
//    return pressed;
//}

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

void InputManager::update(int key, int scancode, int action, int mods)
{

    LOG_INFO("pressed {} {}", key, scancode);

//    for (auto &[rAction, rActionInfo] : m_keyMapping)
//    {
//        bool isPressed = false;
//        for (EInputKey key : rActionInfo.keySet)
//        {
//            if (glfwGetKey(m_pWindow, static_cast<int>(key)))
//            {
//                isPressed = true;
//                break;
//            }
//        }
//
//        if (isPressed != rActionInfo.keyPressed)
//        {
//            rActionInfo.stateTimePoint = steady_clock::now();
//            rActionInfo.keyPressed = isPressed;
//        }
//    }
}
