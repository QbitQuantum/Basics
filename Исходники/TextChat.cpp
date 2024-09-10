BOOL CALLBACK TextChat::TextChatDlgProc(  HWND hWnd,  UINT uMsg,  WPARAM wParam, LPARAM lParam )
{

	TextChat* _this = (TextChat *) GetWindowLong(hWnd, GWL_USERDATA);

	switch (uMsg)
	{

	case WM_INITDIALOG:
		{
			SetWindowLong(hWnd, GWL_USERDATA, lParam);
            TextChat *_this = (TextChat *) lParam;
			if (_this->m_szLocalText == NULL || _this->m_szRemoteText == NULL)
				EndDialog(hWnd, FALSE);

			// Window always on top if Fullscreen On
			if (_this->m_pCC->InFullScreenMode())
			{
				RECT Rect;
				GetWindowRect(hWnd, &Rect);
				SetWindowPos(hWnd, 
							HWND_TOPMOST,
							Rect.left,
							Rect.top,
							Rect.right - Rect.left,
							Rect.bottom - Rect.top,
							SWP_SHOWWINDOW);
			}

            // CentreWindow(hWnd);
			_this->m_hWnd = hWnd;
			_this->m_hDlg = hWnd;
			
			if (_snprintf(_this->m_szRemoteName,MAXNAMESIZE-1,"%s", _this->m_pCC->m_desktopName) < 0 )
			{
				_this->m_szRemoteName[MAXNAMESIZE-4]='.';
				_this->m_szRemoteName[MAXNAMESIZE-3]='.';
				_this->m_szRemoteName[MAXNAMESIZE-2]='.';
				_this->m_szRemoteName[MAXNAMESIZE-1]=0x00;
			}	
			

			const long lTitleBufSize=256;			
			char szTitle[lTitleBufSize];
			
			_snprintf(szTitle,lTitleBufSize-1," Chat with <%s> - Ultr@VNC",_this->m_szRemoteName);
			SetWindowText(hWnd, szTitle);			

			// Trunc the remote name for display in Chat Area before the first parenthesis, if any.
			char *p = strchr(_this->m_szRemoteName, '('); 
			if (p != NULL) *(p - 1) = '\0';

			//  Chat area			
			_this->SetTextFormat(); //  Set character formatting and background color
			SendDlgItemMessage( hWnd, IDC_CHATAREA_EDIT, EM_SETBKGNDCOLOR, FALSE, 0xFFFFFF ); 

			memset(_this->m_szLocalText, 0, TEXTMAXSIZE);
			// if (!_this->m_fPersistentTexts)
			{
				memset(_this->m_szLastLocalText, 0, TEXTMAXSIZE);
				memset(_this->m_szTextBoxBuffer, 0, TEXTMAXSIZE); // Clear Chat area 
				 //  Load and display diclaimer message
				// sf@2005 - Only if the DSMplugin is used
				if (!_this->m_pCC->m_fUsePlugin)
				{
					if (LoadString(_this->m_pApp->m_instance, IDS_WARNING, _this->m_szRemoteText, TEXTMAXSIZE -1) )
						_this->PrintMessage(_this->m_szRemoteText, NULL ,GREY);
				}
			}

			SetDlgItemText(hWnd, IDC_INPUTAREA_EDIT, _this->m_szLocalText);
			SetDlgItemText(hWnd, IDC_CHATAREA_EDIT, _this->m_szTextBoxBuffer); // Chat area

			// Scroll down the chat window
			// The following seems necessary under W9x & Me if we want the Edit to scroll to bottom...
			SCROLLINFO si;
			ZeroMemory(&si, sizeof(SCROLLINFO));
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_RANGE|SIF_PAGE;
			GetScrollInfo(GetDlgItem(hWnd, IDC_CHATAREA_EDIT), SB_VERT, &si);
			si.nPos = si.nMax - max(si.nPage - 1, 0);
			SendDlgItemMessage(hWnd, IDC_CHATAREA_EDIT, WM_VSCROLL, MAKELONG(SB_THUMBPOSITION, si.nPos), 0L);	
			// This line does the bottom scrolling correctly under NT4,W2K, XP...
			// SendDlgItemMessage(m_hDlg, IDC_CHATAREA_EDIT, WM_VSCROLL, SB_BOTTOM, 0L);

			// SendDlgItemMessage(hWnd, IDC_PERSISTENT_CHECK, BM_SETCHECK, _this->m_fPersistentTexts, 0);

			// Tell the other side to open the TextChat Window
			_this->SendTextChatRequest(CHAT_OPEN);

			SetForegroundWindow(hWnd);
			
			return TRUE;
		}
		// break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		/*
		case IDC_PERSISTENT_CHECK:
		    _this->m_fPersistentTexts = (SendDlgItemMessage(hWnd, IDC_PERSISTENT_CHECK, BM_GETCHECK, 0, 0) == BST_CHECKED);
			return TRUE;
		*/

		case IDOK:
			// Server orders to close TextChat 			
			EndDialog(hWnd, FALSE);
			return TRUE;

		case IDCANCEL:			
			_this->SendTextChatRequest(CHAT_CLOSE); // Server must close TextChat
			EndDialog(hWnd, FALSE);
			return TRUE;

		case IDC_SEND_B:
			{
			memset(_this->m_szLocalText,0,TEXTMAXSIZE);
			UINT nRes = GetDlgItemText( hWnd, IDC_INPUTAREA_EDIT, _this->m_szLocalText, TEXTMAXSIZE-1);
			strcat(_this->m_szLocalText, "\n");
			_this->SendLocalText();		
			SetFocus(GetDlgItem(hWnd, IDC_INPUTAREA_EDIT));
			}
			return TRUE;

		case IDC_HIDE_B:
			_this->ShowChatWindow(false);
			return TRUE;

		case IDC_INPUTAREA_EDIT:
			if(HIWORD(wParam) == EN_UPDATE)			
			{
				memset(_this->m_szLocalText,0,TEXTMAXSIZE);
				UINT nRes = GetDlgItemText( hWnd, IDC_INPUTAREA_EDIT, _this->m_szLocalText, TEXTMAXSIZE);
				if (strstr(_this->m_szLocalText,"\n") >0 ) 
				{
					_this->SendLocalText();			
				}								
			}
			return TRUE;
		}
		break;

	case WM_SYSCOMMAND:
		switch (LOWORD(wParam))
		{
		case SC_RESTORE:
			_this->ShowChatWindow(true);
			//SetFocus(GetDlgItem(hWnd, IDC_INPUTAREA_EDIT));
			return TRUE;
		}
		break;

	case WM_DESTROY:
		// _this->SendTextChatRequest(_this, CHAT_FINISHED);
		EndDialog(hWnd, FALSE);
		return TRUE;
	}
	return 0;
}