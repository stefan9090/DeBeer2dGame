//
// Created by stefan on 5/5/22.
//

#ifndef DEBEER2D_COREEVENTS_H
#define DEBEER2D_COREEVENTS_H

#include <Event.h>
#include <glm/glm.hpp>

#include <InputManager.h>

namespace Beer
{
    struct WindowCloseEvent : public Event<WindowCloseEvent>
    {
        int hi{};
    };

    struct WindowResizeEvent : public Event<WindowResizeEvent>
    {
        int newX{};
        int newY{};
    };

    struct KeyPressedEvent : public Event<KeyPressedEvent>
    {
        EInputKey key = EInputKey::none;
    };

    struct KeyReleaseEvent : public Event<KeyReleaseEvent>
    {
        EInputKey key = EInputKey::none;
    };

    struct KeyRepeatEvent : public Event<KeyRepeatEvent>
    {
        EInputKey key = EInputKey::none;
        int count{};
    };

    struct MouseScrollUpEvent : public Event<MouseScrollUpEvent>
    {

    };

    struct MouseScrollDownEvent : public Event<MouseScrollDownEvent>
    {

    };

    struct MouseMoveEvent : public Event<MouseMoveEvent>
    {
        int newX{};
        int newY{};

        int deltaX{};
        int deltaY{};
    };
}

#endif//DEBEER2D_COREEVENTS_H
