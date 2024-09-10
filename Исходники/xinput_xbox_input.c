static void xinput_input_poll(void *data)
{
   (void)data;
   unsigned int dwInsertions, dwRemovals;
   
   XGetDeviceChanges(XDEVICE_TYPE_GAMEPAD, reinterpret_cast<PDWORD>(&dwInsertions), reinterpret_cast<PDWORD>(&dwRemovals));

   pads_connected = 0;

   for (unsigned i = 0; i < 4; i++)
   {
      XINPUT_STATE state[4];
      XINPUT_CAPABILITIES caps[4];
      (void)caps;
      real_state[i] = 0;
      // handle removed devices
      bRemoved[i] = (dwRemovals & (1<<i)) ? true : false;

      if(bRemoved[i])
      {
         // if the controller was removed after XGetDeviceChanges but before
         // XInputOpen, the device handle will be NULL
         if(gamepads[i])
            XInputClose(gamepads[i]);

          gamepads[i] = NULL;
      }

      // handle inserted devices
      bInserted[i] = (dwInsertions & (1<<i)) ? true : false;

      if(bInserted[i])
      {
         XINPUT_POLLING_PARAMETERS m_pollingParameters;
         m_pollingParameters.fAutoPoll = TRUE;
         m_pollingParameters.fInterruptOut = TRUE;
         m_pollingParameters.bInputInterval = 8;
         m_pollingParameters.bOutputInterval = 8;
         gamepads[i] = XInputOpen(XDEVICE_TYPE_GAMEPAD, i, XDEVICE_NO_SLOT, NULL);
      }
	  
      if (gamepads[i])
      {
         unsigned long retval;

         // if the controller is removed after XGetDeviceChanges but before
         // XInputOpen, the device handle will be NULL

         retval = XInputGetState(gamepads[i], &state[i]);
         if(retval == ERROR_SUCCESS)
         {
            pads_connected++;
            real_state[i] |= ((state[i].Gamepad.bAnalogButtons[XINPUT_GAMEPAD_B]) ? XINPUT1_GAMEPAD_B : 0);
            real_state[i] |= ((state[i].Gamepad.bAnalogButtons[XINPUT_GAMEPAD_A]) ? XINPUT1_GAMEPAD_A : 0);
            real_state[i] |= ((state[i].Gamepad.bAnalogButtons[XINPUT_GAMEPAD_Y]) ? XINPUT1_GAMEPAD_Y : 0);
            real_state[i] |= ((state[i].Gamepad.bAnalogButtons[XINPUT_GAMEPAD_X]) ? XINPUT1_GAMEPAD_X : 0);
            real_state[i] |= ((state[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) || (state[i].Gamepad.sThumbLX < -DEADZONE) ? XINPUT1_GAMEPAD_DPAD_LEFT : 0);
            real_state[i] |= ((state[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) || (state[i].Gamepad.sThumbLX > DEADZONE) ? XINPUT1_GAMEPAD_DPAD_RIGHT : 0);
            real_state[i] |= ((state[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) || (state[i].Gamepad.sThumbLY > DEADZONE) ? XINPUT1_GAMEPAD_DPAD_UP : 0);
            real_state[i] |= ((state[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)|| (state[i].Gamepad.sThumbLY < -DEADZONE) ? XINPUT1_GAMEPAD_DPAD_DOWN : 0);
            real_state[i] |= ((state[i].Gamepad.wButtons & XINPUT_GAMEPAD_START) ? XINPUT1_GAMEPAD_START : 0);
            real_state[i] |= ((state[i].Gamepad.wButtons & XINPUT_GAMEPAD_BACK) ? XINPUT1_GAMEPAD_BACK : 0);
            real_state[i] |= ((state[i].Gamepad.bAnalogButtons[XINPUT_GAMEPAD_LEFT_TRIGGER]) ? XINPUT1_GAMEPAD_LEFT_TRIGGER : 0);
            real_state[i] |= ((state[i].Gamepad.bAnalogButtons[XINPUT_GAMEPAD_RIGHT_TRIGGER]) ? XINPUT1_GAMEPAD_RIGHT_TRIGGER : 0);
            real_state[i] |= ((state[i].Gamepad.bAnalogButtons[XINPUT_GAMEPAD_WHITE]) ? XINPUT1_GAMEPAD_WHITE : 0);
            real_state[i] |= ((state[i].Gamepad.bAnalogButtons[XINPUT_GAMEPAD_BLACK]) ? XINPUT1_GAMEPAD_BLACK : 0);
            real_state[i] |= ((state[i].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? XINPUT1_GAMEPAD_LEFT_THUMB : 0);
            real_state[i] |= ((state[i].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? XINPUT1_GAMEPAD_RIGHT_THUMB : 0);
         }
      }
   }
}