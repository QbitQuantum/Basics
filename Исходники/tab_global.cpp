	static BOOL CALLBACK ConfigProc(HWND wnd, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
		case WM_INITDIALOG:
		{
			uTCITEM tabs;
			memset(&tabs, 0, sizeof(tabs));

			HWND wnd_tab = GetDlgItem(wnd, IDC_TAB1);

			tabs.mask = TCIF_TEXT;
			tabs.pszText = "Variables";
			uTabCtrl_InsertItem(wnd_tab, 0, &tabs);
			tabs.pszText = "Style";
			uTabCtrl_InsertItem(wnd_tab, 1, &tabs);

			TabCtrl_SetCurSel(wnd_tab, g_cur_tab2);

			uSendDlgItemMessageText(wnd, IDC_CHAR7, WM_SETTEXT, 0, "\x07");
			colour_code_gen(wnd, IDC_COLOUR, false, true);

			uSendDlgItemMessage(wnd, IDC_STRING, EM_LIMITTEXT, 0, 0);

			refresh_me(wnd);
			editproc = (WNDPROC)SetWindowLongPtr(GetDlgItem(wnd, IDC_STRING), GWLP_WNDPROC, (LPARAM)EditHook);

			g_editor_font_notify.set(GetDlgItem(wnd, IDC_STRING));
		}

		break;

		case WM_NOTIFY:
			switch (((LPNMHDR)lp)->idFrom)
			{
			case IDC_TAB1:
				switch (((LPNMHDR)lp)->code)
				{
				case TCN_SELCHANGE:
				{
					save_string(wnd);
					int id = TabCtrl_GetCurSel(GetDlgItem(wnd, IDC_TAB1));
					g_cur_tab2 = id;
					uSendDlgItemMessageText(wnd, IDC_STRING, WM_SETTEXT, 0, (g_cur_tab2 == 0 ? cfg_globalstring : cfg_colour));
				}
				break;
				}
				break;
			}
			break;

		case WM_DESTROY:
		{
			g_editor_font_notify.release();
			save_string(wnd);
			refresh_all_playlist_views();
			pvt::ng_playlist_view_t::g_update_all_items();
		}
		break;

		case WM_COMMAND:
			switch (wp)
			{
			case IDC_GLOBAL:
				cfg_global = uSendMessage((HWND)lp, BM_GETCHECK, 0, 0);
				break;
			case IDC_DATE:
				cfg_playlist_date = uSendMessage((HWND)lp, BM_GETCHECK, 0, 0);
				set_day_timer();
				pvt::ng_playlist_view_t::g_on_use_date_info_change();
				break;
			case IDC_TFHELP:
			{
				RECT rc;
				GetWindowRect(GetDlgItem(wnd, IDC_TFHELP), &rc);
				//		MapWindowPoints(HWND_DESKTOP, wnd, (LPPOINT)(&rc), 2);
				HMENU menu = CreatePopupMenu();


				enum { IDM_TFHELP = 1, IDM_GHELP = 2, IDM_SPEEDTEST, IDM_PREVIEW, IDM_EDITORFONT, IDM_RESETSTYLE };

				uAppendMenu(menu, (MF_STRING), IDM_TFHELP, "Titleformatting &help");
				uAppendMenu(menu, (MF_STRING), IDM_GHELP, "&Global help");
				uAppendMenu(menu, (MF_SEPARATOR), 0, "");
				uAppendMenu(menu, (MF_STRING), IDM_SPEEDTEST, "&Speed test");
				uAppendMenu(menu, (MF_STRING), IDM_PREVIEW, "&Preview to console");
				uAppendMenu(menu, (MF_SEPARATOR), 0, "");
				uAppendMenu(menu, (MF_STRING), IDM_EDITORFONT, "Change editor &font");
				uAppendMenu(menu, (MF_SEPARATOR), 0, "");
				uAppendMenu(menu, (MF_STRING), IDM_RESETSTYLE, "&Reset style string");


				int cmd = TrackPopupMenu(menu, TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD, rc.left, rc.bottom, 0, wnd, 0);
				DestroyMenu(menu);
				if (cmd == IDM_TFHELP)
				{
					standard_commands::main_titleformat_help();
				}
				else if (cmd == IDM_GHELP)
				{
					uMessageBox(wnd, COLOUR_HELP "\n\nNew global format: $set_global(var, val), retreive values using $get_global(var)", "Global help", 0);
				}
				else if (cmd == IDM_SPEEDTEST)
				{
					speedtest(g_columns, cfg_global != 0, cfg_oldglobal != 0, cfg_playlist_date != 0);
				}
				else if (cmd == IDM_PREVIEW)
				{
					preview_to_console(string_utf8_from_window(wnd, IDC_STRING), g_cur_tab2 != 0 && cfg_global);
				}
				else if (cmd == IDM_EDITORFONT)
				{
					if (font_picker(wnd, cfg_editor_font))
						g_editor_font_notify.on_change();
				}
				else if (cmd == IDM_RESETSTYLE)
				{
					extern const char * g_default_colour;
					cfg_colour = g_default_colour;
					if (g_cur_tab2 == 1)
						uSendDlgItemMessageText(wnd, IDC_STRING, WM_SETTEXT, 0, cfg_colour);
					refresh_all_playlist_views();
					pvt::ng_playlist_view_t::g_update_all_items();
				}
			}


			break;
			case IDC_OLDGLOBAL:
				cfg_oldglobal = uSendMessage((HWND)lp, BM_GETCHECK, 0, 0);
				break;
			case IDC_GLOBALSORT:
				cfg_global_sort = uSendMessage((HWND)lp, BM_GETCHECK, 0, 0);
				break;
			case IDC_APPLY:
				save_string(wnd);
				refresh_all_playlist_views();
				pvt::ng_playlist_view_t::g_update_all_items();
				break;
			case IDC_PICK_COLOUR:
				colour_code_gen(wnd, IDC_COLOUR, false, false);
				break;
			}
		}
		return 0;
	}