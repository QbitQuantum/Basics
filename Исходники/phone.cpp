/*****************************************************************************
** Procedure:  CDSPhone::UnsolicitedEvent
**
** Arguments: 'lpBuff'    - Data buffer (structure) specific to code
**
** Returns:    void
**
** Description:  This function processes any responses from the device which
**               are not matched to a pending line request.
**
*****************************************************************************/
bool CDSPhone::UnsolicitedEvent(LPCVOID lpBuff)
{             
	USES_CONVERSION;
	EVENTBUFF* pevBuff = (EVENTBUFF*) lpBuff;

    switch (pevBuff->dwResponse)
    {
        // A lamp has changed states.
        case EMRESULT_LAMPCHANGED:        
        {
            LPEMLAMPCHANGE lpChange = (LPEMLAMPCHANGE) pevBuff->lpBuff;
            SetLampState ((int)lpChange->wButtonLampID, g_LampStates[lpChange->wLampState]);
        }                                        
        break;
        
        // A hookswitch device has changed states.
        case EMRESULT_HSCHANGED:
        {
            LPEMHOOKSWITCHCHANGE lpChange = (LPEMHOOKSWITCHCHANGE) pevBuff->lpBuff;
            _TSP_ASSERTE (lpChange->wHookswitchID == HSDEVICE_HANDSET);
            SetHookSwitch (PHONEHOOKSWITCHDEV_HANDSET, g_hsStates[lpChange->wHookswitchState]);
        }
        break;

        // A button has changed
        case EMRESULT_BUTTONCHANGED:
        {
            LPEMBUTTONCHANGE lpChange = (LPEMBUTTONCHANGE) pevBuff->lpBuff;
            SetButtonState (lpChange->wButtonLampID, g_ButtonStates[lpChange->wButtonState]);
        }                    
        break;
        
        // Ringer mode changed
        case EMRESULT_RINGCHANGE:
            SetRingMode (*((LPDWORD)pevBuff->lpBuff));
            break;
        
        // Volume/Gain of the handset changed
        case EMRESULT_LEVELCHANGED:
        {
            LPEMLEVELCHANGE lpChange = (LPEMLEVELCHANGE) pevBuff->lpBuff;
            if (lpChange->wLevelType == LEVELTYPE_MIC)
                SetGain (PHONEHOOKSWITCHDEV_HANDSET, lpChange->wLevel);
            else if (lpChange->wLevelType == LEVELTYPE_SPEAKER)
                SetVolume (PHONEHOOKSWITCHDEV_HANDSET, lpChange->wLevel);
        }
        break;                        
        
        // The display has changed.
        case EMRESULT_DISPLAYCHANGED:
        {
            LPEMDISPLAY lpChange = (LPEMDISPLAY) pevBuff->lpBuff;
            SetDisplay (A2T(lpChange->szDisplay));
        }        
        break;
    }

	return true;

}// CDSPhone::UnsolicitedEvent