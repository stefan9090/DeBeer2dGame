//
// Created by beerd on 1/10/2022.
//

#ifndef DEBEER2D_INPUTMANAGER_H
#define DEBEER2D_INPUTMANAGER_H

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <set>
#include <chrono>
#include <optional>

#include <Event.h>

enum class EInputKey : int
{
    space = GLFW_KEY_SPACE,
    apostrophe = GLFW_KEY_APOSTROPHE,
    comma = GLFW_KEY_COMMA,
    minus,
    period,
    slash,

    num0 = GLFW_KEY_0,
    num1,
    num2,
    num3,
    num4,
    num5,
    num6,
    num7,
    num8,
    num9,

    semicolon = GLFW_KEY_SEMICOLON,
    equal = GLFW_KEY_EQUAL,

    a = GLFW_KEY_A,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,
    leftBracket,
    backslash,
    rightBracket,

    graveAccent = GLFW_KEY_GRAVE_ACCENT,
    escape = GLFW_KEY_ESCAPE,
    enter,
    tab,
    backspace,
    insert,
    deleteKey,
    right,
    left,
    down,
    up,
    pageUp,
    pageDown,
    home,
    end,

    capsLock = GLFW_KEY_CAPS_LOCK,
    scrollLock,
    numLock,
    printScreen,
    pause,

    f1 = GLFW_KEY_F1,
    f2,
    f3,
    f5,
    f6,
    f7,
    f8,
    f9,
    f10,
    f11,
    f12,
    f13,
    f14,
    f15,
    f16,
    f17,
    f18,
    f19,
    f20,
    f21,
    f22,
    f23,
    f24,
    f25,

    keypad0 = GLFW_KEY_KP_0,
    keypad1,
    keypad2,
    keypad3,
    keypad4,
    keypad5,
    keypad6,
    keypad7,
    keypad8,
    keypad9,
    keypadDecimal,
    keyPadDivide,
    keypadMultiply,
    keypadSubtract,
    keypadAdd,
    keypadEnter,
    keypadEqual,

    leftShift = GLFW_KEY_LEFT_SHIFT,
    leftControl,
    leftAlt,
    leftSuper,
    rightShift,
    rightControl,
    rightAlt,
    rightSuper,
    menu
};

enum class EInputAction
{
    up,
    down,
    left,
    right,
    close
};

struct ActionState
{
    bool isActive;
    std::set<EInputKey> pressedKeys;
    std::chrono::steady_clock::duration stateDuration;
};

class InputManager
{
private:

    struct ActionInfo
    {
        std::set<EInputKey> keySet;
        bool keyPressed;
        std::chrono::steady_clock::time_point stateTimePoint;
    };

    std::unordered_map<EInputAction, ActionInfo> m_keyMapping;
    GLFWwindow *m_pWindow{};
    EventBus *m_pEventBus{};

public:
    InputManager() = default;
    InputManager(GLFWwindow *pWindow, EventBus *pEventBus);

    void mapActionToKey(EInputAction action, EInputKey key);

    bool isKeyPressedForAction(EInputAction action);
    ActionState getActionState(EInputAction action);

    void tick();
};


#endif//DEBEER2D_INPUTMANAGER_H
