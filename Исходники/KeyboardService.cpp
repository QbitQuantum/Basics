void KeyboardService::keyboardButtonCallback( uint key, Event::Type type )
{
    if(mysInstance)
    {
        mysInstance->lockEvents();

        Event* evt = mysInstance->writeHead();
        evt->reset(type, Service::Keyboard, key);

        uint keyFlagsToRemove = 0;

        HANDLE_KEY_FLAG(296, Alt)
        HANDLE_KEY_FLAG(292, Shift)
        HANDLE_KEY_FLAG(294, Ctrl)

        // Convert arrow keys to buttons. This allows user code to do es.
        // evt.isButtonDown(Event::ButtonLeft) without having to make a
        // separate call to isKeyDown when using keyboards instead of gamepads.
        HANDLE_KEY_FLAG(KC_LEFT, ButtonLeft);
        HANDLE_KEY_FLAG(KC_RIGHT, ButtonRight);
        HANDLE_KEY_FLAG(KC_DOWN, ButtonDown);
        HANDLE_KEY_FLAG(KC_UP, ButtonUp);

        // Add some special keys as buttons
        HANDLE_KEY_FLAG(KC_RETURN, Button4);
        HANDLE_KEY_FLAG(KC_BACKSPACE, Button5);
        HANDLE_KEY_FLAG(KC_TAB, Button6);
        HANDLE_KEY_FLAG(KC_HOME, Button7);

        evt->setFlags(sKeyFlags);

        // Remove the bit of all buttons that have been unpressed.
        sKeyFlags &= ~keyFlagsToRemove;

        mysInstance->unlockEvents();
    }
}