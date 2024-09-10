// -----------------------------------------------------------------------------
// Feedback intensity dialog
static INT_PTR CALLBACK PhosphorProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)	// LPARAM lParam
{
	static int nPrevIntensity;
	static int nPrevSaturation;

	switch (Msg) {
		case WM_INITDIALOG: {
			TCHAR szText[16];
			nPrevIntensity = nVidFeedbackIntensity;
			nPrevSaturation = nVidFeedbackOverSaturation;
			nExitStatus = 0;

			WndInMid(hDlg, hScrnWnd);

			// Initialise sliders
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_1_SLIDER, TBM_SETRANGE, (WPARAM)0, (LPARAM)MAKELONG(0, 255));
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_1_SLIDER, TBM_SETPAGESIZE, (WPARAM)0, (LPARAM)8);
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_1_SLIDER, TBM_SETTIC, (WPARAM)0, (LPARAM)127);
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_1_SLIDER, TBM_SETTIC, (WPARAM)0, (LPARAM)63);
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_1_SLIDER, TBM_SETTIC, (WPARAM)0, (LPARAM)31);
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_1_SLIDER, TBM_SETTIC, (WPARAM)0, (LPARAM)15);

			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_2_SLIDER, TBM_SETRANGE, (WPARAM)0, (LPARAM)MAKELONG(0, 127));
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_2_SLIDER, TBM_SETPAGESIZE, (WPARAM)0, (LPARAM)4);
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_2_SLIDER, TBM_SETTIC, (WPARAM)0, (LPARAM)63);
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_2_SLIDER, TBM_SETTIC, (WPARAM)0, (LPARAM)31);
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_2_SLIDER, TBM_SETTIC, (WPARAM)0, (LPARAM)15);

			// Set slider to current values
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_1_SLIDER, TBM_SETPOS, (WPARAM)true, (LPARAM)nVidFeedbackIntensity);
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_2_SLIDER, TBM_SETPOS, (WPARAM)true, (LPARAM)nVidFeedbackOverSaturation);

			// Set the edit control to current values
			_stprintf(szText, _T("%i"), nVidFeedbackIntensity);
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_1_EDIT, WM_SETTEXT, (WPARAM)0, (LPARAM)szText);
			_stprintf(szText, _T("%i"), nVidFeedbackOverSaturation);
			SendDlgItemMessage(hDlg, IDC_PHOSPHOR_2_EDIT, WM_SETTEXT, (WPARAM)0, (LPARAM)szText);

			return TRUE;
		}
		case WM_COMMAND: {
			switch (HIWORD(wParam)) {
				case BN_CLICKED: {
					if (LOWORD(wParam) == IDOK) {
						nExitStatus = 1;
						SendMessage(hDlg, WM_CLOSE, 0, 0);
					}
					if (LOWORD(wParam) == IDCANCEL) {
						nExitStatus = -1;
						SendMessage(hDlg, WM_CLOSE, 0, 0);
					}
					break;
				}
				case EN_UPDATE: {
					if (nExitStatus == 0) {
						TCHAR szText[16] = _T("");
						bool bValid = 1;

						switch (LOWORD(wParam)) {
							case IDC_PHOSPHOR_1_EDIT:
								if (SendDlgItemMessage(hDlg, IDC_PHOSPHOR_1_EDIT, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0) < 16) {
									SendDlgItemMessage(hDlg, IDC_PHOSPHOR_1_EDIT, WM_GETTEXT, (WPARAM)16, (LPARAM)szText);
								}

								// Scan string in the edit control for illegal characters
								for (int i = 0; szText[i]; i++) {
									if (!_istdigit(szText[i])) {
										bValid = 0;
										break;
									}
								}

								if (bValid) {
									nVidFeedbackIntensity = _tcstol(szText, NULL, 0);
									if (nVidFeedbackIntensity < 0) {
										nVidFeedbackIntensity = 0;
									} else {
										if (nVidFeedbackIntensity > 255) {
											nVidFeedbackIntensity = 255;
										}
									}

									// Set slider to current value
									SendDlgItemMessage(hDlg, IDC_PHOSPHOR_1_SLIDER, TBM_SETPOS, (WPARAM)true, (LPARAM)nVidFeedbackIntensity);
								}
								break;
							case IDC_PHOSPHOR_2_EDIT:
								if (SendDlgItemMessage(hDlg, IDC_PHOSPHOR_2_EDIT, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0) < 16) {
									SendDlgItemMessage(hDlg, IDC_PHOSPHOR_2_EDIT, WM_GETTEXT, (WPARAM)16, (LPARAM)szText);
								}

								// Scan string in the edit control for illegal characters
								for (int i = 0; szText[i]; i++) {
									if (!_istdigit(szText[i])) {
										bValid = 0;
										break;
									}
								}

								if (bValid) {
									nVidFeedbackOverSaturation = _tcstol(szText, NULL, 0);
									if (nVidFeedbackOverSaturation < 0) {
										nVidFeedbackOverSaturation = 0;
									} else {
										if (nVidFeedbackOverSaturation > 255) {
											nVidFeedbackOverSaturation = 255;
										}
									}

									// Set slider to current value
									SendDlgItemMessage(hDlg, IDC_PHOSPHOR_2_SLIDER, TBM_SETPOS, (WPARAM)true, (LPARAM)nVidFeedbackOverSaturation);

									// Update the screen
									if (bVidOkay) {
										VidPaint(2);
									}
								}
								break;
						}
					}
					break;
				}
			}
			break;
		}

		case WM_HSCROLL: {
			switch (LOWORD(wParam)) {
				case TB_BOTTOM:
				case TB_ENDTRACK:
				case TB_LINEDOWN:
				case TB_LINEUP:
				case TB_PAGEDOWN:
				case TB_PAGEUP:
				case TB_THUMBPOSITION:
				case TB_THUMBTRACK:
				case TB_TOP: {
					if (nExitStatus == 0) {
						TCHAR szText[16];

						// Update the contents of the edit control
						switch (GetDlgCtrlID((HWND)lParam)) {
							case IDC_PHOSPHOR_1_SLIDER:
								nVidFeedbackIntensity = SendDlgItemMessage(hDlg, IDC_PHOSPHOR_1_SLIDER, TBM_GETPOS, (WPARAM)0, (LPARAM)0);
								_stprintf(szText, _T("%i"), nVidFeedbackIntensity);
								SendDlgItemMessage(hDlg, IDC_PHOSPHOR_1_EDIT, WM_SETTEXT, (WPARAM)0, (LPARAM)szText);
								break;
							case IDC_PHOSPHOR_2_SLIDER:
								nVidFeedbackOverSaturation = SendDlgItemMessage(hDlg, IDC_PHOSPHOR_2_SLIDER, TBM_GETPOS, (WPARAM)0, (LPARAM)0);
								_stprintf(szText, _T("%i"), nVidFeedbackOverSaturation);
								SendDlgItemMessage(hDlg, IDC_PHOSPHOR_2_EDIT, WM_SETTEXT, (WPARAM)0, (LPARAM)szText);
								break;
						}
					}
					break;
				}
			}
			break;
		}

		case WM_CLOSE:
			if (nExitStatus != 1) {
				nVidFeedbackIntensity = nPrevIntensity;
				nVidFeedbackOverSaturation = nPrevSaturation;
			}
			EndDialog(hDlg, 0);
			break;
	}

	return 0;
}