//
// Created by stefan on 5/5/22.
//

#ifndef DEBEER2D_COREEVENTS_H
#define DEBEER2D_COREEVENTS_H

#include <Event.h>
#include <glm/glm.hpp>

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
}

#endif//DEBEER2D_COREEVENTS_H
