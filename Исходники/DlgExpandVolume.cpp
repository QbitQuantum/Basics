BOOL CALLBACK ExpandVolProgressDlgProc (HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static EXPAND_VOL_THREAD_PARAMS *pProgressDlgParam;
	static BOOL bVolTransformStarted = FALSE;
	static BOOL showRandPool = TRUE;

	WORD lw = LOWORD (wParam);

	switch (msg)
	{
	case WM_INITDIALOG:
		{
			char szOldHostSize[512], szNewHostSize[512];

			pProgressDlgParam = (EXPAND_VOL_THREAD_PARAMS*)lParam;
			bVolTransformStarted = FALSE;
			showRandPool = TRUE;

			hCurPage = hwndDlg;
			nPbar = IDC_PROGRESS_BAR;

			GetSpaceString(szOldHostSize,sizeof(szOldHostSize),pProgressDlgParam->oldSize,pProgressDlgParam->bIsDevice);
			GetSpaceString(szNewHostSize,sizeof(szNewHostSize),pProgressDlgParam->newSize,pProgressDlgParam->bIsDevice);

			SetWindowText (GetDlgItem (hwndDlg, IDC_EXPAND_VOLUME_OLDSIZE), szOldHostSize);
			SetWindowText (GetDlgItem (hwndDlg, IDC_EXPAND_VOLUME_NEWSIZE), szNewHostSize);
			SetWindowText (GetDlgItem (hwndDlg, IDC_EXPAND_VOLUME_NAME), pProgressDlgParam->szVolumeName);
			SetWindowText (GetDlgItem (hwndDlg, IDC_EXPAND_FILE_SYSTEM), szFileSystemStr[pProgressDlgParam->FileSystem]);
			SetWindowText (GetDlgItem (hwndDlg, IDC_EXPAND_VOLUME_INITSPACE), pProgressDlgParam->bInitFreeSpace?"Yes":"No");

			SendMessage (GetDlgItem (hwndDlg, IDC_BOX_STATUS), WM_SETFONT, (WPARAM) hBoldFont, (LPARAM) TRUE);

			SendMessage (GetDlgItem (hwndDlg, IDC_RANDOM_BYTES), WM_SETFONT, (WPARAM) hFixedDigitFont, (LPARAM) TRUE);

			// set status text
			if ( !pProgressDlgParam->bInitFreeSpace && pProgressDlgParam->bIsLegacy )
			{
				showRandPool = FALSE;
				EnableWindow (GetDlgItem (hwndDlg, IDC_DISPLAY_POOL_CONTENTS), FALSE);
				EnableWindow (GetDlgItem (hwndDlg, IDC_RANDOM_BYTES), FALSE);
				SetDlgItemText(hwndDlg, IDC_BOX_STATUS, "Click 'Continue' to expand the volume.");
			}
			else
			{
				SetDlgItemText(hwndDlg, IDC_BOX_STATUS, "IMPORTANT: Move your mouse as randomly as possible within this window. The longer you move it, the better. This significantly increases the cryptographic strength of the encryption keys. Then click 'Continue' to expand the volume.");
			}

			SendMessage (GetDlgItem (hwndDlg, IDC_DISPLAY_POOL_CONTENTS), BM_SETCHECK, showRandPool ? BST_CHECKED : BST_UNCHECKED, 0);
			SetTimer (hwndDlg, TIMER_ID_RANDVIEW, TIMER_INTERVAL_RANDVIEW, NULL);
		}
		return 0;
	case TC_APPMSG_VOL_TRANSFORM_THREAD_ENDED:
		{
			int nStatus = (int)lParam;

			NormalCursor ();
			if (nStatus != 0)
			{
				if ( nStatus != ERR_USER_ABORT )
					AddProgressDlgStatus (hwndDlg, "Error: volume expansion failed.");
				else
					AddProgressDlgStatus (hwndDlg, "Error: operation aborted by user.");
			}
			else
			{
				AddProgressDlgStatus (hwndDlg, "Finished. Volume successfully expanded.");
			}

			SetWindowText (GetDlgItem (hwndDlg, IDOK), "Exit");
			EnableWindow (GetDlgItem (hwndDlg, IDOK), TRUE);
			EnableWindow (GetDlgItem (hwndDlg, IDCANCEL), FALSE);
		}
		return 1;

	case WM_TIMER:

		switch (wParam)
		{
		case TIMER_ID_RANDVIEW:
			{
				unsigned char tmp[16] = {0};
				char szRndPool[64] = {0};

				if (!showRandPool)
					return 1;

				RandpeekBytes (hwndDlg, tmp, sizeof (tmp));

				StringCbPrintfA (szRndPool, sizeof(szRndPool), "%08X%08X%08X%08X", 
					*((DWORD*) (tmp + 12)), *((DWORD*) (tmp + 8)), *((DWORD*) (tmp + 4)), *((DWORD*) (tmp)));

				SetWindowText (GetDlgItem (hwndDlg, IDC_RANDOM_BYTES), szRndPool);

				burn (tmp, sizeof(tmp));
				burn (szRndPool, sizeof(szRndPool));
			}
			return 1;
		}
		return 0;

	case WM_COMMAND:
		if (lw == IDC_DISPLAY_POOL_CONTENTS)
		{
			showRandPool = IsButtonChecked (GetDlgItem (hwndDlg, IDC_DISPLAY_POOL_CONTENTS));
			return 1;
		}
		if (lw == IDCANCEL)
		{
			if (bVolTransformStarted)
			{
				if (MessageBoxW (hwndDlg, L"Warning: Volume expansion is in progress!\n\nStopping now may result in a damaged volume.\n\nDo you really want to cancel?", lpszTitle, YES_NO|MB_ICONQUESTION|MB_DEFBUTTON2) == IDNO)
					return 1;

				// tell the volume transform thread to terminate
				bVolTransformThreadCancel = TRUE;
			}
			EndDialog (hwndDlg, lw);
			return 1;
		}

		if (lw == IDOK)
		{
			if (bVolTransformStarted)
			{
				// TransformThreadFunction finished -> OK button is now exit
				EndDialog (hwndDlg, lw);
			}
			else
			{
				showRandPool = FALSE;
				KillTimer (hwndDlg, TIMER_ID_RANDVIEW);
				EnableWindow (GetDlgItem (hwndDlg, IDC_DISPLAY_POOL_CONTENTS), FALSE);
				EnableWindow (GetDlgItem (hwndDlg, IDOK), FALSE);
				SetProgressDlgStatus (hwndDlg, "Starting volume expansion ...\r\n");
				bVolTransformStarted = TRUE;
				pProgressDlgParam->hwndDlg = hwndDlg;
				if ( _beginthread (volTransformThreadFunction, 0, pProgressDlgParam) == -1L )
				{
					handleError (hwndDlg, ERR_OS_ERROR, SRC_POS);
					EndDialog (hwndDlg, lw);
				}
				WaitCursor();
			}
			return 1;
		}

		return 0;
	}

	return 0;
}