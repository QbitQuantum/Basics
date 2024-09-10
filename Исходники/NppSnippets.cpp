extern "C" __declspec(dllexport) void beNotified(SCNotification* notifyCode)
{
	switch (notifyCode->nmhdr.code)
	{
		case NPPN_READY:
		{
			// Initialize the database
			g_db = new SnippetsDB();

			if (g_Options->showConsoleDlg)
				SnippetsConsole();

			// Check if we are running a newer version
			Version curVer, prevVer(g_Options->GetPrevVersion());
			if (curVer > prevVer)
				g_Options->Write();
			break;
		}

		case NPPN_SHUTDOWN:
		{
			break;
		}

		case NPPN_TBMODIFICATION:
		{
			// First initialize the options
			g_Options = new Options();

			// Do we need to load the toolbar icon?
			if (g_Options->toolbarIcon)
			{
				// Add the button to the toolbar
				toolbarIcons tbiFolder;
				hbmpToolbar = CreateMappedBitmap(g_hInst, IDB_SNIPPETS, 0, 0, 0);
				tbiFolder.hToolbarBmp = hbmpToolbar;
				tbiFolder.hToolbarIcon = NULL;
				SendMessage((HWND) notifyCode->nmhdr.hwndFrom, NPPM_ADDTOOLBARICON, (WPARAM) g_funcItem[0]._cmdID, (LPARAM) &tbiFolder);
			}
			break;
		}

		case NPPN_LANGCHANGED:
		case NPPN_BUFFERACTIVATED:
		{
			LangType lang;
			SendMessage(g_nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM) &lang);
			if (g_currentLang != lang)
			{
				g_currentLang = lang;
				UpdateSnippetsList();
			}
			break;
		}

		case NPPN_WORDSTYLESUPDATED:
		{
			InvalidateListbox();
			break;
		}
	}
}