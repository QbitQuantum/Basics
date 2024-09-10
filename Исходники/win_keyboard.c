PUBLIC void
ROMlib_set_caps_lock_off (void)
{
  if (GetKeyState (VK_CAPITAL) & 1)
    {
      char state[256];

      GetKeyboardState (state);
      state[VK_CAPITAL] = 0;
      SetKeyboardState (state);
    }
}