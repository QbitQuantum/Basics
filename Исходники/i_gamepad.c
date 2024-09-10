void I_InitGamepad(void)
{
    gamepadfunc = I_PollDirectInputGamepad;
    gamepadthumbsfunc = (gp_swapthumbsticks ? I_PollThumbs_DirectInput_LeftHanded :
        I_PollThumbs_DirectInput_RightHanded);

    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0)
        return;
    else
    {
        int     i;
        int     numgamepads = SDL_NumJoysticks();

        for (i = 0; i < numgamepads; ++i)
        {
            gamepad = SDL_JoystickOpen(i);
            if (gamepad)
                break;
        }

        if (!gamepad)
        {
            SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
            return;
        }
        else
        {
#if defined(WIN32)
            char        *XInputDLL = malloc(16);
            static int  initcount;

            if ((pXInputDLL = LoadLibrary("XInput1_4.dll")))
                M_StringCopy(XInputDLL, "XINPUT1_4.DLL", 16);
            else if ((pXInputDLL = LoadLibrary("XInput9_1_0.dll")))
                M_StringCopy(XInputDLL, "XINPUT9_1_0.DLL", 16);
            else if ((pXInputDLL = LoadLibrary("XInput1_3.dll")))
                M_StringCopy(XInputDLL, "XINPUT1_3.DLL", 16);

            ++initcount;

            if (pXInputDLL)
            {
                pXInputGetState = (XINPUTGETSTATE)GetProcAddress(pXInputDLL, "XInputGetState");
                pXInputSetState = (XINPUTSETSTATE)GetProcAddress(pXInputDLL, "XInputSetState");

                if (pXInputGetState && pXInputSetState)
                {
                    XINPUT_STATE        state;

                    ZeroMemory(&state, sizeof(XINPUT_STATE));

                    if (pXInputGetState(0, &state) == ERROR_SUCCESS)
                    {
                        gamepadfunc = I_PollXInputGamepad;
                        gamepadthumbsfunc = (gp_swapthumbsticks ? I_PollThumbs_XInput_LeftHanded :
                            I_PollThumbs_XInput_RightHanded);
                        if (initcount == 1)
                            C_Output("XInput gamepad detected. Using %s.", XInputDLL);
                    }
                }
                else
                    FreeLibrary(pXInputDLL);
            }
            else if (initcount == 1)
                C_Output("DirectInput gamepad \"%s\" detected.", SDL_JoystickName(gamepad));

            free(XInputDLL);
#else
            C_Output("DirectInput gamepad \"%s\" detected.", SDL_JoystickName(gamepad));
#endif

            SDL_JoystickEventState(SDL_ENABLE);
        }
    }
}