//
// Created by stefan on 4/19/22.
//

#ifndef DEBEER2D_LAYER_H
#define DEBEER2D_LAYER_H

#include <string>

#include <Event.h>
#include <EventClass.h>

namespace Beer
{
    template<typename LayerType>
    class Layer : public internal::EventClass<LayerType>
    {
    protected:
        internal::EventEndPoint *m_pEventBus{};

    public:
        virtual ~Layer() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}

        void setEventBus(internal::EventEndPoint *pEventBus) { m_pEventBus = pEventBus; }

    protected:

        template<typename EventType, typename EventClassType>
        void subscribeTo(EventClassType &rReceiver)
        {
            assert(m_pEventBus);
            m_pEventBus->template subscribeTo<EventType>(rReceiver);
        }

        template<typename EventType, typename Receiver>
        void unsubscribeFrom(Receiver &rReceiver)
        {
            assert(m_pEventBus);
            m_pEventBus->template unsubscribeFrom<EventType>(rReceiver);
        }
    };


}// namespace Beer

#endif//DEBEER2D_LAYER_H
