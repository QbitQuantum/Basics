static LRESULT CALLBACK ToolbarParentWndProc(HWND hDlg, 
											 UINT msg,
											 WPARAM wParam, 
											 LPARAM lParam)
{
	WNDPROC lpOldProc;
	PluginInfo *plugin;
	LPNMHDR lpnm;
	LPNMTOOLBAR lptb;

	lpOldProc = (WNDPROC)GetProp( hDlg, "oldproc" );
	plugin = GetPluginInfo(hDlg);

	lpnm = (LPNMHDR) lParam;
	lptb = (LPNMTOOLBAR) lParam;

	switch(msg)
	{
	case WM_NOTIFY:
		{
			int nIndex;

			if (lpnm->code == TBN_BEGINADJUST)
			{
				nIndex = SendMessage(plugin->hToolbar, TB_COMMANDTOINDEX,
							IDC_PGPKEYS, 0);

				SendMessage(plugin->hToolbar, TB_DELETEBUTTON, nIndex, 0);
				plugin->nPGPKeysButton = -1;
			}

			if (lpnm->code == TBN_ENDADJUST)
			{
				TBBUTTON tbb[1];
				HIMAGELIST hilToolbar;
				int nX;
				int nY;
				LRESULT lResult;
				
				lResult = CallWindowProc(lpOldProc, hDlg, msg, wParam, 
							lParam);

				hilToolbar = (HIMAGELIST) SendMessage(plugin->hToolbar, 
											TB_GETIMAGELIST, 0, 0);

				ImageList_GetIconSize(hilToolbar, &nX, &nY);
				if ((nX < 20) && !(plugin->bSmallIcons))
					AddMainToolbarButtons(plugin);
				else if ((nX > 20) && plugin->bSmallIcons)
					AddMainToolbarButtons(plugin);
				else
				{
					tbb[0].iBitmap = plugin->nPGPKeysImage;
					tbb[0].idCommand = IDC_PGPKEYS;
					tbb[0].fsState = TBSTATE_ENABLED;
					tbb[0].fsStyle = TBSTYLE_BUTTON;
					tbb[0].dwData = 0;
					tbb[0].iString = plugin->nPGPKeysString;
					
					SendMessage(plugin->hToolbar, TB_ADDBUTTONS, 1, 
						(LPARAM) &tbb);
					
					plugin->nPGPKeysButton = SendMessage(plugin->hToolbar,
												TB_COMMANDTOINDEX,
												IDC_PGPKEYS,
												0);
				}

				return lResult;
			}

			break;
		}
	}

	return CallWindowProc(lpOldProc, hDlg, msg, wParam, lParam);
}