//
// Created by beerd on 1/10/2022.
//

#include "InputManager.h"

InputManager::InputManager(GLFWwindow *pWindow)
    : m_pWindow{pWindow}
{
}

bool InputManager::isKeyPressedForAction(EInputAction action)
{
    if (!m_pWindow) return false;

    bool pressed = false;

    auto keySet = m_keyMapping.find(action);
    if (keySet != m_keyMapping.end())
    {
        for (EInputKey key : keySet->second)
        {
            pressed = glfwGetKey(m_pWindow, static_cast<int>(key));
            if (pressed) break;
        }
    }

    return pressed;
}

void InputManager::mapActionToKey(EInputAction action, EInputKey key)
{
    m_keyMapping[action].insert(key);
}
