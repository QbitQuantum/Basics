bool
InputEvents::ProcessKey(Mode mode, unsigned key_code)
{
  if (IsAltair() && key_code == 0xF5) {
    UIActions::SignalShutdown(false);
    return true;
  }

  if (!global_running)
    return false;

#ifdef KOBO
#ifdef ENABLE_SDL
  if (key_code == SDLK_POWER)
    /* the Kobo power button opens the main menu */
    key_code = KEY_MENU;
#else
  // TODO: check the console key code
#endif
#endif

  // Which key - can be defined locally or at default (fall back to default)
  unsigned event_id = key_to_event(mode, overlay_mode, key_code);
  if (event_id == 0)
    return false;

  ProcessEvent(event_id);
  return true;
}