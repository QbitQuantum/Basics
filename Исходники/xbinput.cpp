//-----------------------------------------------------------------------------
// Name: XBInput_GetInput()
// Desc: Processes input from the gamepads
//-----------------------------------------------------------------------------
VOID XBInput_GetInput( XBGAMEPAD* pGamepads )
{
    if( NULL == pGamepads )
        pGamepads = g_Gamepads;

    // TCR 3-21 Controller Discovery
    // Get status about gamepad insertions and removals. Note that, in order to
    // not miss devices, we will check for removed device BEFORE checking for
    // insertions
    DWORD dwInsertions, dwRemovals;
    XGetDeviceChanges( XDEVICE_TYPE_GAMEPAD, &dwInsertions, &dwRemovals );

    // Loop through all gamepads
    for( DWORD i=0; i < XGetPortCount(); i++ )
    {
        // Handle removed devices.
        pGamepads[i].bRemoved = ( dwRemovals & (1<<i) ) ? TRUE : FALSE;
        if( pGamepads[i].bRemoved )
        {
            // if the controller was removed after XGetDeviceChanges but before
            // XInputOpen, the device handle will be NULL
            if( pGamepads[i].hDevice )
                XInputClose( pGamepads[i].hDevice );
            pGamepads[i].hDevice = NULL;
            pGamepads[i].Feedback.Rumble.wLeftMotorSpeed  = 0;
            pGamepads[i].Feedback.Rumble.wRightMotorSpeed = 0;
        }

        // Handle inserted devices
        pGamepads[i].bInserted = ( dwInsertions & (1<<i) ) ? TRUE : FALSE;
        if( pGamepads[i].bInserted ) 
        {
            // TCR 1-14 Device Types
            pGamepads[i].hDevice = XInputOpen( XDEVICE_TYPE_GAMEPAD, i, 
                                               XDEVICE_NO_SLOT, NULL );

            // if the controller is removed after XGetDeviceChanges but before
            // XInputOpen, the device handle will be NULL
            if( pGamepads[i].hDevice )
                XInputGetCapabilities( pGamepads[i].hDevice, &pGamepads[i].caps );
        }

        // If we have a valid device, poll it's state and track button changes
        if( pGamepads[i].hDevice )
        {
            // Read the input state
            XInputGetState( pGamepads[i].hDevice, &g_InputStates[i] );

            // Copy gamepad to local structure
            memcpy( &pGamepads[i], &g_InputStates[i].Gamepad, sizeof(XINPUT_GAMEPAD) );

            // Put Xbox device input for the gamepad into our custom format
            FLOAT fX1 = (pGamepads[i].sThumbLX+0.5f)/32767.5f;
            pGamepads[i].fX1 = ( fX1 >= 0.0f ? 1.0f : -1.0f ) *
                               max( 0.0f, (fabsf(fX1)-XBINPUT_DEADZONE)/(1.0f-XBINPUT_DEADZONE) );

            FLOAT fY1 = (pGamepads[i].sThumbLY+0.5f)/32767.5f;
            pGamepads[i].fY1 = ( fY1 >= 0.0f ? 1.0f : -1.0f ) *
                               max( 0.0f, (fabsf(fY1)-XBINPUT_DEADZONE)/(1.0f-XBINPUT_DEADZONE) );

            FLOAT fX2 = (pGamepads[i].sThumbRX+0.5f)/32767.5f;
            pGamepads[i].fX2 = ( fX2 >= 0.0f ? 1.0f : -1.0f ) *
                               max( 0.0f, (fabsf(fX2)-XBINPUT_DEADZONE)/(1.0f-XBINPUT_DEADZONE) );

            FLOAT fY2 = (pGamepads[i].sThumbRY+0.5f)/32767.5f;
            pGamepads[i].fY2 = ( fY2 >= 0.0f ? 1.0f : -1.0f ) *
                               max( 0.0f, (fabsf(fY2)-XBINPUT_DEADZONE)/(1.0f-XBINPUT_DEADZONE) );

            // Get the boolean buttons that have been pressed since the last
            // call. Each button is represented by one bit.
            pGamepads[i].wPressedButtons = ( pGamepads[i].wLastButtons ^ pGamepads[i].wButtons ) & pGamepads[i].wButtons;
            pGamepads[i].wLastButtons    = pGamepads[i].wButtons;

            // Get the analog buttons that have been pressed or released since
            // the last call.
            for( DWORD b=0; b<8; b++ )
            {
                // Turn the 8-bit polled value into a boolean value
                BOOL bPressed = ( pGamepads[i].bAnalogButtons[b] > XINPUT_GAMEPAD_MAX_CROSSTALK );

                if( bPressed )
                    pGamepads[i].bPressedAnalogButtons[b] = !pGamepads[i].bLastAnalogButtons[b];
                else
                    pGamepads[i].bPressedAnalogButtons[b] = FALSE;
                
                // Store the current state for the next time
                pGamepads[i].bLastAnalogButtons[b] = bPressed;
            }
        }
    }
}