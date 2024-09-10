////////////////////////////////////////////////////////////////////////////////
// Window procedure for the Desktop window
LRESULT CALLBACK
DesktopWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
#ifndef _X64
	vncDesktop *_this = (vncDesktop*)GetWindowLong(hwnd, GWL_USERDATA);
#else
	vncDesktop *_this = (vncDesktop*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
#endif
	/*#ifdef _DEBUG
										char			szText[256];
										sprintf(szText,"Message %i\n",iMsg );
										OutputDebugString(szText);
										//vnclog.Print(LL_INTERR, VNCLOG("%i  \n"),iMsg);
			#endif*/
	switch (iMsg)
	{
	case WM_CREATE:
		vnclog.Print(LL_INTERR, VNCLOG("wmcreate  \n"));
		break;
	case WM_TIMER:
		if (_this->can_be_hooked)
		{
			if (wParam==100)
			{
					KillTimer(hwnd, 100);
					if (_this->startw8)
					{
						_this->startw8(!_this->multi_monitor);
						vnclog.Print(LL_INTERR, VNCLOG("set W8 hooks OK\n"));
						_this->m_hookinited = TRUE;
					}
					else if (_this->SetHook)
					{
						_this->SetHook(hwnd);
						vnclog.Print(LL_INTERR, VNCLOG("set SC hooks OK\n"));
						_this->m_hookinited = TRUE;
						if (_this->SetKeyboardFilterHooks) _this->SetKeyboardFilterHooks( _this->m_bIsInputDisabledByClient || _this->m_server->LocalInputsDisabled());
						if (_this->SetMouseFilterHooks) _this->SetMouseFilterHooks( _this->m_bIsInputDisabledByClient || _this->m_server->LocalInputsDisabled());
					}
					else if (_this->SetHooks)
					{
						if (!_this->SetHooks(
							GetCurrentThreadId(),
							RFB_SCREEN_UPDATE,
							RFB_COPYRECT_UPDATE,
							RFB_MOUSE_UPDATE, 0
							))
						{
							vnclog.Print(LL_INTERR, VNCLOG("failed to set system hooks\n"));
							// Switch on full screen polling, so they can see something, at least...
							_this->m_server->PollFullScreen(TRUE);
							_this->m_hookinited = FALSE;
						}
						else
						{
							vnclog.Print(LL_INTERR, VNCLOG("set hooks OK\n"));
							_this->m_hookinited = TRUE;
							// Start up the keyboard and mouse filters
							if (_this->SetKeyboardFilterHook) _this->SetKeyboardFilterHook(_this->m_bIsInputDisabledByClient || _this->m_server->LocalInputsDisabled());
							if (_this->SetMouseFilterHook) _this->SetMouseFilterHook(_this->m_bIsInputDisabledByClient || _this->m_server->LocalInputsDisabled());
						}
					}
			}
			else SetEvent(_this->trigger_events[0]);
		}
		break;
	case WM_MOUSESHAPE:
		if (_this->can_be_hooked)
		{
			SetEvent(_this->trigger_events[3]);
		}
		break;
	case WM_HOOKCHANGE:
		if (wParam==1)
			{
				if (_this->m_hookinited==FALSE)
							SetTimer(hwnd,100,1000,NULL);
			}
		else if (wParam==2)
		{
			if (_this->m_hookinited)
				{
					if (_this->SetHook)
					{
						if (_this->SetKeyboardFilterHooks) _this->SetKeyboardFilterHooks( _this->m_bIsInputDisabledByClient || _this->m_server->LocalInputsDisabled());
						if (_this->SetMouseFilterHooks) _this->SetMouseFilterHooks( _this->m_bIsInputDisabledByClient || _this->m_server->LocalInputsDisabled());
					}
					else if (_this->SetHooks)
					{
						if (_this->SetKeyboardFilterHook) _this->SetKeyboardFilterHook( _this->m_bIsInputDisabledByClient || _this->m_server->LocalInputsDisabled());
						if (_this->SetMouseFilterHook) _this->SetMouseFilterHook( _this->m_bIsInputDisabledByClient || _this->m_server->LocalInputsDisabled());
					}
				}
		}
		else if (_this->m_hookinited)
			{
				_this->m_hookinited=FALSE;
				if (_this->stopw8)
				{
					vnclog.Print(LL_INTERR, VNCLOG("unset W8 hooks OK\n"));
					_this->stopw8();
				}
				if (_this->UnSetHook)
				{
					vnclog.Print(LL_INTERR, VNCLOG("unset SC hooks OK\n"));
					_this->UnSetHook(hwnd);
				}
				else if (_this->UnSetHooks)
				{
				if(!_this->UnSetHooks(GetCurrentThreadId()) )
					vnclog.Print(LL_INTERR, VNCLOG("Unsethooks Failed\n"));
				else vnclog.Print(LL_INTERR, VNCLOG("Unsethooks OK\n"));
				}
			}
		return true;

	case WM_QUERYENDSESSION:

		/*if (OSversion()==2)
		{
		if (_this->m_hnextviewer!=NULL) ChangeClipboardChain(hwnd, _this->m_hnextviewer);
		_this->m_hnextviewer=NULL;
		if (_this->m_hookinited)
			{
				_this->m_hookinited=FALSE;
				if (_this->UnSetHook)
				{
					vnclog.Print(LL_INTERR, VNCLOG("unset SC hooks OK\n"));
					_this->UnSetHook(hwnd);
				}
				else if (_this->UnSetHooks)
				{
				if(!_this->UnSetHooks(GetCurrentThreadId()) )
					vnclog.Print(LL_INTERR, VNCLOG("Unsethooks Failed\n"));
				else vnclog.Print(LL_INTERR, VNCLOG("Unsethooks OK\n"));
				}
			}
		vnclog.Print(LL_INTERR, VNCLOG("WM_QUERYENDSESSION\n"));
		PostQuitMessage(0);
		SetEvent(_this->trigger_events[5]);
		}*/
		return DefWindowProc(hwnd, iMsg, wParam, lParam);

	case WM_CLOSE:
		if (_this->m_hnextviewer!=NULL) ChangeClipboardChain(hwnd, _this->m_hnextviewer);
		_this->m_hnextviewer=NULL;
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 100);
		if (_this->m_hnextviewer!=NULL) ChangeClipboardChain(hwnd, _this->m_hnextviewer);
		_this->m_hnextviewer=NULL;
		if (_this->m_hookinited)
			{
				if (_this->stopw8)
				{
					vnclog.Print(LL_INTERR, VNCLOG("unset W8 hooks OK\n"));
					_this->stopw8();
				}
				if (_this->UnSetHook)
				{
					vnclog.Print(LL_INTERR, VNCLOG("unset SC hooks OK\n"));
					_this->UnSetHook(hwnd);
				}
				else if (_this->UnSetHooks)
				{
				if(!_this->UnSetHooks(GetCurrentThreadId()) )
					vnclog.Print(LL_INTERR, VNCLOG("Unsethooks Failed\n"));
				else vnclog.Print(LL_INTERR, VNCLOG("Unsethooks OK\n"));
				}
				_this->m_hookinited=FALSE;
			}
		vnclog.Print(LL_INTERR, VNCLOG("WM_DESTROY\n"));
		break;
	///ddihook
	case WM_SYSCOMMAND:
		// User has clicked an item on the tray menu
		switch (wParam)
		{
			case SC_MONITORPOWER:
				vnclog.Print(LL_INTINFO, VNCLOG("Monitor22 %i\n"),lParam);
		}
		vnclog.Print(LL_INTINFO, VNCLOG("Monitor3 %i %i\n"),wParam,lParam);
		return DefWindowProc(hwnd, iMsg, wParam, lParam);
	case WM_POWER:
	case WM_POWERBROADCAST:
		// User has clicked an item on the tray menu
		switch (wParam)
		{
			case SC_MONITORPOWER:
				vnclog.Print(LL_INTINFO, VNCLOG("Monitor222 %i\n"),lParam);
		}
		vnclog.Print(LL_INTINFO, VNCLOG("Power3 %i %i\n"),wParam,lParam);
		return DefWindowProc(hwnd, iMsg, wParam, lParam);

	case WM_COPYDATA:
        {
			PCOPYDATASTRUCT pMyCDS = (PCOPYDATASTRUCT) lParam;
			if (pMyCDS->dwData==112233)
			{
					DWORD mysize=pMyCDS->cbData;
					char mytext[1024];
					char *myptr;
					char split[4][6];
					strcpy(mytext,(LPCSTR)pMyCDS->lpData);
					myptr=mytext;
					for (DWORD j =0; j<(mysize/20);j++)
					{
						for (int i=0;i<4;i++)
							{
								strcpy(split[i],"     ");
								strncpy(split[i],myptr,4);
								myptr=myptr+5;
							}
						_this->QueueRect(rfb::Rect(atoi(split[0]), atoi(split[1]), atoi(split[2]), atoi(split[3])));
					}
			}
			//vnclog.Print(LL_INTINFO, VNCLOG("copydata\n"));
        }
			return 0;

	// GENERAL

	case WM_DISPLAYCHANGE:
		// The display resolution is changing
		// We must kick off any clients since their screen size will be wrong
		// WE change the clients screensize, if they support it.
		vnclog.Print(LL_INTERR, VNCLOG("WM_DISPLAYCHANGE\n"));
		// We First check if the Resolution changed is caused by a temp resolution switch
		// For a temp resolution we don't use the driver, to fix the mirror driver
		// to the new change, a resolution switch is needed, preventing screensaver locking.

		if (_this->m_videodriver != NULL) //Video driver active
		{
			if (!_this->m_videodriver->blocked)
			{
				_this->m_displaychanged = TRUE;
				_this->m_hookdriver=true;
				_this->m_videodriver->blocked=true;
				vnclog.Print(LL_INTERR, VNCLOG("Resolution switch detected, driver active\n"));
			}
			else
			{
				//Remove display change, cause by driver activation
				_this->m_videodriver->blocked=false;
				vnclog.Print(LL_INTERR, VNCLOG("Resolution switch by driver activation removed\n"));
			}
		}
		else
		{
				_this->m_displaychanged = TRUE;
				_this->m_hookdriver=true;
				vnclog.Print(LL_INTERR, VNCLOG("Resolution switch detected, driver NOT active\n"));
		}
		return 0;

	case WM_SYSCOLORCHANGE:
	case WM_PALETTECHANGED:
		if (!_this->m_displaychanged)
		{
		// The palette colours have changed, so tell the server

		// Get the system palette
            // better to use the wrong colors than close the connection
		_this->SetPalette();

		// Update any palette-based clients, too
		//set to flase to avoid deadlock
		_this->m_server->UpdatePalette(false);
		}
		return 0;

		// CLIPBOARD MESSAGES

	case WM_CHANGECBCHAIN:
		// The clipboard chain has changed - check our nextviewer handle
		if ((HWND)wParam == _this->m_hnextviewer)
			_this->m_hnextviewer = (HWND)lParam;
		else
			if (_this->m_hnextviewer != NULL) {
				// adzm - 2010-07 - Fix clipboard hangs
				// use SendNotifyMessage instead of SendMessage so misbehaving or hung applications
				// won't cause our thread to hang.
				SendNotifyMessage(_this->m_hnextviewer,
							WM_CHANGECBCHAIN,
							wParam, lParam);
			}

		return 0;

	case WM_DRAWCLIPBOARD:
		// adzm - 2010-07 - Fix clipboard hangs
		if (_this->can_be_hooked && !_this->m_settingClipboardViewer)
		{
			// The clipboard contents have changed
			if((GetClipboardOwner() != _this->Window()) &&
				//_this->m_initialClipBoardSeen &&
				_this->m_clipboard_active && !_this->m_server->IsThereFileTransBusy())
			{
				// adzm - 2010-07 - Extended clipboard
				{
					// only need a window when setting clipboard data
					omni_mutex_lock l(_this->m_update_lock);
					_this->m_server->UpdateClipTextEx(NULL);
				}
				/*
				LPSTR cliptext = NULL;

				// Open the clipboard
				if (OpenClipboard(_this->Window()))
				{
					// Get the clipboard data
					HGLOBAL cliphandle = GetClipboardData(CF_TEXT);
					if (cliphandle != NULL)
					{
						LPSTR clipdata = (LPSTR) GlobalLock(cliphandle);

						// Copy it into a new buffer
						if (clipdata == NULL)
							cliptext = NULL;
						else
							cliptext = _strdup(clipdata);

						// Release the buffer and close the clipboard
						GlobalUnlock(cliphandle);
					}

					CloseClipboard();
				}

				if (cliptext != NULL)
				{
					int cliplen = strlen(cliptext);
					LPSTR unixtext = (char *)malloc(cliplen+1);

					// Replace CR-LF with LF - never send CR-LF on the wire,
					// since Unix won't like it
					int unixpos=0;
					for (int x=0; x<cliplen; x++)
					{
						if (cliptext[x] != '\x0d')
						{
							unixtext[unixpos] = cliptext[x];
							unixpos++;
						}
					}
					unixtext[unixpos] = 0;

					// Free the clip text
					free(cliptext);
					cliptext = NULL;

					// Now send the unix text to the server
					omni_mutex_lock l(_this->m_update_lock);
					_this->m_server->UpdateClipText(unixtext);

					free(unixtext);
				}
				*/
			}

			//_this->m_initialClipBoardSeen = TRUE;
		}

		if (_this->m_hnextviewer != NULL)
		{
			// adzm - 2010-07 - Fix clipboard hangs
			// Pass the message to the next window in clipboard viewer chain.

			// use SendNotifyMessage instead of SendMessage so misbehaving or hung applications
			// won't cause our thread to hang.
			return SendNotifyMessage(_this->m_hnextviewer, WM_DRAWCLIPBOARD, wParam, lParam);
		}

		return 0;

	default:
		return DefWindowProc(hwnd, iMsg, wParam, lParam);
	}
	return 0;
}