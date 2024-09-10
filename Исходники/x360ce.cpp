extern "C" DWORD WINAPI XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, XINPUT_KEYSTROKE* pKeystroke)
{
    if(g_bDisable) return ERROR_DEVICE_NOT_CONNECTED;

    if((dwUserIndex+1 > g_Devices.size() || g_Devices[dwUserIndex].passthrough) && XInputInitialize())
    {
        //PrintLog("flags: %u, hidcode: %u, unicode: %c, user: %u, vk: 0x%X",pKeystroke->Flags,pKeystroke->HidCode,pKeystroke->Unicode,pKeystroke->UserIndex,pKeystroke->VirtualKey);
		return xinput.XInputGetKeystroke(dwUserIndex, dwReserved, pKeystroke);
    }

    if (!pKeystroke || !(dwUserIndex < XUSER_MAX_COUNT)) return ERROR_BAD_ARGUMENTS;

    DInputDevice& device = g_Devices[dwUserIndex];

    if(hMsgWnd == NULL) CreateMsgWnd();

    if(device.device == NULL && device.dwUserIndex == dwUserIndex)
        DeviceInitialize(device);
    if(!device.device) return ERROR_DEVICE_NOT_CONNECTED;

    XINPUT_KEYSTROKE& xkey = *pKeystroke;

    XINPUT_STATE xstate;
    ZeroMemory(&xstate,sizeof(XINPUT_STATE));
    XInputGetState(dwUserIndex,&xstate);

    static WORD repeat[14];
    static WORD flags[14];

    WORD vkey = NULL;
    WORD curretFlags = NULL;

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

    static const uint16_t keyIDs[14] =
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

    for(int i = 0; i < 14; i++)
    {
        if(xstate.Gamepad.wButtons & allButtonIDs[i])
        {
            if(flags[i] == NULL)
            {
                vkey = keyIDs[i];
                curretFlags = flags[i] = XINPUT_KEYSTROKE_KEYDOWN;
                break;
            }
            if((flags[i] & XINPUT_KEYSTROKE_KEYDOWN))
            {
                if(repeat[i] <= 0)
                {
                    repeat[i] = 5;
                    vkey = keyIDs[i];
                    curretFlags = flags[i] = XINPUT_KEYSTROKE_KEYDOWN | XINPUT_KEYSTROKE_REPEAT;
                    break;
                }
                else
                {
                    repeat[i]--;
                    continue;
                }
            }
        }
        if(!(xstate.Gamepad.wButtons & allButtonIDs[i]))
        {
            if(flags[i] & XINPUT_KEYSTROKE_KEYDOWN)
            {
                repeat[i] = 5*4;
                vkey = keyIDs[i];
                curretFlags = flags[i] = XINPUT_KEYSTROKE_KEYUP;
                break;
            }
            if(flags[i] & XINPUT_KEYSTROKE_KEYUP)
            {
                curretFlags = flags[i] = NULL;
                break;
            }
        }
    }

    DWORD ret = ERROR_EMPTY;

    if(vkey)
    {
        xkey.UserIndex = (BYTE)dwUserIndex;
        xkey.Unicode = NULL;
        xkey.HidCode = NULL;
        xkey.Flags = curretFlags;
        xkey.VirtualKey = vkey;
        ret = ERROR_SUCCESS;
    }

    //PrintLog("ret: %u, flags: %u, hid: %u, unicode: %c, user: %u, vk: 0x%X",ret,pKeystroke->Flags,pKeystroke->HidCode,pKeystroke->Unicode,pKeystroke->UserIndex,pKeystroke->VirtualKey);

    return ret;
}