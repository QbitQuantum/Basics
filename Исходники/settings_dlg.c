static INT_PTR CALLBACK settingsDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		saved_mute_mask = mute_mask;
		settingsDialogSet(hDlg, song_length, silence_seconds, play_loops, mute_mask);
		return TRUE;
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED) {
			WORD wCtrl = LOWORD(wParam);
			BOOL enabled;
			switch (wCtrl) {
			case IDC_UNLIMITED:
				enableTimeInput(hDlg, FALSE);
				return TRUE;
			case IDC_LIMITED:
				enableTimeInput(hDlg, TRUE);
				setFocusAndSelect(hDlg, IDC_MINUTES);
				return TRUE;
			case IDC_SILENCE:
				enabled = (IsDlgButtonChecked(hDlg, IDC_SILENCE) == BST_CHECKED);
				EnableWindow(GetDlgItem(hDlg, IDC_SILSECONDS), enabled);
				if (enabled)
					setFocusAndSelect(hDlg, IDC_SILSECONDS);
				return TRUE;
			case IDC_LOOPS:
			case IDC_NOLOOPS:
				return TRUE;
			case IDC_MUTE1:
			case IDC_MUTE1 + 1:
			case IDC_MUTE1 + 2:
			case IDC_MUTE1 + 3:
			case IDC_MUTE1 + 4:
			case IDC_MUTE1 + 5:
			case IDC_MUTE1 + 6:
			case IDC_MUTE1 + 7:
			{
				int mask = 1 << (wCtrl - IDC_MUTE1);
				if (IsDlgButtonChecked(hDlg, wCtrl) == BST_CHECKED)
					mute_mask |= mask;
				else
					mute_mask &= ~mask;
				ASAP_MutePokeyChannels(asap, mute_mask);
				return TRUE;
			}
			case IDOK:
			{
				int new_song_length;
				if (IsDlgButtonChecked(hDlg, IDC_UNLIMITED) == BST_CHECKED)
					new_song_length = -1;
				else {
					int minutes;
					int seconds;
					if (!getDlgInt(hDlg, IDC_MINUTES, &minutes)
					 || !getDlgInt(hDlg, IDC_SECONDS, &seconds))
						return TRUE;
					new_song_length = 60 * minutes + seconds;
				}
				if (IsDlgButtonChecked(hDlg, IDC_SILENCE) != BST_CHECKED)
					silence_seconds = -1;
				else if (!getDlgInt(hDlg, IDC_SILSECONDS, &silence_seconds))
					return TRUE;
				song_length = new_song_length;
				play_loops = (IsDlgButtonChecked(hDlg, IDC_LOOPS) == BST_CHECKED);
				EndDialog(hDlg, IDOK);
				return TRUE;
			}
			case IDCANCEL:
				mute_mask = saved_mute_mask;
				ASAP_MutePokeyChannels(asap, mute_mask);
				EndDialog(hDlg, IDCANCEL);
				return TRUE;
			}
		}
		break;
	default:
		break;
	}
	return FALSE;
}