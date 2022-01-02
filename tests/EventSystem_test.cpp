//
// Created by beerd on 12/24/2021.
//

#include <gtest/gtest.h>
#include <Event.h>

using ::testing::Test;

struct SomeEvent {};
struct SomePayloadEvent
{
    bool payload;
};

class EventSystemTesting : public Test
{
public:
    EventBus eventBus;
    bool wasCalled = false;

    void callbackFunc()
    {
        wasCalled = true;
    }

    void callbackPayload(SomePayloadEvent rEvent)
    {
        wasCalled = rEvent.payload;
    }
};

TEST_F(EventSystemTesting, triggerNow)
{
    eventBus.listenTo<SomeEvent, &EventSystemTesting::callbackFunc>(this);

    eventBus.triggerNow<SomeEvent>();

    EXPECT_TRUE(wasCalled);
}

TEST_F(EventSystemTesting, triggerLater)
{
    eventBus.listenTo<SomeEvent, &EventSystemTesting::callbackFunc>(this);

    eventBus.triggerLater<SomeEvent>();

    EXPECT_FALSE(wasCalled);
    eventBus.update();
    EXPECT_TRUE(wasCalled);
}

TEST_F(EventSystemTesting, triggerNowWithPayload)
{
    eventBus.listenTo<SomePayloadEvent, &EventSystemTesting::callbackPayload>(this);

    eventBus.triggerNow<SomePayloadEvent>(true);

    EXPECT_TRUE(wasCalled);
}

TEST_F(EventSystemTesting, triggerLaterWithPayload)
{
    eventBus.listenTo<SomePayloadEvent, &EventSystemTesting::callbackPayload>(this);

    eventBus.triggerLater<SomePayloadEvent>(true);

    EXPECT_FALSE(wasCalled);
    eventBus.update();
    EXPECT_TRUE(wasCalled);
}
