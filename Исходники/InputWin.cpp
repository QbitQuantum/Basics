    // Callback that lists all gamepads.
    static BOOL CALLBACK gamepadCallback(LPCDIDEVICEINSTANCE device,
        LPVOID userData)
    {
        Impl* pimpl = static_cast<Impl*>(userData);

        IDirectInputDevice8* gamepad;
        if (FAILED(pimpl->input->CreateDevice(device->guidInstance,
            &gamepad, 0)))
        {
            return DIENUM_CONTINUE;
        }

        if (FAILED(gamepad->SetDataFormat(&c_dfDIJoystick)) ||
            FAILED(gamepad->SetCooperativeLevel(pimpl->window,
                DISCL_EXCLUSIVE | DISCL_FOREGROUND)) ||
            FAILED(gamepad->EnumObjects(axisCallback, gamepad, DIDFT_AXIS)))
        {
            gamepad->Release();
            return DIENUM_CONTINUE;
        }

        pimpl->gamepads.push_back(Win::shareComPtr(gamepad));

        return DIENUM_CONTINUE;
    }