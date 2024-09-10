    HRESULT InitDirectInput(unsigned int joystick_index)
    {
        HRESULT hr;

        state.is_initialized = false;

        // Register with the DirectInput subsystem and get a pointer
        // to a IDirectInput interface we can use.
        // Create a DInput object
        if (FAILED(hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION,
            IID_IDirectInput8, (VOID**)&g_pDI, nullptr)))
            return hr;


        if (g_bFilterOutXinputDevices)
            SetupForIsXInputDevice();

        enumContext.pPreferredJoyCfg = &PreferredJoyCfg;
        enumContext.bPreferredJoyCfgValid = false;

        IDirectInputJoyConfig8* pJoyConfig = nullptr;
        if (FAILED(hr = g_pDI->QueryInterface(IID_IDirectInputJoyConfig8, (void**)&pJoyConfig))) {
            state.message = "QueryInterface on IID_IDirectInputJoyConfig8 failed";
            return hr;
        }

        PreferredJoyCfg.dwSize = sizeof(PreferredJoyCfg);
        if (SUCCEEDED(pJoyConfig->GetConfig(joystick_index, &PreferredJoyCfg, DIJC_GUIDINSTANCE))) { // This function is expected to fail if no joystick is attached
            enumContext.bPreferredJoyCfgValid = true;

            joystick_info.is_valid = true;
            joystick_info.instance_guide = toDIGUID(PreferredJoyCfg.guidInstance);
            joystick_info.pid_vid = toString(PreferredJoyCfg.wszType);
        }
        DIJT_SAFE_RELEASE(pJoyConfig);

        // Look for a simple joystick we can use for this sample program.
        if (FAILED(hr = g_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL,
            DirectInputJoyStick::impl::EnumJoysticksCallback,
            this, DIEDFL_ATTACHEDONLY))) {

            state.message = "EnumDevices failed";
            return hr;
        }

        if (g_bFilterOutXinputDevices)
            CleanupForIsXInputDevice();

        // Make sure we got a joystick
        if (!g_pJoystick)
        {
            state.message = "Joystick at index " + std::to_string(joystick_index) + " is not available";
            return S_FALSE;
        }

        // Set the data format to "simple joystick" - a predefined data format 
        //
        // A data format specifies which controls on a device we are interested in,
        // and how they should be reported. This tells DInput that we will be
        // passing a DIJOYSTATE2 structure to IDirectInputDevice::GetDeviceState().
        if (FAILED(hr = g_pJoystick->SetDataFormat(&c_dfDIJoystick2)))
        {
            state.message = "Device does not support DIJOYSTATE2";
            return hr;
        }

        // Set the cooperative level to let DInput know how this device should
        // interact with the system and with other DInput applications.
        if (FAILED(hr = g_pJoystick->SetCooperativeLevel(NULL, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND))) {

            state.message = "SetCooperativeLevel failed";
            return hr;
        }

        // Enumerate the joystick objects. The callback function enabled user
        // interface elements for objects that are found, and sets the min/max
        // values property for discovered axes.
        if (FAILED(hr = g_pJoystick->EnumObjects(DirectInputJoyStick::impl::EnumObjectsCallback,
            (VOID*) this, DIDFT_ALL))) {

            state.message = "EnumObjects failed";
            return hr;
        }

        InitForceFeedback();

        state.is_initialized = true;
        return S_OK;
    }