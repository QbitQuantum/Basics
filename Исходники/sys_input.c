/**
 * Initialize input.
 *
 * @return              @c true, if successful.
 */
boolean I_Init(void)
{
    HRESULT         hr;

    if(initIOk)
        return true; // Already initialized.

    if(ArgCheck("-nowsk")) // No Windows system keys?
    {
        // Disable Alt-Tab, Alt-Esc, Ctrl-Alt-Del.  A bit of a hack...
        SystemParametersInfo(SPI_SETSCREENSAVERRUNNING, TRUE, 0, 0);
        Con_Message("Windows system keys disabled.\n");
    }

    // We'll create the DirectInput object. The only required input device
    // is the keyboard. The others are optional.
    dInput = NULL;
    if(FAILED
       (hr =
        CoCreateInstance(&CLSID_DirectInput8, NULL, CLSCTX_INPROC_SERVER,
                         &IID_IDirectInput8, &dInput)) ||
       FAILED(hr =
              IDirectInput8_Initialize(dInput, app.hInstance, DIRECTINPUT_VERSION)))
    {
        Con_Message("I_Init: DirectInput 8 init failed (0x%x).\n", hr);
        // Try DInput3 instead.
        // I'm not sure if this works correctly.
        if(FAILED
           (hr =
            CoCreateInstance(&CLSID_DirectInput, NULL, CLSCTX_INPROC_SERVER,
                             &IID_IDirectInput2W, &dInput)) ||
           FAILED(hr = IDirectInput2_Initialize(dInput, app.hInstance, 0x0300)))
        {
            Con_Message
                ("I_Init: Failed to create DirectInput 3 object (0x%x).\n",
                 hr);
            return false;
        }
        Con_Message("I_Init: Using DirectInput 3.\n");
    }

    if(!dInput)
    {
        Con_Message("I_Init: DirectInput init failed.\n");
        return false;
    }

    if(!I_InitKeyboard())
        return false; // We must have a keyboard!

    // Acquire the keyboard.
    IDirectInputDevice_Acquire(didKeyb);

    // Create the mouse and joystick devices. It doesn't matter if the init
    // fails for them.
    I_InitMouse();
    I_InitJoystick();

    initIOk = true;

    return true;
}