LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int gap = bevelWidth + borderWidth;

	switch (message)
	{
		case WM_PAINT:
		{
			OnPaint(hwnd);
		}
		break;

		// ==========

		case BB_RECONFIGURE:
		{
			if (myMenu){ DelMenu(myMenu); myMenu = NULL;}
			GetStyleSettings();
			InvalidateRect(hwndPlugin, NULL, true);
		}
		break;

		// for bbStylemaker
		case BB_REDRAWGUI:
		{
			GetStyleSettings();
			InvalidateRect(hwndPlugin, NULL, true);
		}
		break;

		case WM_DISPLAYCHANGE:
		{
			if(!inSlit)
			{
				// IntelliMove(tm)... <g>
				// (c) 2003 qwilk
				//should make this a function so it can be used on startup in case resolution changed since
				//the last time blackbox was used.
				int relx, rely;
				int oldscreenwidth = ScreenWidth;
				int oldscreenheight = ScreenHeight;
				ScreenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
				ScreenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);
				if (xpos > oldscreenwidth / 2)
				{
					relx = oldscreenwidth - xpos;
					xpos = ScreenWidth - relx;
				}
				if (ypos > oldscreenheight / 2)
				{
					rely = oldscreenheight - ypos;
					ypos = ScreenHeight - rely;
				}
				MoveWindow(hwndPlugin, xpos, ypos, width, height, true);
			}
		}
		break;

		// ==========

		case BB_BROADCAST:
		{
			szTemp = (char*)lParam;

			if (!_stricmp(szTemp, "@BBShowPlugins") &&  pluginToggle && !inSlit)
			{
				// Show window and force update...
				ShowWindow( hwndPlugin, SW_SHOW);
				InvalidateRect( hwndPlugin, NULL, true);
			}
			else if (!_stricmp(szTemp, "@BBHidePlugins") && pluginToggle && !inSlit)
			{
				// Hide window...
				ShowWindow( hwndPlugin, SW_HIDE);
			}

			//===================

			if (strnicmp(szTemp, "@BBSeekbar", 10))
				return 0;
			szTemp += 10;

			if (!_stricmp(szTemp, "About"))
			{
				char tmp_str[MAX_LINE_LENGTH];
				SendMessage(hwndBlackbox, BB_HIDEMENU, 0, 0);
				sprintf(tmp_str, "%s", szVersion);
				MessageBox(hwndBlackbox, tmp_str, szAppName, MB_OK | MB_TOPMOST);
			}

			//===================

			else if (!_strnicmp(szTemp, "StyleType", 9))
			{
				styleType = atoi(szTemp + 10);
				GetStyleSettings();
				InvalidateRect(hwndPlugin, NULL, true);
			}
			else if (!_strnicmp(szTemp, "TrackStyle", 10))
			{
				trackStyleType = atoi(szTemp + 11);
				GetStyleSettings();
				InvalidateRect(hwndPlugin, NULL, true);
			}
			else if (!_strnicmp(szTemp, "KnobStyle", 9))
			{
				knobStyleType = atoi(szTemp + 10);
				GetStyleSettings();
				InvalidateRect(hwndPlugin, NULL, true);
			}

			else if (!_strnicmp(szTemp, "Appearance", 10))
			{
				appearance = atoi(szTemp + 11);
				track_needsupdate = true;
				knob_needsupdate = true;
				InvalidateRect(hwndPlugin, NULL, true);
				ShowMyMenu(false);
			}
			else if (!_strnicmp(szTemp, "PlayerType", 10))
			{
				playerType = atoi(szTemp + 11);

				// Stop the monitor...
				unsigned long exitcode;
				GetExitCodeThread(hThread_Time, &exitcode);
				TerminateThread(hThread_Time, exitcode);

				FreeLibrary(controlPlugin);
				if(!loadPlayerControl(hInstance, playerType)){
					MessageBox(hwndBlackbox, "Player control plugin not found", szAppName, MB_OK | MB_ICONERROR | MB_TOPMOST);
				}

				// Start the monitoring threads...
				hThread_Time = CreateThread(NULL, 0, TimeProc, NULL, 0, &dwThreadId_Time);

				knob_needsupdate = true;
				InvalidateRect(hwndPlugin, NULL, true);
				ShowMyMenu(false);
			}

			//===================

			else if (!_strnicmp(szTemp, "WidthSize", 9))
			{
				newWidth = atoi(szTemp + 10);
				if(ResizeMyWindow(newWidth, height)){
					track_needsupdate = true;
					knob_needsupdate = true;
					InvalidateRect(hwndPlugin, NULL, true);
				}
			}
			else if (!_strnicmp(szTemp, "HeightSize", 10))
			{
				newHeight = atoi(szTemp + 11);
				if(ResizeMyWindow(width, newHeight)){
					track_needsupdate = true;
					knob_needsupdate = true;
					InvalidateRect(hwndPlugin, NULL, true);
				}
			}

			//===================

			else if (!_stricmp(szTemp, "pluginToggle"))
			{
				pluginToggle = (pluginToggle ? false : true);
				SetWindowModes();
			}
			else if (!_stricmp(szTemp, "OnTop"))
			{
				alwaysOnTop = (alwaysOnTop ? false : true);
				if(!inSlit)SetWindowPos( hwndPlugin,
                                                         alwaysOnTop ? HWND_TOPMOST : HWND_NOTOPMOST,
                                                         0, 0, 0, 0,
                                                         SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE);

				ShowMyMenu(false);
			}

			else if (!_stricmp(szTemp, "InSlit"))
			{
				if(inSlit && hSlit){
					// We are in the slit, so lets unload and get out..
					SendMessage(hSlit, SLIT_REMOVE, NULL, (LPARAM)hwndPlugin);

					// Here you can move to where ever you want ;)
					SetWindowPos(hwndPlugin, NULL, xpos, ypos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
					inSlit = false;
					SetWindowModes();
				}
				/* Make sure before you try and load into the slit that you have
				* the HWND of the slit ;)
				*/
				else if(hSlit){
					// (Back) into the slit..
					inSlit = true;
					SetWindowModes();
					SendMessage(hSlit, SLIT_ADD, NULL, (LPARAM)hwndPlugin);
				}
			}

			else if (!_stricmp(szTemp, "Transparent"))
			{
				transparency = (transparency ? false : true);
				SetWindowModes();
			}
			else if (!_strnicmp(szTemp, "AlphaValue", 10))
			{
				alpha = atoi(szTemp + 11);
				SetWindowModes();
			}
			else if (!_stricmp(szTemp, "SnapToEdge"))
			{
				snapWindow = (snapWindow ? false : true);
				ShowMyMenu(false);
			}
			else if (!_stricmp(szTemp, "ShowBorder"))
			{
				showBorder = (showBorder ? false : true);
				InvalidateRect(hwndPlugin, NULL, false);
				ShowMyMenu(false);
			}
			else if (!_stricmp(szTemp, "AllowTip"))
			{
				allowtip = (allowtip ? false : true);
				SetAllowTip(allowtip);
				ShowMyMenu(false);
			}

			else if (!_stricmp(szTemp, "Vertical"))
			{
				vertical = (vertical ? false : true);
				if(ResizeMyWindow(height, width)){
					track_needsupdate = true;
					knob_needsupdate = true;
					InvalidateRect(hwndPlugin, NULL, true);
				}
				ShowMyMenu(false);
			}
			else if (!_stricmp(szTemp, "Reversed"))
			{
				reversed = (reversed ? false : true);
				track_needsupdate = true;
				knob_needsupdate = true;
				InvalidateRect(hwndPlugin, NULL, true);
				ShowMyMenu(false);
			}

			//===================

			else if (!_stricmp(szTemp, "EditRC"))
			{
				BBExecute(GetDesktopWindow(), NULL,
				ReadString(extensionsrcPath(), "blackbox.editor:", "notepad.exe"),
                                          rcpath, NULL, SW_SHOWNORMAL, false);
			}
			else if (!_stricmp(szTemp, "ReloadSettings"))
			{
				ReadRCSettings();
				GetStyleSettings();

				if(inSlit && hSlit)
				{
					SetWindowModes();
					SendMessage(hSlit, SLIT_UPDATE, NULL, NULL);
				}
				else if(!inSlit || !hSlit)
					SendMessage(hSlit, SLIT_REMOVE, NULL, (LPARAM)hwndPlugin);

				else inSlit = false;
			}
			else if (!_stricmp(szTemp, "SaveSettings"))
			{
				WriteRCSettings();
			}
		}
		break;

		// ==========

		case WM_WINDOWPOSCHANGING:
		{
			// Is SnapWindowToEdge enabled?
			if (!inSlit && snapWindow)
			{
				// Snap window to screen edges (if the last bool is false it uses the current DesktopArea)
				if(IsWindowVisible(hwnd)) SnapWindowToEdge((WINDOWPOS*)lParam, 10, true);
			}
		}
		break;

		// ==========

		case WM_WINDOWPOSCHANGED:
		{
			if(!inSlit)
			{
				WINDOWPOS* windowpos = (WINDOWPOS*)lParam;
				if (0 == (windowpos->flags & SWP_NOMOVE))
				{
					xpos = windowpos->x;
					ypos = windowpos->y;
				}

				if(ResizeMyWindow(windowpos->cx, windowpos->cy) && 0 == (windowpos->flags & SWP_NOSIZE))
				{
					track_needsupdate = true;
					knob_needsupdate = true;
					InvalidateRect(hwndPlugin, NULL, true);
				}
			}
		}
		break;

		// ==========

		case WM_NCHITTEST:
		{
			if (!inSlit && GetKeyState(VK_MENU) & 0xF0)
			{
				return HTBOTTOMRIGHT;
			}
			else
			if (!inSlit && GetKeyState(VK_CONTROL) & 0xF0)
			{
				return HTCAPTION;
			}
		}
		return HTCLIENT;

		// ==========

		case WM_LBUTTONDOWN:
			SetFocus(hwnd);
			SetCapture(hwnd);

			InvalidateRect(hwndPlugin, NULL, false);
			dragging = true;
			SliderOnValueChange(lParam);
			break;
	
		case WM_MOUSEMOVE:
			if (!dragging) break;
			InvalidateRect(hwndPlugin, NULL, false);
			SliderOnValueChange(lParam);
			break;

		case WM_LBUTTONUP:
			ReleaseCapture();

		case WM_KILLFOCUS: 
			dragging = false;
			break;

		// ==========

		case WM_RBUTTONUP:
			ReleaseCapture();

		case WM_NCRBUTTONUP:
			ShowMyMenu(true);
			break;

		case WM_CLOSE:
			break;

		// bring window into foreground on sizing/moving-start
		case WM_NCLBUTTONDOWN:
			SetWindowPos(hwnd, HWND_TOP, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
			UpdateWindow(hwnd);
			// fall through
 		// ==========
		default:
			return DefWindowProc(hwnd,message,wParam,lParam);
	}
	return 0;
}