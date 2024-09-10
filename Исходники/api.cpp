void OBSAPIInterface::HandleHotkeys()
{
    List<DWORD> hitKeys;

    static bool allow_other_hotkey_modifiers;
    static bool uplay_overlay_compatibility;
    static bool set_vars = false;

    /* only query these config variables once */
    if (!set_vars)
    {
        allow_other_hotkey_modifiers = !!GlobalConfig->GetInt(TEXT("General"), TEXT("AllowOtherHotkeyModifiers"), true);
        uplay_overlay_compatibility = !!GlobalConfig->GetInt(L"General", L"UplayOverlayCompatibility", false);
        set_vars = true;
    }

    DWORD modifiers = 0;
    if(GetAsyncKeyState(VK_MENU) & 0x8000)
        modifiers |= HOTKEYF_ALT;
    if(GetAsyncKeyState(VK_CONTROL) & 0x8000)
        modifiers |= HOTKEYF_CONTROL;
    if (!uplay_overlay_compatibility)
        if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
            modifiers |= HOTKEYF_SHIFT;

    OSEnterMutex(App->hHotkeyMutex);

    for(UINT i=0; i<hotkeys.Num(); i++)
    {
        HotkeyInfo &info = hotkeys[i];

        DWORD hotkeyVK          = LOBYTE(info.hotkey);
        DWORD hotkeyModifiers   = HIBYTE(info.hotkey);
        DWORD xinputNum         = LOWORD(info.hotkey);
        DWORD xinputButton      = HIWORD(info.hotkey);

        hotkeyModifiers &= ~(HOTKEYF_EXT);

        if(xinputButton)
        {
            XINPUT_STATE state = { 0 };

            if(XInputGetState(xinputNum, &state) == ERROR_SUCCESS)
            {
                if(state.Gamepad.bLeftTrigger >= 85)
                    state.Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_TRIGGER;

                if(state.Gamepad.bRightTrigger >= 85)
                    state.Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_TRIGGER;

                if((state.Gamepad.wButtons & xinputButton) != 0 && !info.bHotkeyDown)
                {
                    PostMessage(hwndMain, OBS_CALLHOTKEY, TRUE, info.hotkeyID);
                    info.bDownSent = true;
                    info.bHotkeyDown = true;
                }
            }

            info.bModifiersDown = 0;
        }
        else
        {
            bool bModifiersMatch = false;
            if(allow_other_hotkey_modifiers)
                bModifiersMatch = ((hotkeyModifiers & modifiers) == hotkeyModifiers); //allows other modifiers to be pressed
            else
                bModifiersMatch = (hotkeyModifiers == modifiers);

            if(hotkeyModifiers && !hotkeyVK) //modifier-only hotkey
            {
                if((hotkeyModifiers & modifiers) == hotkeyModifiers)
                {
                    if(!info.bHotkeyDown)
                    {
                        PostMessage(hwndMain, OBS_CALLHOTKEY, TRUE, info.hotkeyID);
                        info.bDownSent = true;
                        info.bHotkeyDown = true;
                    }

                    continue;
                }
            }
            else
            {
                if (bModifiersMatch && !(uplay_overlay_compatibility && hotkeyVK == VK_F2))
                {
                    short keyState = GetAsyncKeyState(hotkeyVK);
                    bool bDown = (keyState & 0x8000) != 0;
                    bool bWasPressed = (keyState & 0x1) != 0;

                    if(bDown || bWasPressed)
                    {
                        if(!info.bHotkeyDown && info.bModifiersDown) //only triggers the hotkey if the actual main key was pressed second
                        {
                            PostMessage(hwndMain, OBS_CALLHOTKEY, TRUE, info.hotkeyID);
                            info.bDownSent = true;
                        }

                        info.bHotkeyDown = true;
                        if(bDown)
                            continue;
                    }
                }
            }

            info.bModifiersDown = bModifiersMatch;
        }

        if(info.bHotkeyDown) //key up
        {
            if(info.bDownSent)
            {
                PostMessage(hwndMain, OBS_CALLHOTKEY, FALSE, info.hotkeyID);
                info.bDownSent = false;
            }

            info.bHotkeyDown = false;
        }
    }

    OSLeaveMutex(App->hHotkeyMutex);
}