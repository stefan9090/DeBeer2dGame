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
        EInputKey key = EInputKey::unknown;
    };

    struct KeyReleaseEvent : public Event<KeyReleaseEvent>
    {
        EInputKey key = EInputKey::unknown;
    };

    struct KeyRepeatEvent : public Event<KeyRepeatEvent>
    {
        EInputKey key = EInputKey::unknown;
        int count{};
    };

    struct MouseButtonPressedEvent : public Event<MouseButtonPressedEvent>
    {
        EMouseButton button = EMouseButton::unknown;
    };

    struct MouseButtonReleasedEvent : public Event<MouseButtonReleasedEvent>
    {
        EMouseButton button = EMouseButton::unknown;
    };

    struct MouseScrollEvent : public Event<MouseScrollEvent>
    {
        double xOffset{};
        double yOffset{};
    };

    struct MouseMoveEvent : public Event<MouseMoveEvent>
    {
        double newX{};
        double newY{};

        double deltaX{};
        double deltaY{};
    };
}

#endif//DEBEER2D_COREEVENTS_H
