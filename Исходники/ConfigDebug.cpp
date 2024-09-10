static BOOL CALLBACK DialogProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	int wmId;
	//wchar_t temp[384]={0};

	switch(uMsg)
	{
		case WM_PAINT:
			return FALSE;

		case WM_INITDIALOG:
		{
			EnableControls( hWnd );

			// Debugging / Logging Flags:
			SET_CHECK(IDC_DEBUG,   DebugEnabled);
			SET_CHECK(IDC_MSGSHOW, _MsgToConsole);
			SET_CHECK(IDC_MSGKEY,  _MsgKeyOnOff);
			SET_CHECK(IDC_MSGVOICE,_MsgVoiceOff);
			SET_CHECK(IDC_MSGDMA,  _MsgDMA);
			SET_CHECK(IDC_MSGADMA, _MsgAutoDMA);
			SET_CHECK(IDC_DBG_OVERRUNS, _MsgOverruns );
			SET_CHECK(IDC_DBG_CACHE, _MsgCache );
			SET_CHECK(IDC_LOGREGS, _AccessLog);
			SET_CHECK(IDC_LOGDMA,  _DMALog);
			SET_CHECK(IDC_LOGWAVE, _WaveLog);
			SET_CHECK(IDC_DUMPCORE,_CoresDump);
			SET_CHECK(IDC_DUMPMEM, _MemDump);
			SET_CHECK(IDC_DUMPREGS,_RegDump);
			SET_CHECK(IDC_DEBUG_VISUAL,_visual_debug_enabled);

			ShowWindow( GetDlgItem( hWnd, IDC_MSG_PUBLIC_BUILD ), !IsDevBuild );
		}
		break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
				case IDOK:
					WriteSettings();
					EndDialog(hWnd,0);
				break;

				case IDCANCEL:
					EndDialog(hWnd,0);
				break;

				HANDLE_CHECKNB(IDC_MSGSHOW,_MsgToConsole);
					EnableMessages( hWnd );
				break;

				HANDLE_CHECK(IDC_MSGKEY,_MsgKeyOnOff);
				HANDLE_CHECK(IDC_MSGVOICE,_MsgVoiceOff);
				HANDLE_CHECK(IDC_MSGDMA,_MsgDMA);
				HANDLE_CHECK(IDC_MSGADMA,_MsgAutoDMA);
				break;

				HANDLE_CHECK(IDC_DBG_OVERRUNS,_MsgOverruns);
				HANDLE_CHECK(IDC_DBG_CACHE,_MsgCache);
				HANDLE_CHECK(IDC_LOGREGS,_AccessLog);
				HANDLE_CHECK(IDC_LOGDMA, _DMALog);
				HANDLE_CHECK(IDC_LOGWAVE,_WaveLog);
				HANDLE_CHECK(IDC_DUMPCORE,_CoresDump);
				HANDLE_CHECK(IDC_DUMPMEM, _MemDump);
				HANDLE_CHECK(IDC_DUMPREGS,_RegDump);
				HANDLE_CHECK(IDC_DEBUG_VISUAL,_visual_debug_enabled);
				default:
					return FALSE;
			}
		break;

		default:
			return FALSE;
	}
	return TRUE;

}