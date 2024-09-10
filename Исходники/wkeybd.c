/* key_dinput_acquire: [window thread]
 *  Acquires the keyboard device. This must be called after a
 *  window switch for example if the device is in foreground
 *  cooperative level.
 */
int key_dinput_acquire(void)
{
   HRESULT hr;
   int mask, state;
   char key_state[256];

   if (key_dinput_device) {
      mask = KB_SCROLOCK_FLAG | KB_NUMLOCK_FLAG | KB_CAPSLOCK_FLAG;
      state = 0;

      /* Read the current Windows keyboard state */
      GetKeyboardState(key_state);

      if (key_state[VK_SCROLL] & 1)
         state |= KB_SCROLOCK_FLAG;

      if (key_state[VK_NUMLOCK] & 1)
         state |= KB_NUMLOCK_FLAG;

      if (key_state[VK_CAPITAL] & 1)
         state |= KB_CAPSLOCK_FLAG;

      _key_shifts = (_key_shifts & ~mask) | (state & mask);

      hr = IDirectInputDevice_Acquire(key_dinput_device);

      if (FAILED(hr)) {
         _TRACE(PREFIX_E "acquire keyboard failed: %s\n", dinput_err_str(hr));
         return -1;
      }

      /* Initialize keyboard state */
      SetEvent(key_input_event);

      return 0;
   }
   else
      return -1;
}