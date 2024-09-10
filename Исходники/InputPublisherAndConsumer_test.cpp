void InputPublisherAndConsumerTest::PublishAndConsumeKeyEvent() {
    status_t status;

    const int32_t deviceId = 1;
    const int32_t source = AINPUT_SOURCE_KEYBOARD;
    const int32_t action = AKEY_EVENT_ACTION_DOWN;
    const int32_t flags = AKEY_EVENT_FLAG_FROM_SYSTEM;
    const int32_t keyCode = AKEYCODE_ENTER;
    const int32_t scanCode = 13;
    const int32_t metaState = AMETA_ALT_LEFT_ON | AMETA_ALT_ON;
    const int32_t repeatCount = 1;
    const nsecs_t downTime = 3;
    const nsecs_t eventTime = 4;

    status = mPublisher->publishKeyEvent(deviceId, source, action, flags,
            keyCode, scanCode, metaState, repeatCount, downTime, eventTime);
    ASSERT_EQ(OK, status)
            << "publisher publishKeyEvent should return OK";

    status = mPublisher->sendDispatchSignal();
    ASSERT_EQ(OK, status)
            << "publisher sendDispatchSignal should return OK";

    status = mConsumer->receiveDispatchSignal();
    ASSERT_EQ(OK, status)
            << "consumer receiveDispatchSignal should return OK";

    InputEvent* event;
    status = mConsumer->consume(& mEventFactory, & event);
    ASSERT_EQ(OK, status)
            << "consumer consume should return OK";

    ASSERT_TRUE(event != NULL)
            << "consumer should have returned non-NULL event";
    ASSERT_EQ(AINPUT_EVENT_TYPE_KEY, event->getType())
            << "consumer should have returned a key event";

    KeyEvent* keyEvent = static_cast<KeyEvent*>(event);
    EXPECT_EQ(deviceId, keyEvent->getDeviceId());
    EXPECT_EQ(source, keyEvent->getSource());
    EXPECT_EQ(action, keyEvent->getAction());
    EXPECT_EQ(flags, keyEvent->getFlags());
    EXPECT_EQ(keyCode, keyEvent->getKeyCode());
    EXPECT_EQ(scanCode, keyEvent->getScanCode());
    EXPECT_EQ(metaState, keyEvent->getMetaState());
    EXPECT_EQ(repeatCount, keyEvent->getRepeatCount());
    EXPECT_EQ(downTime, keyEvent->getDownTime());
    EXPECT_EQ(eventTime, keyEvent->getEventTime());

    status = mConsumer->sendFinishedSignal();
    ASSERT_EQ(OK, status)
            << "consumer sendFinishedSignal should return OK";

    status = mPublisher->receiveFinishedSignal();
    ASSERT_EQ(OK, status)
            << "publisher receiveFinishedSignal should return OK";

    status = mPublisher->reset();
    ASSERT_EQ(OK, status)
            << "publisher reset should return OK";
}