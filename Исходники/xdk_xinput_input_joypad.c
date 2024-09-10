static void xdk_joypad_poll(void)
{
   uint64_t *state_p1, *lifecycle_state;
   unsigned port;
#if defined(_XBOX1)
   unsigned int dwInsertions, dwRemovals;

   XGetDeviceChanges(XDEVICE_TYPE_GAMEPAD,
         reinterpret_cast<PDWORD>(&dwInsertions),
         reinterpret_cast<PDWORD>(&dwRemovals));
#endif

   for (port = 0; port < MAX_PADS; port++)
   {
#ifdef _XBOX1
      XINPUT_CAPABILITIES caps[MAX_PADS];
      (void)caps;

      /* handle removed devices. */
      bRemoved[port] = (dwRemovals & (1 << port)) ? true : false;

      if(bRemoved[port])
      {
         /* if the controller was removed after 
          * XGetDeviceChanges but before
          * XInputOpen, the device handle will be NULL. */
         if(gamepads[port])
            XInputClose(gamepads[port]);

         gamepads[port] = 0;
         pad_state[port] = 0;
      }

      /* handle inserted devices. */
      bInserted[port] = (dwInsertions & (1 << port)) ? true : false;

      if(bInserted[port])
      {
         XINPUT_POLLING_PARAMETERS m_pollingParameters;
         m_pollingParameters.fAutoPoll = FALSE;
         m_pollingParameters.fInterruptOut = TRUE;
         m_pollingParameters.bInputInterval = 8;
         m_pollingParameters.bOutputInterval = 8;
         gamepads[port] = XInputOpen(XDEVICE_TYPE_GAMEPAD, port,
               XDEVICE_NO_SLOT, NULL);
      }

      if (!gamepads[port])
         continue;

      /* if the controller is removed after 
       * XGetDeviceChanges but before XInputOpen,
       * the device handle will be NULL. */
#endif

      XINPUT_STATE state_tmp;

#if defined(_XBOX1)
      if (XInputPoll(gamepads[port]) != ERROR_SUCCESS)
         continue;

      if (XInputGetState(gamepads[port], &state_tmp) != ERROR_SUCCESS)
         continue;
#elif defined(_XBOX360)
      if (XInputGetState(port, &state_tmp) == ERROR_DEVICE_NOT_CONNECTED)
         continue;
#endif

      uint64_t *state_cur = &pad_state[port];

      *state_cur = 0;
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_LEFT) : 0);
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_RIGHT) : 0);
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_UP) : 0);
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_DOWN) : 0);
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_START) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_START) : 0);
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_SELECT) : 0);

#if defined(_XBOX1)
      *state_cur |= ((state_tmp.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_B]) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_A) : 0);
      *state_cur |= ((state_tmp.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_A]) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_B) : 0);
      *state_cur |= ((state_tmp.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_Y]) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_X) : 0);
      *state_cur |= ((state_tmp.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_X]) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_Y) : 0);
      *state_cur |= ((state_tmp.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_LEFT_TRIGGER]) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_L) : 0);
      *state_cur |= ((state_tmp.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_RIGHT_TRIGGER]) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_R) : 0);
      *state_cur |= ((state_tmp.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_WHITE]) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_L2) : 0);
      *state_cur |= ((state_tmp.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_BLACK]) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_R2) : 0);
#elif defined(_XBOX360)
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_B) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_A) : 0);
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_A) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_B) : 0);
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_Y) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_X) : 0);
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_X) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_Y) : 0);
      *state_cur |= ((state_tmp.Gamepad.bLeftTrigger > 128) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_L) : 0);
      *state_cur |= ((state_tmp.Gamepad.bRightTrigger > 128) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_R) : 0);
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_L2) : 0);
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_R2) : 0);
#endif
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_L3) : 0);
      *state_cur |= ((state_tmp.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? (1ULL << RETRO_DEVICE_ID_JOYPAD_R3) : 0);

      analog_state[port][RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_X] = state_tmp.Gamepad.sThumbLX;
      analog_state[port][RETRO_DEVICE_INDEX_ANALOG_LEFT][RETRO_DEVICE_ID_ANALOG_Y] = state_tmp.Gamepad.sThumbLY;
      analog_state[port][RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_X] = state_tmp.Gamepad.sThumbRX;
      analog_state[port][RETRO_DEVICE_INDEX_ANALOG_RIGHT][RETRO_DEVICE_ID_ANALOG_Y] = state_tmp.Gamepad.sThumbRY;

      for (int i = 0; i < 2; i++)
         for (int j = 0; j < 2; j++)
            if (analog_state[port][i][j] == -0x8000)
               analog_state[port][i][j] = -0x7fff;
   }

   state_p1 = &pad_state[0];
   lifecycle_state = &g_extern.lifecycle_state;

   *lifecycle_state &= ~((1ULL << RARCH_MENU_TOGGLE));

   if((*state_p1 & (1ULL << RETRO_DEVICE_ID_JOYPAD_L3)) && (*state_p1 & (1ULL << RETRO_DEVICE_ID_JOYPAD_R3)))
      *lifecycle_state |= (1ULL << RARCH_MENU_TOGGLE);
}