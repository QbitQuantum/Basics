/*
 * Initializes the haptic subsystem.
 */
int
SDL_SYS_HapticInit(void)
{
    const char *env = SDL_GetHint(SDL_HINT_XINPUT_ENABLED);
    HRESULT ret;
    HINSTANCE instance;

    if (dinput != NULL) {       /* Already open. */
        return SDL_SetError("Haptic: SubSystem already open.");
    }

    /* Clear all the memory. */
    SDL_memset(SDL_hapticlist, 0, sizeof(SDL_hapticlist));

    SDL_numhaptics = 0;

    ret = WIN_CoInitialize();
    if (FAILED(ret)) {
        return DI_SetError("Coinitialize", ret);
    }

    coinitialized = SDL_TRUE;

    ret = CoCreateInstance(&CLSID_DirectInput8, NULL, CLSCTX_INPROC_SERVER,
                           &IID_IDirectInput8, (LPVOID) & dinput);
    if (FAILED(ret)) {
        SDL_SYS_HapticQuit();
        return DI_SetError("CoCreateInstance", ret);
    }

    /* Because we used CoCreateInstance, we need to Initialize it, first. */
    instance = GetModuleHandle(NULL);
    if (instance == NULL) {
        SDL_SYS_HapticQuit();
        return SDL_SetError("GetModuleHandle() failed with error code %d.",
                            GetLastError());
    }
    ret = IDirectInput8_Initialize(dinput, instance, DIRECTINPUT_VERSION);
    if (FAILED(ret)) {
        SDL_SYS_HapticQuit();
        return DI_SetError("Initializing DirectInput device", ret);
    }

    /* Look for haptic devices. */
    ret = IDirectInput8_EnumDevices(dinput,
                                   0,
                                   EnumHapticsCallback,
                                   NULL,
                                   DIEDFL_FORCEFEEDBACK |
                                   DIEDFL_ATTACHEDONLY);
    if (FAILED(ret)) {
        SDL_SYS_HapticQuit();
        return DI_SetError("Enumerating DirectInput devices", ret);
    }

    if (!env || SDL_atoi(env)) {
        loaded_xinput = (WIN_LoadXInputDLL() == 0);
    }

    if (loaded_xinput) {
        DWORD i;
        const SDL_bool bIs14OrLater = (SDL_XInputVersion >= ((1<<16)|4));

        for (i = 0; (i < SDL_XINPUT_MAX_DEVICES) && (SDL_numhaptics < MAX_HAPTICS); i++) {
            XINPUT_CAPABILITIES caps;
            if (XINPUTGETCAPABILITIES(i, XINPUT_FLAG_GAMEPAD, &caps) == ERROR_SUCCESS) {
                if ((!bIs14OrLater) || (caps.Flags & XINPUT_CAPS_FFB_SUPPORTED)) {
                    /* !!! FIXME: I'm not bothering to query for a real name right now. */
                    char buf[64];
                    SDL_snprintf(buf, sizeof (buf), "XInput Controller #%u", i+1);
                    SDL_hapticlist[SDL_numhaptics].name = SDL_strdup(buf);
                    SDL_hapticlist[SDL_numhaptics].bXInputHaptic = 1;
                    SDL_hapticlist[SDL_numhaptics].userid = (Uint8) i;
                    SDL_numhaptics++;
                }
            }
        }
    }

    return SDL_numhaptics;
}