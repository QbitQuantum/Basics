/* _al_win_kbd_handle_key_press:
 *  Does stuff when a key is pressed.
 */
void _al_win_kbd_handle_key_press(int scode, int vcode, bool extended,
                           bool repeated, ALLEGRO_DISPLAY_WIN *win_disp)
{
   ALLEGRO_DISPLAY *display = (ALLEGRO_DISPLAY *)win_disp;
   ALLEGRO_EVENT event;
   int my_code;
   bool actual_repeat;
   int char_count;
   int event_count;
   int i;
   BYTE ks[256];
   WCHAR buf[8] = { 0 };

   if (!installed)
      return;

   /* Check for an extended key first. */
   my_code = 0;
   if (extended)
      my_code = extkey_to_keycode(vcode);

   /* Map a non-extended key.  This also works as a fallback in case
      the key was extended, but no extended mapping was found. */
   if (my_code == 0) {
      if (vcode == VK_SHIFT) /* Left or right Shift key? */
         vcode = MapVirtualKey(scode, MAPVK_VSC_TO_VK_EX);
      my_code = hw_to_mycode[vcode];
   }
   update_modifiers(my_code, true);   

   actual_repeat = repeated && _AL_KEYBOARD_STATE_KEY_DOWN(the_state, my_code);
   _AL_KEYBOARD_STATE_SET_KEY_DOWN(the_state, my_code);

   if (!_al_event_source_needs_to_generate_event(&the_keyboard.es))
      return;

   event.keyboard.type = ALLEGRO_EVENT_KEY_DOWN;
   event.keyboard.timestamp = al_get_time();
   event.keyboard.display = display;
   event.keyboard.keycode = my_code;
   event.keyboard.unichar = 0;
   event.keyboard.modifiers = 0;
   event.keyboard.repeat = false;

   _al_event_source_lock(&the_keyboard.es);

   if (my_code > 0 && !actual_repeat) {
      _al_event_source_emit_event(&the_keyboard.es, &event);
   }

   /* Send char events, but not for modifier keys or dead keys. */
   if (my_code < ALLEGRO_KEY_MODIFIERS) {
      char_count = ToUnicode(vcode, scode, GetKeyboardState(ks) ? ks : NULL, buf, 8, 0);
      /* Send ASCII code 127 for both Del keys. */
      if (char_count == 0 && vcode == VK_DELETE) {
         char_count = 1;
         buf[0] = 127;
      }
      if (char_count != -1) { /* -1 means it was a dead key. */
         event_count = char_count ? char_count : 1;
         event.keyboard.type = ALLEGRO_EVENT_KEY_CHAR;
         update_toggle_modifiers();
         event.keyboard.modifiers = modifiers;
         event.keyboard.repeat = actual_repeat;
         for (i = 0; i < event_count; i++) {
            event.keyboard.unichar = buf[i];
            _al_event_source_emit_event(&the_keyboard.es, &event);
         }
      }
   }
   _al_event_source_unlock(&the_keyboard.es);

   /* Toggle mouse grab key. */
   if (my_code && !repeated) {
      ALLEGRO_SYSTEM_WIN *system = (void *)al_get_system_driver();
      if (my_code == system->toggle_mouse_grab_keycode &&
         (modifiers & system->toggle_mouse_grab_modifiers) == system->toggle_mouse_grab_modifiers)
      {
         if (system->mouse_grab_display == display) {
            al_ungrab_mouse();
         }
         else {
            al_grab_mouse(display);
         }
      }
   }
}