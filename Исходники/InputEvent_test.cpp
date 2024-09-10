TEST_F(KeyEventTest, Properties) {
    KeyEvent event;

    // Initialize and get properties.
    const nsecs_t ARBITRARY_DOWN_TIME = 1;
    const nsecs_t ARBITRARY_EVENT_TIME = 2;
    event.initialize(2, AINPUT_SOURCE_GAMEPAD, AKEY_EVENT_ACTION_DOWN,
            AKEY_EVENT_FLAG_FROM_SYSTEM, AKEYCODE_BUTTON_X, 121,
            AMETA_ALT_ON, 1, ARBITRARY_DOWN_TIME, ARBITRARY_EVENT_TIME);

    ASSERT_EQ(AINPUT_EVENT_TYPE_KEY, event.getType());
    ASSERT_EQ(2, event.getDeviceId());
    ASSERT_EQ(static_cast<int>(AINPUT_SOURCE_GAMEPAD), event.getSource());
    ASSERT_EQ(AKEY_EVENT_ACTION_DOWN, event.getAction());
    ASSERT_EQ(AKEY_EVENT_FLAG_FROM_SYSTEM, event.getFlags());
    ASSERT_EQ(AKEYCODE_BUTTON_X, event.getKeyCode());
    ASSERT_EQ(121, event.getScanCode());
    ASSERT_EQ(AMETA_ALT_ON, event.getMetaState());
    ASSERT_EQ(1, event.getRepeatCount());
    ASSERT_EQ(ARBITRARY_DOWN_TIME, event.getDownTime());
    ASSERT_EQ(ARBITRARY_EVENT_TIME, event.getEventTime());

    // Set source.
    event.setSource(AINPUT_SOURCE_JOYSTICK);
    ASSERT_EQ(static_cast<int>(AINPUT_SOURCE_JOYSTICK), event.getSource());
}