LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	//sprintf_s(s_buf, "GetMsgProc\n");
	//WriteConsole(s_out, s_buf, strlen(s_buf), &s_ccount, 0);
	if (!s_initialized)
	{
		if (!AttachConsole(g_consoleId))
		{
			FreeConsole();
			AttachConsole(g_consoleId);
		}
		s_out = GetStdHandle(STD_OUTPUT_HANDLE); // TODO: we don't really close it
		sprintf_s(s_buf, "Attached console\n");
		WriteConsole(s_out, s_buf, strlen(s_buf), &s_ccount, 0);

		if (!g_mouseHook)
		{
			g_mouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, g_this, 0); // mouse_ll global only (requires process with message loop)
			if (g_mouseHook)
			{
				sprintf_s(s_buf, "Installed mouse hook\n");
				WriteConsole(s_out, s_buf, strlen(s_buf), &s_ccount, 0);
			}
			else
			{
				sprintf_s(s_buf, "Could not install mouse hook\n");
				WriteConsole(s_out, s_buf, strlen(s_buf), &s_ccount, 0);
			}
		}

		if (g_detect_screen_size)
		{
			HWND win = GetDesktopWindow();
			RECT rec;
			GetWindowRect(win, &rec);
			g_screen_height = rec.bottom;
			g_screen_width = rec.right;
		}

		sprintf_s(s_buf, "X-Offset: %i Y-Offset: %i Width: %i Height: %i\n", g_screen_offsetX, g_screen_offsetY, g_screen_width, g_screen_height);
		WriteConsole(s_out, s_buf, strlen(s_buf), &s_ccount, 0);

		s_cursors.reset(new CursorMap);
		s_cursorBuf.reset(new CursorMap);

		s_server.reset(new TUIO::TuioServer(g_host, g_serverPort));
		sprintf_s(s_buf, "Created server (%s:%i)\n", g_host, g_serverPort);
		WriteConsole(s_out, s_buf, strlen(s_buf), &s_ccount, 0);

		s_timer = SetTimer(g_targetWnd, TIMER_IDENTIFIER, TIMER_CALL_TIME, 0);

		s_initialized = true;
	}

	if (nCode < 0) // do not process message 
	{
		return CallNextHookEx(0, nCode, wParam, lParam);
	}

	switch (nCode) 
	{ 
	case HC_ACTION: 
		{
			LPMSG msg = (LPMSG)lParam;

			// register everything for touch
			// Note: pretty ugly but seems to be the only possibility to register every window
			RegisterTouchWindow(msg->hwnd, TOUCH_FLAGS);

			switch (msg->message)
			{
			case WM_TOUCH:
				{
					//sprintf_s(s_buf, "Touches received:\n");
					//WriteConsole(s_out, s_buf, strlen(s_buf), &s_ccount, 0);

					UINT cInputs = LOWORD(msg->wParam);
					PTOUCHINPUT pInputs = new TOUCHINPUT[cInputs];
					if (NULL != pInputs)
					{
						if (GetTouchInputInfo((HTOUCHINPUT)msg->lParam,
							cInputs,
							pInputs,
							sizeof(TOUCHINPUT)))
						{
							s_server->initFrame(TUIO::TuioTime::getSessionTime());

							// process pInputs
							for (UINT i=0; i<cInputs; ++i)
							{
								//sprintf_s(s_buf, "ID: %i, X: %i, Y: %i\n", pInputs[i].dwID, pInputs[i].x, pInputs[i].y);
								//WriteConsole(s_out, s_buf, strlen(s_buf), &s_ccount, 0);

								std::map<DWORD, TUIO::TuioCursor*>::iterator cursorIt = s_cursors->find(pInputs[i].dwID);
								if (cursorIt != s_cursors->end())
								{
									// found
									s_server->updateTuioCursor(cursorIt->second,
															   ((pInputs[i].x*0.01f)+g_screen_offsetX)/(float)(g_screen_width+g_screen_offsetX),
															   ((pInputs[i].y*0.01f)+g_screen_offsetY)/(float)(g_screen_height+g_screen_offsetY));
									(*s_cursorBuf)[pInputs[i].dwID] = cursorIt->second;
									s_cursors->erase(cursorIt);
								}
								else
								{
									// not found
									(*s_cursorBuf)[pInputs[i].dwID] = s_server->addTuioCursor(
															((pInputs[i].x*0.01f)+g_screen_offsetX)/(float)(g_screen_width+g_screen_offsetX),
															((pInputs[i].y*0.01f)+g_screen_offsetY)/(float)(g_screen_height+g_screen_offsetY));
								}
							}
							
							for (std::map<DWORD, TUIO::TuioCursor*>::iterator it = s_cursors->begin(); it != s_cursors->end(); ++it)
							{
								s_server->removeTuioCursor(it->second);
							}
							
							s_cursors->clear();
							std::auto_ptr<CursorMap> tmp(s_cursorBuf);
							s_cursorBuf = s_cursors;
							s_cursors = tmp;	
							s_server->commitFrame();
						}
					}
					delete[] pInputs;
				}
				break;
			case WM_TIMER:
				{
					//if (msg->wParam == TIMER_IDENTIFIER)
					//{
						BOOL frameOpen(false);
						for (std::map<DWORD, TUIO::TuioCursor*>::iterator it = s_cursors->begin(); it != s_cursors->end();)
						{
							long delta = TUIO::TuioTime::getSessionTime().getTotalMilliseconds() - it->second->getTuioTime().getTotalMilliseconds();
							if (delta > MAX_CURSOR_IDLE_TIME)
							{
								if (!frameOpen)
								{
									s_server->initFrame(TUIO::TuioTime::getSessionTime());
									frameOpen = true;
								}
								s_server->removeTuioCursor(it->second);
								std::map<DWORD, TUIO::TuioCursor*>::iterator tmp = it++;
								s_cursors->erase(tmp);
								//sprintf_s(s_buf, "Removed cursor due to time limit\n");
								//WriteConsole(s_out, s_buf, strlen(s_buf), &s_ccount, 0);
							}
							else
							{
								++it;
							}
						}
						if (frameOpen)
						{
							s_server->commitFrame();
						}
					//}
				}
				break;
			}
		}
		break; 
	}

	return CallNextHookEx(0, nCode, wParam, lParam); 
}