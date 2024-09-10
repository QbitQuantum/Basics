static void
update_keymap (void)
{
  static guint current_serial = 0;
  guchar key_state[256];
  guint scancode;
  guint vk;
  gboolean capslock_tested = FALSE;

  if (keysym_tab != NULL && current_serial == _gdk_keymap_serial)
    return;

  current_serial = _gdk_keymap_serial;

  if (keysym_tab == NULL)
    keysym_tab = g_new (guint, 4*256);

  memset (key_state, 0, sizeof (key_state));

  _gdk_keyboard_has_altgr = FALSE;
  gdk_shift_modifiers = GDK_SHIFT_MASK;

  for (vk = 0; vk < 256; vk++)
    {
      if ((scancode = MapVirtualKey (vk, 0)) == 0 &&
	  vk != VK_DIVIDE)
	keysym_tab[vk*4+0] =
	  keysym_tab[vk*4+1] =
	  keysym_tab[vk*4+2] =
	  keysym_tab[vk*4+3] = GDK_VoidSymbol;
      else
	{
	  gint shift;

	  if (vk == VK_RSHIFT)
	    _scancode_rshift = scancode;

	  key_state[vk] = 0x80;
	  for (shift = 0; shift < 4; shift++)
	    {
	      guint *ksymp = keysym_tab + vk*4 + shift;
	      
	      set_shift_vks (key_state, shift);

	      *ksymp = 0;

	      /* First, handle those virtual keys that we always want
	       * as special GDK_* keysyms, even if ToAsciiEx might
	       * turn some them into a ASCII character (like TAB and
	       * ESC).
	       */
	      handle_special (vk, ksymp, shift);

	      if (*ksymp == 0)
		{
		  wchar_t wcs[10];
		  gint k;

		  wcs[0] = wcs[1] = 0;
		  k = ToUnicodeEx (vk, scancode, key_state,
				   wcs, G_N_ELEMENTS (wcs),
				   0, _gdk_input_locale);
#if 0
		  g_print ("ToUnicodeEx(%#02x, %d: %d): %d, %04x %04x\n",
			   vk, scancode, shift, k,
			   wcs[0], wcs[1]);
#endif
		  if (k == 1)
		    *ksymp = gdk_unicode_to_keyval (wcs[0]);
		  else if (k == -1)
		    {
		      guint keysym = gdk_unicode_to_keyval (wcs[0]);

		      /* It is a dead key, and it's has been stored in
		       * the keyboard layout's state by
		       * ToAsciiEx()/ToUnicodeEx(). Yes, this is an
		       * incredibly silly API! Make the keyboard
		       * layout forget it by calling
		       * ToAsciiEx()/ToUnicodeEx() once more, with the
		       * virtual key code and scancode for the
		       * spacebar, without shift or AltGr. Otherwise
		       * the next call to ToAsciiEx() with a different
		       * key would try to combine with the dead key.
		       */
		      reset_after_dead (key_state);

		      /* Use dead keysyms instead of "undead" ones */
		      handle_dead (keysym, ksymp);
		    }
		  else if (k == 0)
		    {
		      /* Seems to be necessary to "reset" the keyboard layout
		       * in this case, too. Otherwise problems on NT4.
		       */
		      reset_after_dead (key_state);
		    }
		  else
		    {
#if 0
		      GDK_NOTE (EVENTS,
				g_print ("ToUnicodeEx returns %d "
					 "for vk:%02x, sc:%02x%s%s\n",
					 k, vk, scancode,
					 (shift&0x1 ? " shift" : ""),
					 (shift&0x2 ? " altgr" : "")));
#endif
		    }
		}
	      if (*ksymp == 0)
		*ksymp = GDK_VoidSymbol;
	    }
	  key_state[vk] = 0;

	  /* Check if keyboard has an AltGr key by checking if
	   * the mapping with Control+Alt is different.
	   */
	  if (!_gdk_keyboard_has_altgr)
	    if ((keysym_tab[vk*4 + 2] != GDK_VoidSymbol &&
		 keysym_tab[vk*4] != keysym_tab[vk*4 + 2]) ||
		(keysym_tab[vk*4 + 3] != GDK_VoidSymbol &&
		 keysym_tab[vk*4 + 1] != keysym_tab[vk*4 + 3]))
	      _gdk_keyboard_has_altgr = TRUE;
	  
	  if (!capslock_tested)
	    {
	      /* Can we use this virtual key to determine the CapsLock
	       * key behaviour: CapsLock or ShiftLock? If it generates
	       * keysyms for printable characters and has a shifted
	       * keysym that isn't just the upperacase of the
	       * unshifted keysym, check the behaviour of VK_CAPITAL.
	       */
	      if (g_unichar_isgraph (gdk_keyval_to_unicode (keysym_tab[vk*4 + 0])) &&
		  keysym_tab[vk*4 + 1] != keysym_tab[vk*4 + 0] &&
		  g_unichar_isgraph (gdk_keyval_to_unicode (keysym_tab[vk*4 + 1])) &&
		  keysym_tab[vk*4 + 1] != gdk_keyval_to_upper (keysym_tab[vk*4 + 0]))
		{
		  guchar chars[2];
		  
		  capslock_tested = TRUE;
		  
		  key_state[VK_SHIFT] = 0;
		  key_state[VK_CONTROL] = key_state[VK_MENU] = 0;
		  key_state[VK_CAPITAL] = 1;

		  if (ToAsciiEx (vk, scancode, key_state,
				 (LPWORD) chars, 0, _gdk_input_locale) == 1)
		    {
		      if (chars[0] >= GDK_space &&
			  chars[0] <= GDK_asciitilde &&
			  chars[0] == keysym_tab[vk*4 + 1])
			{
			  /* CapsLock acts as ShiftLock */
			  gdk_shift_modifiers |= GDK_LOCK_MASK;
			}
		    }
		  key_state[VK_CAPITAL] = 0;
		}    
	    }
	}
    }
  GDK_NOTE (EVENTS, print_keysym_tab ());
} 