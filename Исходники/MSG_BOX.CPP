BOOL CALLBACK MsgBoxDlgProc (HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
MBDATA * pMbd;

	switch (uMsg)
		{
		//  center in parent but on screen if hWndPar != NULL
		case WM_INITDIALOG : {
			CRect rWin;
			GetClientRect (hDlg, &rWin);
			ASSERT ((rWin.left == 0) && (rWin.top == 0));
			HWND hWndPar = GetParent (hDlg);

			if (hWndPar == NULL)
				rWin += CPoint ((GetSystemMetrics (SM_CXSCREEN) - rWin.Width ()) / 2,
										(GetSystemMetrics (SM_CYSCREEN) - rWin.Height ()) / 2);
			else
			  {
			  CRect rPar;
				GetWindowRect (hWndPar, &rPar);
				rWin += CPoint (rPar.left + (rPar.Width () - rWin.Width ()) / 2,
										rPar.top + (rPar.Height () - rWin.Height ()) / 2);
				if (rWin.left < 0)
					rWin += CPoint (- rWin.left, 0);
				else
					if (rWin.right > GetSystemMetrics (SM_CXSCREEN))
						rWin -= CPoint (rWin.right - GetSystemMetrics (SM_CXSCREEN), 0);
				if (rWin.top < 0)
					rWin += CPoint (0, - rWin.top);
				else
					if (rWin.bottom > GetSystemMetrics (SM_CYSCREEN))
						rWin -= CPoint (0, rWin.bottom - GetSystemMetrics (SM_CYSCREEN));
			  }

			SetWindowPos (hDlg, NULL, rWin.left, rWin.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			} // NO BREAK - falls through

		case WM_ACTIVATE :
		case WM_ACTIVATEAPP :
			hDlgBox = hDlg;
			return (TRUE);
		case WM_DESTROY :
			hDlgBox = NULL;
			break;

		case WM_PAINT :
			pMbd = (MBDATA *) GetWindowLong (hDlg, DWL_USER);
			if ((pMbd == NULL) || (pMbd->hIcon == NULL))
				break;
			PAINTSTRUCT ps;
			BeginPaint (hDlg, &ps);
			DrawIcon (ps.hdc, pMbd->iXicon, pMbd->iYicon, pMbd->hIcon);
			EndPaint (hDlg, &ps);
			return (TRUE);

		case WM_COMMAND :
			if ((LOWORD (lParam) == 0) || (HIWORD (lParam) != BN_CLICKED))
				break;
			if ((pMbd = (MBDATA *) GetWindowLong (hDlg, DWL_USER)) == NULL)
				break;

			// check for help
			if (wParam == pMbd->wHelpBtn)
			  {
				const char *pHelpFile;
				char sName[130];
				CWinApp *pApp = AfxGetApp ();
				if (pApp != NULL)
					pHelpFile =	pApp->m_pszHelpFilePath;
				else
				  {
				  GetModuleFileName (AfxGetInstanceHandle (), sName, 128);
					int iLen = strlen (sName);
					if (iLen < 3)
						break;
					sName[iLen-3] = 0;
					strcat (sName, "HLP");
					pHelpFile = sName;
				  }

				if (pMbd->lHelp == 0)
					WinHelp (hDlg, pHelpFile,	HELP_CONTENTS, 0);
				else
					WinHelp (hDlg, pHelpFile,	HELP_CONTEXT, pMbd->lHelp);
			  return (TRUE);
			  }

			*(pMbd->piRtn) = wParam;
			return (TRUE);
		}

	return (FALSE);
}