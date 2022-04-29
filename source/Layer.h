//
// Created by stefan on 4/19/22.
//

#ifndef DEBEER2D_LAYER_H
#define DEBEER2D_LAYER_H

#include <string>

#include <Event.h>

class Layer
{
protected:
    EventBus &m_rEventBus;

public:
    explicit Layer(EventBus &rEventBus);
    virtual ~Layer();

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate() {}
};


#endif//DEBEER2D_LAYER_H
