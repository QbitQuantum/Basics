  void keyEvent(rdr::U32 keysym, bool down, bool jap)
  {
	  //vnclog.Print(LL_INTWARN, " keysym 0x%x",keysym);
	if (keysym>=XK_dead_grave && keysym <=XK_dead_belowdot)// && down)
	{
		keysymDead=keysym;
		vnclog.Print(LL_INTWARN, " ************** DEAD KEY");
		//we have a dead key
		//Record dead key
		return;
	}

    if ((keysym >= 32 && keysym <= 126) ||
        (keysym >= 160 && keysym <= 255))
    {
	if (keysymDead!=0 && down)
	{
		vnclog.Print(LL_INTWARN, " Compose dead 0x%x 0x%x",keysymDead,keysym);
		switch (keysymDead)
		{
		case XK_dead_grave:
			switch(keysym)
			{
			case XK_A: keysym=XK_Agrave;break;
			case XK_E: keysym=XK_Egrave;break;
			case XK_I: keysym=XK_Igrave;break;
			case XK_O: keysym=XK_Ograve;break;
			case XK_U: keysym=XK_Ugrave;break;
			case XK_a: keysym=XK_agrave;break;
			case XK_e: keysym=XK_egrave;break;
			case XK_i: keysym=XK_igrave;break;
			case XK_o: keysym=XK_ograve;break;
			case XK_u: keysym=XK_ugrave;break;
			}
		case XK_dead_acute:
			switch(keysym)
			{
			case XK_A: keysym=XK_Aacute;break;
			case XK_E: keysym=XK_Eacute;break;
			case XK_I: keysym=XK_Iacute;break;
			case XK_O: keysym=XK_Oacute;break;
			case XK_U: keysym=XK_Uacute;break;
			case XK_a: keysym=XK_aacute;break;
			case XK_e: keysym=XK_eacute;break;
			case XK_i: keysym=XK_iacute;break;
			case XK_o: keysym=XK_oacute;break;
			case XK_u: keysym=XK_uacute;break;
			case XK_y: keysym=XK_yacute;break;
			case XK_Y: keysym=XK_Yacute;break;

			}
		case XK_dead_circumflex:
			switch(keysym)
			{
			case XK_A: keysym=XK_Acircumflex;break;
			case XK_E: keysym=XK_Ecircumflex;break;
			case XK_I: keysym=XK_Icircumflex;break;
			case XK_O: keysym=XK_Ocircumflex;break;
			case XK_U: keysym=XK_Ucircumflex;break;
			case XK_a: keysym=XK_acircumflex;break;
			case XK_e: keysym=XK_ecircumflex;break;
			case XK_i: keysym=XK_icircumflex;break;
			case XK_o: keysym=XK_ocircumflex;break;
			case XK_u: keysym=XK_ucircumflex;break;
			}
		case XK_dead_tilde:
			switch(keysym)
			{
			case XK_A : keysym=XK_Ntilde;break;
			case XK_O : keysym=XK_Otilde;break;
			case XK_a : keysym=XK_atilde;break;
			case XK_n : keysym=XK_ntilde;break;
			case XK_o : keysym=XK_otilde;break;
			}

		case XK_dead_diaeresis:
			switch(keysym)
			{
			case XK_A: keysym=XK_Adiaeresis;break;
			case XK_E: keysym=XK_Ediaeresis;break;
			case XK_I: keysym=XK_Idiaeresis;break;
			case XK_O: keysym=XK_Odiaeresis;break;
			case XK_U: keysym=XK_Udiaeresis;break;
			case XK_a: keysym=XK_adiaeresis;break;
			case XK_e: keysym=XK_ediaeresis;break;
			case XK_i: keysym=XK_idiaeresis;break;
			case XK_o: keysym=XK_odiaeresis;break;
			case XK_u: keysym=XK_udiaeresis;break;
			case XK_y: keysym=XK_ydiaeresis;break;

			}
		case XK_dead_cedilla:
			switch(keysym)
			{
			case XK_C: keysym=XK_Ccedilla;break;
			case XK_c: keysym=XK_ccedilla;break;
			}
		}
		keysymDead=0;
		vnclog.Print(LL_INTWARN, " Composed 0x%x",keysym);

	}
      // ordinary Latin-1 character

      SHORT s = VkKeyScan(keysym);

      //	[v1.0.2-jp1 fix] yak!'s patch
	  // This break Other keyboards, we need an easy way of fixing this
	  if (jap)
	  {
		  if (keysym==XK_kana_WO) {
			s = 0x0130;
		  } else if (keysym==XK_backslash) {
			s = 0x00e2;
		  } else if (keysym==XK_yen) {
			s = 0x00dc;
		  }
	  }

	  //vnclog.Print(LL_INTWARN, " SHORT s %i",s);

	 if (s == -1)
	 {
		 
      if (down) {
		  vnclog.Print(LL_INTWARN, "down");
        // not a single keypress - try synthesizing dead chars.
			{
			  vnclog.Print(LL_INTWARN, " Found key");
			  //Lookup ascii representation
			  int ascii=0;
#if 0
              // 11 Dec 2008 jdp disabled since the viewer is sending unicode now
			  for (ascii=0;ascii<256;ascii++)
			  {
				  if (keysym==ascii_to_x[ascii]) break;
			  }
#endif
              ascii = keysym;
			  if (ascii <= 255)
			  {

			  rdr::U8 a0=ascii/100;
			  ascii=ascii%100;
			  rdr::U8 a1=ascii/10;
			  ascii=ascii%10;
			  rdr::U8 a2=ascii;

              KeyStateModifier shift(VK_SHIFT);
              KeyStateModifier lshift(VK_LSHIFT);
              KeyStateModifier rshift(VK_RSHIFT);

              if (vncService::IsWin95()) {
                shift.release();
              } else {
                lshift.release();
                rshift.release();
			  }

              vnclog.Print(LL_INTWARN, " Simulating ALT+%d%d%d\n", a0, a1 ,a2);

			  keybd_event(VK_MENU,MapVirtualKey( VK_MENU, 0 ), 0 ,0);
              /**
                Pressing the Alt+NNN combinations without leading zero (for example, Alt+20, Alt+130, Alt+221) 
                will insert characters from the Extended ASCII (or MS DOS ASCII, or OEM) table. The character 
                glyphs contained by this table depend on the language of Windows. See the table below for the 
                list of characters that can be inserted through the Alt+NNN combinations (without leading zero)
                in English Windows.

                Pressing the Alt+0NNN combinations will insert the ANSI characters corresponding to the activate 
                keyboard layout. Please see Windows Character Map utility (charmap.exe) for the possible Alt+0NNN
                combinations.

                Finally, the Alt+00NNN combinations (two leading zeros) will insert Unicode characters. The Unicode 
                codes of characters are displayed in Charmap.

              **/
              // jdp 11 December 2008 - Need the leading 0! 
			  keybd_event(VK_NUMPAD0,    MapVirtualKey(VK_NUMPAD0,    0), 0, 0);
			  keybd_event(VK_NUMPAD0,    MapVirtualKey(VK_NUMPAD0,    0),KEYEVENTF_KEYUP,0);
			  keybd_event(VK_NUMPAD0+a0, MapVirtualKey(VK_NUMPAD0+a0, 0), 0, 0);
			  keybd_event(VK_NUMPAD0+a0, MapVirtualKey(VK_NUMPAD0+a0, 0),KEYEVENTF_KEYUP,0);
			  keybd_event(VK_NUMPAD0+a1, MapVirtualKey(VK_NUMPAD0+a1, 0),0,0);
			  keybd_event(VK_NUMPAD0+a1, MapVirtualKey(VK_NUMPAD0+a1, 0),KEYEVENTF_KEYUP, 0);
			  keybd_event(VK_NUMPAD0+a2, MapVirtualKey(VK_NUMPAD0+a2, 0) ,0, 0);
			  keybd_event(VK_NUMPAD0+a2, MapVirtualKey(VK_NUMPAD0+a2, 0),KEYEVENTF_KEYUP, 0);
			  keybd_event(VK_MENU, MapVirtualKey( VK_MENU, 0 ),KEYEVENTF_KEYUP, 0);
			  return;
			  }
        }
        vnclog.Print(LL_INTWARN, "ignoring unrecognised Latin-1 keysym 0x%x",keysym);
      }
      return;
    }

      /*if (s == -1) {
        vnclog.Print(LL_INTWARN, "ignoring unrecognised Latin-1 keysym %d\n",
                     keysym);
		keybd_event( VK_MENU, MapVirtualKey(VK_MENU, 0),0, 0);
		keybd_event( VK_MENU, MapVirtualKey(VK_MENU, 0),KEYEVENTF_KEYUP, 0);


        return;
      }*/

      BYTE vkCode = LOBYTE(s);

      // 18 March 2008 jdp
      // Correct the keymask shift state to cope with the capslock state
      BOOL capslockOn = (GetKeyState(VK_CAPITAL) & 1) != 0;

      BYTE modifierState = HIBYTE(s);
      modifierState = capslockOn ? modifierState ^ 1 : modifierState;
      KeyStateModifier ctrl(VK_CONTROL);
      KeyStateModifier alt(VK_MENU);
      KeyStateModifier shift(VK_SHIFT);
      KeyStateModifier lshift(VK_LSHIFT);
      KeyStateModifier rshift(VK_RSHIFT);

      if (down) {
        if (modifierState & 2) ctrl.press();
        if (modifierState & 4) alt.press();
        if (modifierState & 1) {
          shift.press(); 
        } else {
		  // [v1.0.2-jp1 fix] Even if "SHIFT + SPACE" are pressed, "SHIFT" is valid
          if (vkCode == 0x20){
		  }
		  else{
            if (vncService::IsWin95()) {
              shift.release();
			} else {
              lshift.release();
              rshift.release();
			}
		  }
        }
      }
      vnclog.Print(LL_INTINFO,
                   "latin-1 key: keysym %d(0x%x) vkCode 0x%x down %d capslockOn %d\n",
                   keysym, keysym, vkCode, down, capslockOn);

      doKeyboardEvent(vkCode, down ? 0 : KEYEVENTF_KEYUP);

    } else {

      // see if it's a recognised keyboard key, otherwise ignore it

      if (vkMap.find(keysym) == vkMap.end()) {
        vnclog.Print(LL_INTWARN, "ignoring unknown keysym %d\n",keysym);
        return;
      }
      BYTE vkCode = vkMap[keysym];
      DWORD flags = 0;
      if (extendedMap[keysym]) flags |= KEYEVENTF_EXTENDEDKEY;
      if (!down) flags |= KEYEVENTF_KEYUP;

//      vnclog.Print(LL_INTINFO,
  //                "keyboard key: keysym %d(0x%x) vkCode 0x%x ext %d down %d\n",
    //               keysym, keysym, vkCode, extendedMap[keysym], down);

      if (down && (vkCode == VK_DELETE) &&
          ((GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0) &&
          ((GetAsyncKeyState(VK_MENU) & 0x8000) != 0) &&
          vncService::IsWinNT())
      {
		vnclog.Print(LL_INTINFO,
                 "CAD\n");
		// If running under Vista and started from Session0 in Application mode
		if (vncService::VersionMajor()>=6 && vncService::RunningFromExternalService() )
		{
			      vnclog.Print(LL_INTINFO,
                 "Vista and runnning as system -> CAD\n");

				// Try to run the special Vista cad.exe file...
				HANDLE ThreadHandle2;
				DWORD dwTId;
				ThreadHandle2 = CreateThread(NULL, 0, Cadthread, NULL, 0, &dwTId);
				CloseHandle(ThreadHandle2);
		}
		else if (vncService::VersionMajor()>=6)
		{
			vnclog.Print(LL_INTINFO,
                 "Vista and runnning as user -> Taskmgr\n");
			WinExec("taskmgr.exe", SW_SHOWNORMAL);
		}
		else if (vncService::VersionMajor()<6 && vncService::RunningFromExternalService() )
		{
			vnclog.Print(LL_INTINFO,
                 "Not Vista and runnning as system, use old method\n");
			vncService::SimulateCtrlAltDel();
		}
		else if (vncService::VersionMajor()<6)
		{
			vnclog.Print(LL_INTINFO,
                 "Not Vista and runnning as user -> Taskmgr\n");
			WinExec("taskmgr.exe", SW_SHOWNORMAL);
		}
        return;
      }

      if (vncService::IsWin95()) {
        switch (vkCode) {
        case VK_RSHIFT:   vkCode = VK_SHIFT;   break;
        case VK_RCONTROL: vkCode = VK_CONTROL; break;
        case VK_RMENU:    vkCode = VK_MENU;    break;
        }
      }

      doKeyboardEvent(vkCode, flags);
    }
  }