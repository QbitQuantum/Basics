static int
add_menu_item (HMENU menu, widget_value *wv, HMENU item)
{
  UINT fuFlags;
  char *out_string, *p, *q;
  int return_value;
  size_t nlen, orig_len;
  USE_SAFE_ALLOCA;

  if (menu_separator_name_p (wv->name))
    {
      fuFlags = MF_SEPARATOR;
      out_string = NULL;
    }
  else
    {
      if (wv->enabled)
	fuFlags = MF_STRING;
      else
	fuFlags = MF_STRING | MF_GRAYED;

      if (wv->key != NULL)
	{
	  out_string = SAFE_ALLOCA (strlen (wv->name) + strlen (wv->key) + 2);
	  p = stpcpy (out_string, wv->name);
	  p = stpcpy (p, "\t");
	  strcpy (p, wv->key);
	}
      else
	out_string = (char *)wv->name;

      /* Quote any special characters within the menu item's text and
	 key binding.  */
      nlen = orig_len = strlen (out_string);
      if (unicode_append_menu)
        {
          /* With UTF-8, & cannot be part of a multibyte character.  */
          for (p = out_string; *p; p++)
            {
              if (*p == '&')
                nlen++;
            }
        }
#ifndef NTGUI_UNICODE
      else
        {
          /* If encoded with the system codepage, use multibyte string
             functions in case of multibyte characters that contain '&'.  */
          for (p = out_string; *p; p = _mbsinc (p))
            {
              if (_mbsnextc (p) == '&')
                nlen++;
            }
        }
#endif /* !NTGUI_UNICODE */

      if (nlen > orig_len)
        {
          p = out_string;
          out_string = SAFE_ALLOCA (nlen + 1);
          q = out_string;
          while (*p)
            {
              if (unicode_append_menu)
                {
                  if (*p == '&')
                    *q++ = *p;
                  *q++ = *p++;
                }
#ifndef NTGUI_UNICODE
              else
                {
                  if (_mbsnextc (p) == '&')
                    {
                      _mbsncpy (q, p, 1);
                      q = _mbsinc (q);
                    }
                  _mbsncpy (q, p, 1);
                  p = _mbsinc (p);
                  q = _mbsinc (q);
                }
#endif /* !NTGUI_UNICODE */
            }
          *q = '\0';
        }

      if (item != NULL)
	fuFlags = MF_POPUP;
      else if (wv->title || wv->call_data == 0)
	{
	  /* Only use MF_OWNERDRAW if GetMenuItemInfo is usable, since
	     we can't deallocate the memory otherwise.  */
	  if (get_menu_item_info)
	    {
              out_string = (char *) local_alloc (strlen (wv->name) + 1);
              strcpy (out_string, wv->name);
#ifdef MENU_DEBUG
	      DebPrint ("Menu: allocating %ld for owner-draw", out_string);
#endif
	      fuFlags = MF_OWNERDRAW | MF_DISABLED;
	    }
	  else
	    fuFlags = MF_DISABLED;
	}

      /* Draw radio buttons and tickboxes. */
      else if (wv->selected && (wv->button_type == BUTTON_TYPE_TOGGLE ||
				wv->button_type == BUTTON_TYPE_RADIO))
	fuFlags |= MF_CHECKED;
      else
	fuFlags |= MF_UNCHECKED;
    }

  if (unicode_append_menu && out_string)
    {
      /* Convert out_string from UTF-8 to UTF-16-LE.  */
      int utf8_len = strlen (out_string);
      WCHAR * utf16_string;
      if (fuFlags & MF_OWNERDRAW)
	utf16_string = local_alloc ((utf8_len + 1) * sizeof (WCHAR));
      else
	utf16_string = SAFE_ALLOCA ((utf8_len + 1) * sizeof (WCHAR));

      utf8to16 ((unsigned char *)out_string, utf8_len, utf16_string);
      return_value = unicode_append_menu (menu, fuFlags,
					  item != NULL ? (UINT_PTR) item
					    : (UINT_PTR) wv->call_data,
					  utf16_string);

#ifndef NTGUI_UNICODE /* Fallback does not apply when always UNICODE */
      if (!return_value)
	{
	  /* On W9x/ME, Unicode menus are not supported, though AppendMenuW
	     apparently does exist at least in some cases and appears to be
	     stubbed out to do nothing.  out_string is UTF-8, but since
	     our standard menus are in English and this is only going to
	     happen the first time a menu is used, the encoding is
	     of minor importance compared with menus not working at all.  */
	  return_value =
	    AppendMenu (menu, fuFlags,
			item != NULL ? (UINT_PTR) item: (UINT_PTR) wv->call_data,
			out_string);
	  /* Don't use Unicode menus in future, unless this is Windows
	     NT or later, where a failure of AppendMenuW does NOT mean
	     Unicode menus are unsupported.  */
	  if (osinfo_cache.dwPlatformId != VER_PLATFORM_WIN32_NT)
	    unicode_append_menu = NULL;
	}
#endif /* NTGUI_UNICODE */

      if (unicode_append_menu && (fuFlags & MF_OWNERDRAW))
	local_free (out_string);
    }
  else
    {
      return_value =
	AppendMenu (menu,
		    fuFlags,
		    item != NULL ? (UINT_PTR) item : (UINT_PTR) wv->call_data,
		    out_string );
    }

  /* This must be done after the menu item is created.  */
  if (!wv->title && wv->call_data != 0)
    {
      if (set_menu_item_info)
	{
	  MENUITEMINFO info;
	  memset (&info, 0, sizeof (info));
	  info.cbSize = sizeof (info);
	  info.fMask = MIIM_DATA;

	  /* Set help string for menu item.  Leave it as a pointer to
	     a Lisp_String until it is ready to be displayed, since GC
	     can happen while menus are active.  */
	  if (!NILP (wv->help))
	    {
	      /* We use XUNTAG below because in a 32-bit build
		 --with-wide-int we cannot pass a Lisp_Object
		 via a DWORD member of MENUITEMINFO.  */
	      /* As of Jul-2012, w32api headers say that dwItemData
		 has DWORD type, but that's a bug: it should actually
		 be ULONG_PTR, which is correct for 32-bit and 64-bit
		 Windows alike.  MSVC headers get it right; hopefully,
		 MinGW headers will, too.  */
	      eassert (STRINGP (wv->help));
	      info.dwItemData = (ULONG_PTR) XUNTAG (wv->help, Lisp_String);
	    }
	  if (wv->button_type == BUTTON_TYPE_RADIO)
	    {
	      /* CheckMenuRadioItem allows us to differentiate TOGGLE and
		 RADIO items, but is not available on NT 3.51 and earlier.  */
	      info.fMask |= MIIM_TYPE | MIIM_STATE;
	      info.fType = MFT_RADIOCHECK | MFT_STRING;
	      info.dwTypeData = out_string;
	      info.fState = wv->selected ? MFS_CHECKED : MFS_UNCHECKED;
	    }

	  set_menu_item_info (menu,
			      item != NULL ? (UINT_PTR) item : (UINT_PTR) wv->call_data,
			      FALSE, &info);
	}
    }
  SAFE_FREE ();
  return return_value;
}