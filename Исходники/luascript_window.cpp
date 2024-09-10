LRESULT CALLBACK LuaScriptProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RECT r;
	RECT r2;
	int dx1, dy1, dx2, dy2;

	switch(uMsg)
	{
		case WM_INITDIALOG: {
			if(std::find(LuaScriptHWnds.begin(), LuaScriptHWnds.end(), hDlg) == LuaScriptHWnds.end())
			{
				LuaScriptHWnds.push_back(hDlg);
				Build_Main_Menu();
			}
			if (Full_Screen)
			{
				while (ShowCursor(false) >= 0);
				while (ShowCursor(true) < 0);
			}

			HANDLE hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_LUA));
			SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

			// remove the 30000 character limit from the console control
			SendMessage(GetDlgItem(hDlg, IDC_LUACONSOLE),EM_LIMITTEXT,0,0);

			GetWindowRect(HWnd, &r);
			dx1 = (r.right - r.left) / 2;
			dy1 = (r.bottom - r.top) / 2;

			GetWindowRect(hDlg, &r2);
			dx2 = (r2.right - r2.left) / 2;
			dy2 = (r2.bottom - r2.top) / 2;

			int windowIndex = std::find(LuaScriptHWnds.begin(), LuaScriptHWnds.end(), hDlg) - LuaScriptHWnds.begin();
			int staggerOffset = windowIndex * 24;
			r.left += staggerOffset;
			r.right += staggerOffset;
			r.top += staggerOffset;
			r.bottom += staggerOffset;

			// push it away from the main window if we can
			const int width = (r.right-r.left); 
			const int width2 = (r2.right-r2.left); 
			if(r.left+width2 + width < GetSystemMetrics(SM_CXSCREEN))
			{
				r.right += width;
				r.left += width;
			}
			else if((int)r.left - (int)width2 > 0)
			{
				r.right -= width2;
				r.left -= width2;
			}

			SetWindowPos(hDlg, NULL, r.left, r.top, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);

			LuaPerWindowInfo info;
			{
				RECT r3;
				GetClientRect(hDlg, &r3);
				info.width = r3.right - r3.left;
				info.height = r3.bottom - r3.top;
			}
			LuaWindowInfo[hDlg] = info;
			RegisterWatcherThread(hDlg);

			OpenLuaContext((int)hDlg, PrintToWindowConsole, OnStart, OnStop);

			DragAcceptFiles(hDlg, TRUE);

			return true;
		}	break;

		case WM_MENUSELECT:
 		case WM_ENTERSIZEMOVE:
			Clear_Sound_Buffer();
			break;

		case WM_SIZING:
			{
				// enforce a minimum window size

				LPRECT r = (LPRECT) lParam;
				int minimumWidth = 333;
				int minimumHeight = 117;
				if(r->right - r->left < minimumWidth)
					if(wParam == WMSZ_LEFT || wParam == WMSZ_TOPLEFT || wParam == WMSZ_BOTTOMLEFT)
						r->left = r->right - minimumWidth;
					else
						r->right = r->left + minimumWidth;
				if(r->bottom - r->top < minimumHeight)
					if(wParam == WMSZ_TOP || wParam == WMSZ_TOPLEFT || wParam == WMSZ_TOPRIGHT)
						r->top = r->bottom - minimumHeight;
					else
						r->bottom = r->top + minimumHeight;
			}
			return TRUE;

		case WM_SIZE:
			{
				// resize or move controls in the window as necessary when the window is resized

				LuaPerWindowInfo& windowInfo = LuaWindowInfo[hDlg];
				int prevDlgWidth = windowInfo.width;
				int prevDlgHeight = windowInfo.height;

				int dlgWidth = LOWORD(lParam);
				int dlgHeight = HIWORD(lParam);

				int deltaWidth = dlgWidth - prevDlgWidth;
				int deltaHeight = dlgHeight - prevDlgHeight;

				for(int i = 0; i < numControlLayoutInfos; i++)
				{
					ControlLayoutInfo layoutInfo = controlLayoutInfos[i];
					ControlLayoutState& layoutState = windowInfo.layoutState[i];

					HWND hCtrl = GetDlgItem(hDlg,layoutInfo.controlID);

					int x,y,width,height;
					if(layoutState.valid)
					{
						x = layoutState.x;
						y = layoutState.y;
						width = layoutState.width;
						height = layoutState.height;
					}
					else
					{
						RECT r;
						GetWindowRect(hCtrl, &r);
						POINT p = {r.left, r.top};
						ScreenToClient(hDlg, &p);
						x = p.x;
						y = p.y;
						width = r.right - r.left;
						height = r.bottom - r.top;
					}

					switch(layoutInfo.horizontalLayout)
					{
						case ControlLayoutInfo::RESIZE_END: width += deltaWidth; break;
						case ControlLayoutInfo::MOVE_START: x += deltaWidth; break;
						default: break;
					}
					switch(layoutInfo.verticalLayout)
					{
						case ControlLayoutInfo::RESIZE_END: height += deltaHeight; break;
						case ControlLayoutInfo::MOVE_START: y += deltaHeight; break;
						default: break;
					}

					SetWindowPos(hCtrl, 0, x,y, width,height, 0);

					layoutState.x = x;
					layoutState.y = y;
					layoutState.width = width;
					layoutState.height = height;
					layoutState.valid = true;
				}

				windowInfo.width = dlgWidth;
				windowInfo.height = dlgHeight;

				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE);
			}
			break;

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case IDC_BUTTON_LUABROWSE:
				{
					LuaPerWindowInfo& info = LuaWindowInfo[hDlg];
					char Str_Tmp [1024]; // shadow added because the global one is unreliable
					strcpy(Str_Tmp,info.filename.c_str());
					SendDlgItemMessage(hDlg,IDC_EDIT_LUAPATH,WM_GETTEXT,(WPARAM)512,(LPARAM)Str_Tmp);
					char* bar = strchr(Str_Tmp, '|');
					if(bar) *bar = '\0';
					DialogsOpen++;
					Clear_Sound_Buffer();
					if(Change_File_L(Str_Tmp, Lua_Dir, "Load Lua Script", "Gens Lua Script\0*.lua*\0All Files\0*.*\0\0", "lua", hDlg))
					{
						SendDlgItemMessage(hDlg,IDC_EDIT_LUAPATH,WM_SETTEXT,0,(LPARAM)Str_Tmp);
					}
					DialogsOpen--;

				}	break;
				case IDC_BUTTON_LUAEDIT:
				{
					LuaPerWindowInfo& info = LuaWindowInfo[hDlg];
					char Str_Tmp [1024]; // shadow added because the global one is unreliable
					strcpy(Str_Tmp,info.filename.c_str());
					SendDlgItemMessage(hDlg,IDC_EDIT_LUAPATH,WM_GETTEXT,(WPARAM)512,(LPARAM)Str_Tmp);
					char LogicalName[1024], PhysicalName[1024];
					bool exists = ObtainFile(Str_Tmp, LogicalName, PhysicalName, "luaview", s_nonLuaExtensions, sizeof(s_nonLuaExtensions)/sizeof(*s_nonLuaExtensions));
					bool created = false;
					if(!exists)
					{
						FILE* file = fopen(Str_Tmp, "r");
						if(!file)
						{
							file = fopen(Str_Tmp, "w");
							if(file)
							{
								created = true;
								exists = true;
								strcpy(PhysicalName, Str_Tmp);
							}
						}
						if(file)
							fclose(file);
					}
					if(exists)
					{
						// tell the OS to open the file with its associated editor,
						// without blocking on it or leaving a command window open.
						if((int)ShellExecute(NULL, "edit", PhysicalName, NULL, NULL, SW_SHOWNORMAL) == SE_ERR_NOASSOC)
							if((int)ShellExecute(NULL, "open", PhysicalName, NULL, NULL, SW_SHOWNORMAL) == SE_ERR_NOASSOC)
								ShellExecute(NULL, NULL, "notepad", PhysicalName, NULL, SW_SHOWNORMAL);
					}
					if(created)
					{
						UpdateFileEntered(hDlg);
					}
				}	break;
				case IDC_EDIT_LUAPATH:
				{
					switch(HIWORD(wParam))
					{
						case EN_CHANGE:
						{
							UpdateFileEntered(hDlg);
						}	break;
					}
				}	break;
				case IDC_BUTTON_LUARUN:
				{
					HWND focus = GetFocus();
					HWND textbox = GetDlgItem(hDlg, IDC_EDIT_LUAPATH);
					if(focus != textbox)
						SetActiveWindow(HWnd);

					LuaPerWindowInfo& info = LuaWindowInfo[hDlg];
					char Str_Tmp [1024]; // shadow added because the global one is completely unreliable
					strcpy(Str_Tmp,info.filename.c_str());
					char LogicalName[1024], PhysicalName[1024];
					bool exists = ObtainFile(Str_Tmp, LogicalName, PhysicalName, "luarun", s_nonLuaExtensions, sizeof(s_nonLuaExtensions)/sizeof(*s_nonLuaExtensions));
					Update_Recent_Script(LogicalName, info.subservient);
					RunLuaScriptFile((int)hDlg, PhysicalName);
				}	break;
				case IDC_BUTTON_LUASTOP:
				{
					PrintToWindowConsole((int)hDlg, "user clicked stop button\r\n");
					SetActiveWindow(HWnd);
					StopLuaScript((int)hDlg);
				}	break;
				case IDC_NOTIFY_SUBSERVIENT:
				{
					LuaPerWindowInfo& info = LuaWindowInfo[hDlg];
					info.subservient = lParam ? true : false;
				}	break;
				//case IDOK:
				case IDCANCEL:
				{	LuaPerWindowInfo& info = LuaWindowInfo[hDlg];
					if(info.filename.empty())
					{
						if (Full_Screen)
						{
							while (ShowCursor(true) < 0);
							while (ShowCursor(false) >= 0);
						}
						DialogsOpen--;
						DragAcceptFiles(hDlg, FALSE);
						KillWatcherThread(hDlg);
						LuaScriptHWnds.erase(remove(LuaScriptHWnds.begin(), LuaScriptHWnds.end(), hDlg), LuaScriptHWnds.end());
						LuaWindowInfo.erase(hDlg);
						CloseLuaContext((int)hDlg);
						Build_Main_Menu();
						EndDialog(hDlg, true);
					}
				}	return true;
			}

			return false;
		}	break;

		case WM_CLOSE:
		{
			LuaPerWindowInfo& info = LuaWindowInfo[hDlg];

			PrintToWindowConsole((int)hDlg, "user closed script window\r\n");
			StopLuaScript((int)hDlg);
			if(info.started)
			{
				// not stopped yet, wait to close until we are, otherwise we'll crash
				info.closeOnStop = true;
				return false;
			}

			if (Full_Screen)
			{
				while (ShowCursor(true) < 0);
				while (ShowCursor(false) >= 0);
			}
			DialogsOpen--;
			DragAcceptFiles(hDlg, FALSE);
			KillWatcherThread(hDlg);
			LuaScriptHWnds.erase(remove(LuaScriptHWnds.begin(), LuaScriptHWnds.end(), hDlg), LuaScriptHWnds.end());
			LuaWindowInfo.erase(hDlg);
			CloseLuaContext((int)hDlg);
			Build_Main_Menu();
			EndDialog(hDlg, true);
		}	return true;

		case WM_DROPFILES:
		{
			HDROP hDrop = (HDROP)wParam;
			DragQueryFile(hDrop, 0, Str_Tmp, 1024);
			DragFinish(hDrop);
			SendDlgItemMessage(hDlg,IDC_EDIT_LUAPATH,WM_SETTEXT,0,(LPARAM)Str_Tmp );
			UpdateFileEntered(hDlg);
		}	return true;
	}

	return false;
}