//
// Created by stefan on 5/4/22.
//

#ifndef DEBEER2D_EVENTCLASS_H
#define DEBEER2D_EVENTCLASS_H

#include <Event.h>

namespace Beer::internal
{
    using EventClassID = FamilyID;

    class IEventClass
    {
    private:
        virtual EventClassID getSystemID() = 0;
    };

    using EventClassFamily = Family<IEventClass>;

    template<typename EventClassType>
    class EventClass : public IEventClass
    {
    private:
        static const EventClassID m_familyType;

    public:
        EventClassID getSystemID() override
        {
            return EventClassFamily::type<EventClassType>;
        }

        static EventClassID getStaticSystemID()
        {
            return EventClassFamily::type<EventClassType>;
        }
    };
}

#endif//DEBEER2D_EVENTCLASS_H
