void PsychHIDInitializeHIDStandardInterfaces(void)
{
    int i;
    HRESULT rc;
    HINSTANCE modulehandle = NULL;
    dinput = NULL;
    ndevices = 0;

    // Init x_dev array:
    for (i = 0; i < PSYCH_HID_MAX_DEVICES; i++) x_dev[i] = NULL;

    // Init keyboard queue arrays:
    memset(&psychHIDKbQueueFirstPress[0], 0, sizeof(psychHIDKbQueueFirstPress));
    memset(&psychHIDKbQueueFirstRelease[0], 0, sizeof(psychHIDKbQueueFirstRelease));
    memset(&psychHIDKbQueueLastPress[0], 0, sizeof(psychHIDKbQueueLastPress));
    memset(&psychHIDKbQueueLastRelease[0], 0, sizeof(psychHIDKbQueueLastRelease));
    memset(&psychHIDKbQueueActive[0], 0, sizeof(psychHIDKbQueueActive));
    memset(&psychHIDKbQueueScanKeys[0], 0, sizeof(psychHIDKbQueueScanKeys));

    // We need the module instance handle of ourselves, ie., the PsychHID mex file to
    // open a DirectInput-8 interface, so the OS can apply backwards compatibility fixes
    // specific to the way our mex file DLL was built. For this we need the name of the
    // mex file, which is dependent on Octave vs. Matlab and 32-Bit vs. 64-Bit:
#ifndef PTBOCTAVE3MEX
    // Matlab: 64-Bit or 32-Bit mex file?
#if defined(__LP64__) || defined(_M_IA64) || defined(_WIN64)
    // 64-Bit:
    modulehandle = GetModuleHandle("PsychHID.mexw64");
#else
    // 32-Bit:
    modulehandle = GetModuleHandle("PsychHID.mexw32");
#endif
#else
    // Octave: Same mex file file-extension for 32/64-Bit:
    modulehandle = GetModuleHandle("PsychHID.mex");
#endif

    // If this doesn't work, try with application module handle as fallback. This works usually on
    // Windows XP/Vista/7, but may fail catastrophically on Windows-8 and later:
    if (NULL == modulehandle) {
        printf("PsychHID-WARNING: Could not get module handle to PsychHID mex file. Did you rename it? Please don't do that!\n");
        printf("PsychHID-WARNING: Will try application module handle as fallback. This may end badly, e.g., with a crash. Cross your fingers!\n");
        modulehandle = GetModuleHandle(NULL);
    }

    if (NULL == modulehandle) PsychErrorExitMsg(PsychError_system, "PsychHID: FATAL ERROR: Couldn't get module handle to create interface to Microsoft DirectInput-8! Game over!");

    // Open a DirectInput-8 interface:
    rc = DirectInput8Create(modulehandle, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&dinput, NULL);

    if (DI_OK != rc) {
        printf("PsychHID-ERROR: Error return from DirectInput8Create: %x\n", (int) rc);
        if (rc == DIERR_OLDDIRECTINPUTVERSION) printf("PsychHID-ERROR: You need to install a more recent version of DirectX -- at least DirectX-8.\n");
        PsychErrorExitMsg(PsychError_system, "PsychHID: FATAL ERROR: Couldn't create interface to Microsoft DirectInput-8! Game over!");
    }

    // Enumerate all DirectInput keyboard(-like) devices:
    rc = dinput->EnumDevices(DI8DEVCLASS_KEYBOARD, (LPDIENUMDEVICESCALLBACK) keyboardEnumCallback, NULL, DIEDFL_ATTACHEDONLY | DIEDFL_INCLUDEHIDDEN);
    if (DI_OK != rc) {
        printf("PsychHID-ERROR: Error return from DirectInput8 EnumDevices(): %x! Game over!\n", (int) rc);
        goto out;
    }

    // Enumerate all DirectInput mouse(-like) devices:
    rc = dinput->EnumDevices(DI8DEVCLASS_POINTER, (LPDIENUMDEVICESCALLBACK) keyboardEnumCallback, NULL, DIEDFL_ATTACHEDONLY | DIEDFL_INCLUDEHIDDEN);
    if (DI_OK != rc) {
        printf("PsychHID-ERROR: Error return from DirectInput8 EnumDevices(): %x! Game over!\n", (int) rc);
        goto out;
    }

    // Enumerate all DirectInput joystick/gamepad(-like) devices:
    rc = dinput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK) keyboardEnumCallback, NULL, DIEDFL_ATTACHEDONLY | DIEDFL_INCLUDEHIDDEN);
    if (DI_OK != rc) {
        printf("PsychHID-ERROR: Error return from DirectInput8 EnumDevices(): %x! Game over!\n", (int) rc);
        goto out;
    }

    // Create keyboard queue mutex for later use:
    KbQueueThreadTerminate = FALSE;
    PsychInitMutex(&KbQueueMutex);
    PsychInitCondition(&KbQueueCondition, NULL);

    // Create event object for signalling device state changes:
    hEvent = CreateEvent(   NULL,	// default security attributes
                            FALSE,	// auto-reset event: This would need to be set TRUE for PsychBroadcastCondition() to work on Windows!
                            FALSE,	// initial state is nonsignaled
                            NULL	// no object name
                        );

    // Ready.
    return;

out:
    ndevices = 0;

    // Close our dedicated x-display connection and we are done:
    if (dinput) dinput->Release();
    dinput = NULL;

    PsychErrorExitMsg(PsychError_system, "PsychHID: FATAL ERROR: X Input extension version 2.0 or later not available! Game over!");
}