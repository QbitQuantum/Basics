LRESULT CALLBACK LowLevelHook::VncLowLevelKbHookProc(INT nCode, WPARAM wParam, LPARAM lParam)
{
TRY_CATCH

	//if set to TRUE, the key-pressed message will NOT be passed on to windows.
	BOOL fHandled = FALSE;
	BOOL fKeyDown = FALSE;
	static bool winKeyDown = false;
	static int countWinKeysToSkip = 0;
	if (nCode == HC_ACTION) 
	{
		KBDLLHOOKSTRUCT *pkbdllhook = (KBDLLHOOKSTRUCT *)lParam;
		DWORD ProcessID ;

		//Receive the process ID of the Active Window
		//(The window with the input focus)
		//GetWindowThreadProcessId(GetFocus(),&ProcessID);
		GetWindowThreadProcessId(GetForegroundWindow(), &ProcessID);
		GetWindowThreadProcessId(g_hwndVNCViewer, &g_VncProcessID);

		//only if this is "our" process (vncviewer's process)
		//we should intecept the key-presses
		if (ProcessID==g_VncProcessID 
			&& 
			ClientConnection::m_focused
			||
			ClientConnection::m_fullScreen > 0)
		{

			fKeyDown = ( (wParam==WM_KEYDOWN) || (wParam==WM_SYSKEYDOWN) );

			switch (pkbdllhook->vkCode)
			{
				case VK_RIGHT:
				case VK_LEFT:
				case VK_DOWN:
				case VK_UP:
				case VK_TAB:
				case VK_NEXT:
				case VK_PRIOR:
				case VK_END:
				case VK_HOME:
				case VK_BACK:
				case VK_RETURN:
				case VK_F4:
				case VK_F3:

					//(cMsgBoxLog()).Add(_MESSAGE_,"VK_UP");
					if (g_fHookActive) 
					{
						if (fKeyDown)
							PostMessage(g_hwndVNCViewer, wParam + WM_USER, pkbdllhook->vkCode, 0);
						fHandled = TRUE;
					}
					break;
					//Print Screen Key 
					//      Request Full screen Update
					//      Simulate a "Request Refresh" from the System Menu
				case VK_SNAPSHOT:
					if (fKeyDown && g_fHookActive) 
					{
						PostMessage(g_hwndVNCViewer,WM_SYSCOMMAND,ID_REQUEST_REFRESH,0);
						fHandled = TRUE;
					}
					break ;

					//Pause Key 
					//      Toggle FullScreen On/Off
					//      Simulate a "FullScreen" from the System Menu
				case VK_PAUSE:
					if (fKeyDown && g_fHookActive)
					{
						PostMessage(g_hwndVNCViewer,WM_SYSCOMMAND,ID_FULLSCREEN,0);
						fHandled = TRUE;
					}
					break ;


					//Left or Right CONTROL keys
					//      Simulate a "Send CONTROL up/down" from the System Menu
				case VK_LCONTROL:
				case VK_RCONTROL:
					if (g_fHookActive) 
					{
						if(fKeyDown)
							PostMessage(g_hwndVNCViewer,WM_SYSCOMMAND,ID_CONN_CTLDOWN,0);
						else
							PostMessage(g_hwndVNCViewer,WM_SYSCOMMAND,ID_CONN_CTLUP,0);
						fHandled = TRUE;
					}
					break;

					//Either Left or Right ALT keys
					//      Simulate a "Send ALT up/down" from the System Menu
				case VK_LMENU:
				case VK_RMENU:
					if (g_fHookActive) 
					{
						if(fKeyDown)
							PostMessage(g_hwndVNCViewer,WM_SYSCOMMAND,ID_CONN_ALTDOWN,0);
						else
							PostMessage(g_hwndVNCViewer,WM_SYSCOMMAND,ID_CONN_ALTUP,0);
						fHandled = TRUE;
					}
					break;
				case VK_LWIN:
					if (g_fHookActive) 
					{
						if(fKeyDown)
						{
							winKeyDown = true;
							Log.Add(_MESSAGE_,_T("LWin key pressed"));
							PostMessage(g_hwndVNCViewer,WM_SYSCOMMAND,ID_VK_LWINDOWN,0);
						}
						else
						{
							winKeyDown = false;
							Log.Add(_MESSAGE_,_T("LWin key unpressed"));
							PostMessage(g_hwndVNCViewer,WM_SYSCOMMAND,ID_VK_LWINUP,0);
						}
						fHandled = countWinKeysToSkip>0?FALSE:TRUE;
						if (countWinKeysToSkip>0)
							--countWinKeysToSkip;
					}
					break;
				case VK_RWIN:
					if (g_fHookActive) 
					{
						if(fKeyDown)
						{
							winKeyDown = true;
							Log.Add(_MESSAGE_,_T("RWin key pressed"));
							PostMessage(g_hwndVNCViewer,WM_SYSCOMMAND,ID_VK_RWINDOWN,0);
						}
						else
						{
							winKeyDown = false;
							Log.Add(_MESSAGE_,_T("RWin key unpressed"));
							PostMessage(g_hwndVNCViewer,WM_SYSCOMMAND,ID_VK_RWINUP,0);
						}
						fHandled = countWinKeysToSkip>0?FALSE:TRUE;
						if (countWinKeysToSkip>0)
							--countWinKeysToSkip;
					}
					break;
				case VK_APPS:
					if (g_fHookActive)
					{
						if(fKeyDown)
							PostMessage(g_hwndVNCViewer,WM_SYSCOMMAND,ID_VK_APPSDOWN,0);
						else
							PostMessage(g_hwndVNCViewer,WM_SYSCOMMAND,ID_VK_APPSUP,0);
						fHandled = TRUE;
					}
					break; 

					//Scroll Lock = Turn the whole thing on or off
					//This is a little tricky hack:
					//Windows sets the scroll-lock LED on or off when the user PRESSes the scroll-lock key.
					//We'll check the LED state when the user RELEASEs the key, so the LED is already set.
					//If the LED/ScrollLock is ON, we'll activate the special key interception.
				/*case VK_SCROLL:
					if (!fKeyDown) 
					{
						g_fHookActive = GetScrollLockState(); 
					}
					break;*/

					//SPACEBAR = When key interception is Active, no special handling is required for 'spacebar'.
					//But when key interception is turned off, I want ALT+SPACE to open the VNCViewer's System Menu.
				case VK_SPACE:
					if (!g_fHookActive) 
					{
						if (pkbdllhook->flags & LLKHF_ALTDOWN) 
						{
							if(!fKeyDown)
								PostMessage(g_hwndVNCViewer,WM_SYSCOMMAND,0xF100,0x20); 

							fHandled = TRUE;
						}
					}
					break ;

					//ESCAPE = ALT+ESC is also a way to switch application, so we block the ESCAPE key,
					//Otherwise windows (on the VNCViewer's side) will switch to another application.
					//Transmitting the ALT+ESCAPE combination to a VNCServer running Windows doesn't work
					//very well, so for now, we'll just block the ALT+ESCAPE combination.
					//(CTRL+ESC work OK, BTW)
				case VK_ESCAPE:
					if (g_fHookActive)
					{
						if (pkbdllhook->flags & LLKHF_ALTDOWN) 
						{
							fHandled = TRUE;
						} else
						if (fKeyDown)
						{
							fHandled = TRUE;
							PostMessage(g_hwndVNCViewer, wParam + WM_USER, pkbdllhook->vkCode, 0);
						}
					}
					break;
				default:
					if (g_fHookActive)
					{
						switch(pkbdllhook->vkCode)
						{
							case VK_LSHIFT:
							case VK_RSHIFT:
							case VK_SHIFT:
								/*pkbdllhook->vkCode = VK_SHIFT;
								fHandled = TRUE;
								break;*/
							case VK_CAPITAL:
							case VK_NUMLOCK:
							case VK_SCROLL:
								fHandled = FALSE;
								break;
							default:
								fHandled = TRUE;
								break;
						}
						if (TRUE == fHandled && fKeyDown)
						{
							if (pkbdllhook->vkCode >= 0x41 /*A key*/ || pkbdllhook->vkCode <= 0x5A /*Z key*/ && fKeyDown)
							{
								if (winKeyDown && 
									pkbdllhook->vkCode == 'l'-'a' + 0x41)
								{
									countWinKeysToSkip = 2;
									Log.Add(_MESSAGE_,_T("Win+L pressed, injecting win key to prevent keys sticking on windows Vista"));
									keybd_event(VK_LWIN, 0, 0, 0);
									keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
								} else
									SendMessage(g_hwndVNCViewer, wParam + WM_USER, pkbdllhook->vkCode, 0);
							}
							else
								if (ClientConnection::m_fullScreen > 0)
									PostMessage(g_hwndVNCViewer, wParam + WM_USER, pkbdllhook->vkCode, 0);
								else 
									fHandled = FALSE;
						}
					}
			} //switch(pkbdllhook->vkCode)

		} // if (ProcessID == g_VncProcesID)

	} // if (nCode==HT_ACTION)
	//Call the next hook, if we didn't handle this message
	return (fHandled ? TRUE : CallNextHookEx(g_HookID, nCode, wParam, lParam));
CATCH_LOG()
	return CallNextHookEx(g_HookID, nCode, wParam, lParam);
}