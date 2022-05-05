//
// Created by beerd on 12/21/2021.
//

#ifndef DEBEER2D_EVENT_H
#define DEBEER2D_EVENT_H

#include "FamilyType.h"
#include "EventClass.h"

#include <cstdint>
#include <entt.hpp>
#include <any>

namespace Beer
{
    using EventID = internal::FamilyID;

    namespace internal
    {
        class FunctionWrapper
        {
            std::any m_func;

        public:
            FunctionWrapper() = default;

            template<typename Arg>
            explicit FunctionWrapper(std::function<bool(const Arg&)> func)
                : m_func(func)
            {}

            template<typename Arg>
            void wrapFunction(std::function<bool(const Arg&)> func)
            {
                m_func = func;
            }

            template<typename Arg>
            bool operator()(const Arg &rArg)
            {
                return std::invoke(std::any_cast<std::function<bool(const Arg&)>>(m_func), rArg);
            }
        };

        class IEvent
        {
            virtual FamilyID getEventID() = 0;
        };

        using EventFamily = internal::Family<internal::IEvent>;



        class EventEndPoint
        {
            std::unordered_map<EventID, internal::FunctionWrapper> subscribers;

        public:
            template<typename EventType, typename SystemType>
            void subscribeTo(SystemType &receiver)
            {

                auto func = [&receiver](const EventType &rEvent) -> bool {
                    return receiver.receive(rEvent);
                };

                internal::FunctionWrapper callback;
                callback.wrapFunction<EventType>(func);

                subscribers[EventType::getStaticEventID()] = callback;

//                auto search = subscribers.find(EventType::getStaticEventID());
//                if (search == subscribers.end())
//                {
//                    subscribers[EventType::getStaticEventID()] = std::unordered_map<EventClassID, internal::FunctionWrapper>();
//                }
//                subscribers[EventType::getStaticEventID()].insert({SystemType::getStaticSystemID(), callback});
            }

            template<typename EventType, typename Receiver>
            void unsubscribeFrom(Receiver &receiver)
            {
                auto search = subscribers.find(EventType::getStaticEventID());
                if (search != subscribers.end())
                {
                    subscribers[EventType::getStaticEventID()].erase(Receiver::getStaticSystemID());
                }
            }

            template<typename EventType>
            bool publishEvent(EventType &rEvent)
            {
                return subscribers[EventType::getStaticEventID()](rEvent);
            }
        };
    }// namespace internal

    template<typename EventType>
    class Event : public internal::IEvent
    {
    public:
        static const EventID getStaticEventID()
        {
            return internal::EventFamily::type<EventType>;
        }

        EventID getEventID() override
        {
            return internal::EventFamily::type<EventType>;
        }
    };
}// namespace Beer

#endif//DEBEER2D_EVENT_H
