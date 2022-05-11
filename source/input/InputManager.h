//
// Created by beerd on 1/10/2022.
//

#ifndef DEBEER2D_INPUTMANAGER_H
#define DEBEER2D_INPUTMANAGER_H

#include <GLFW/glfw3.h>
#include <chrono>
#include <optional>
#include <set>
#include <unordered_map>

#include <EventManager.h>

namespace Beer
{

    enum class EInputKey : int
    {
        unknown = -1,
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

    enum class EMouseButton : int
    {
        unknown = -1,
        button1 = 0,
        button2,
        button3,
        button4,
        button5,
        button6,
        button7,
        button8,
        left = button1,
        right = button2,
        middle = button3
    };

    namespace internal
    {
        class InputManager
        {
        private:
            EventManager &m_rEventManager;

            double m_lastCursorXPos{};
            double m_lastCursorYPos{};

        public:
            explicit InputManager(EventManager &rEventManager);
            void updateKeyInput(int key, int scancode, int action, int mods);
            void updateMouseButtonInput(int button, int action, int mods);
            void updateScrollInput(double xOffset, double yOffset);
            void updateCursorPos(double xPos, double yPos);
        };
    }// namespace internal


}// namespace Beer

#endif//DEBEER2D_INPUTMANAGER_H
