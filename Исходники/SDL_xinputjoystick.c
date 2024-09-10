void
SDL_XINPUT_JoystickUpdate(SDL_Joystick * joystick)
{
    HRESULT result;
    XINPUT_STATE_EX XInputState;
    XINPUT_BATTERY_INFORMATION_EX XBatteryInformation;

    if (!XINPUTGETSTATE)
        return;

    result = XINPUTGETSTATE(joystick->hwdata->userid, &XInputState);
    if (result == ERROR_DEVICE_NOT_CONNECTED) {
        return;
    }

    SDL_zero(XBatteryInformation);
    if (XINPUTGETBATTERYINFORMATION) {
        result = XINPUTGETBATTERYINFORMATION(joystick->hwdata->userid, BATTERY_DEVTYPE_GAMEPAD, &XBatteryInformation);
    }

    /* only fire events if the data changed from last time */
    if (XInputState.dwPacketNumber && XInputState.dwPacketNumber != joystick->hwdata->dwPacketNumber) {
        if (SDL_XInputUseOldJoystickMapping()) {
            UpdateXInputJoystickState_OLD(joystick, &XInputState, &XBatteryInformation);
        } else {
            UpdateXInputJoystickState(joystick, &XInputState, &XBatteryInformation);
        }
        joystick->hwdata->dwPacketNumber = XInputState.dwPacketNumber;
    }

    if (joystick->hwdata->rumble_expiration) {
        Uint32 now = SDL_GetTicks();
        if (SDL_TICKS_PASSED(now, joystick->hwdata->rumble_expiration)) {
            SDL_XINPUT_JoystickRumble(joystick, 0, 0, 0);
        }
    }
}