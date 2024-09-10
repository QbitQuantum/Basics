DWORD ControllerBase::GetKeystroke(DWORD dwReserved, XINPUT_KEYSTROKE* pKeystroke)
{
    if (m_passthrough)
        return XInputModuleManager::Get().XInputGetKeystroke(m_passthroughindex, dwReserved, pKeystroke);

    XINPUT_STATE xstate;
    ZeroMemory(&xstate, sizeof(XINPUT_STATE));
    XInputGetState(m_user, &xstate);

    static WORD repeat[14];
    static WORD flags[14];

    ZeroMemory(pKeystroke, sizeof(XINPUT_KEYSTROKE));
    pKeystroke->UserIndex = (BYTE)m_user;

    static const WORD allButtonIDs[14] =
    {
        XINPUT_GAMEPAD_A,
        XINPUT_GAMEPAD_B,
        XINPUT_GAMEPAD_X,
        XINPUT_GAMEPAD_Y,
        XINPUT_GAMEPAD_LEFT_SHOULDER,
        XINPUT_GAMEPAD_RIGHT_SHOULDER,
        XINPUT_GAMEPAD_BACK,
        XINPUT_GAMEPAD_START,
        XINPUT_GAMEPAD_LEFT_THUMB,
        XINPUT_GAMEPAD_RIGHT_THUMB,
        XINPUT_GAMEPAD_DPAD_UP,
        XINPUT_GAMEPAD_DPAD_DOWN,
        XINPUT_GAMEPAD_DPAD_LEFT,
        XINPUT_GAMEPAD_DPAD_RIGHT
    };

    static const u16 keyIDs[14] =
    {
        VK_PAD_A,
        VK_PAD_B,
        VK_PAD_X,
        VK_PAD_Y,
        VK_PAD_LSHOULDER,
        VK_PAD_RSHOULDER,
        VK_PAD_BACK,
        VK_PAD_START,
        VK_PAD_LTHUMB_PRESS,
        VK_PAD_RTHUMB_PRESS,
        VK_PAD_DPAD_UP,
        VK_PAD_DPAD_DOWN,
        VK_PAD_DPAD_LEFT,
        VK_PAD_DPAD_RIGHT
    };


    for (int i = 0; i < 14; i++)
    {
        if (xstate.Gamepad.wButtons & allButtonIDs[i])
        {
            if (flags[i] == NULL)
            {
                pKeystroke->VirtualKey = keyIDs[i];
                pKeystroke->Flags = flags[i] = XINPUT_KEYSTROKE_KEYDOWN;
                break;
            }
            if ((flags[i] & XINPUT_KEYSTROKE_KEYDOWN))
            {
                if (repeat[i] <= 0)
                {
                    repeat[i] = 5;
                    pKeystroke->VirtualKey = keyIDs[i];
                    pKeystroke->Flags = flags[i] = XINPUT_KEYSTROKE_KEYDOWN | XINPUT_KEYSTROKE_REPEAT;
                    break;
                }
                else
                {
                    repeat[i]--;
                    continue;
                }
            }
        }
        if (!(xstate.Gamepad.wButtons & allButtonIDs[i]))
        {
            if (flags[i] & XINPUT_KEYSTROKE_KEYDOWN)
            {
                repeat[i] = 5 * 4;
                pKeystroke->VirtualKey = keyIDs[i];
                pKeystroke->Flags = flags[i] = XINPUT_KEYSTROKE_KEYUP;
                break;
            }
            if (flags[i] & XINPUT_KEYSTROKE_KEYUP)
            {
                pKeystroke->Flags = flags[i] = NULL;
                break;
            }
        }
    }

    //PrintLog("ret: %u, flags: %u, hid: %u, unicode: %c, user: %u, vk: 0x%X",ret,pKeystroke->Flags,pKeystroke->HidCode,pKeystroke->Unicode,pKeystroke->UserIndex,pKeystroke->VirtualKey);

    if (pKeystroke->VirtualKey)
        return ERROR_SUCCESS;
    else
        return ERROR_EMPTY;

}