INT_PTR CALLBACK GbaSlotPiano(HWND dialog, UINT msg,WPARAM wparam,LPARAM lparam)
{
	int which = 0;

	switch(msg)
	{
		case WM_INITDIALOG: 
		{
			_OKbutton = TRUE;
			SendDlgItemMessage(dialog,IDC_PIANO_C,WM_USER+44,tmp_Piano.C,0);
			SendDlgItemMessage(dialog,IDC_PIANO_CS,WM_USER+44,tmp_Piano.CS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_D,WM_USER+44,tmp_Piano.D,0);
			SendDlgItemMessage(dialog,IDC_PIANO_DS,WM_USER+44,tmp_Piano.DS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_E,WM_USER+44,tmp_Piano.E,0);
			SendDlgItemMessage(dialog,IDC_PIANO_F,WM_USER+44,tmp_Piano.F,0);
			SendDlgItemMessage(dialog,IDC_PIANO_FS,WM_USER+44,tmp_Piano.FS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_G,WM_USER+44,tmp_Piano.G,0);
			SendDlgItemMessage(dialog,IDC_PIANO_GS,WM_USER+44,tmp_Piano.GS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_A,WM_USER+44,tmp_Piano.A,0);
			SendDlgItemMessage(dialog,IDC_PIANO_AS,WM_USER+44,tmp_Piano.AS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_B,WM_USER+44,tmp_Piano.B,0);
			SendDlgItemMessage(dialog,IDC_PIANO_HIC,WM_USER+44,tmp_Piano.HIC,0);
			if (temp_type != addon_type)
				needReset = true;
			else
				needReset = false;

			return TRUE;
		}

		case WM_USER+46:
			SendDlgItemMessage(dialog,IDC_PIANO_C,WM_USER+44,tmp_Piano.C,0);
			SendDlgItemMessage(dialog,IDC_PIANO_CS,WM_USER+44,tmp_Piano.CS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_D,WM_USER+44,tmp_Piano.D,0);
			SendDlgItemMessage(dialog,IDC_PIANO_DS,WM_USER+44,tmp_Piano.DS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_E,WM_USER+44,tmp_Piano.E,0);
			SendDlgItemMessage(dialog,IDC_PIANO_F,WM_USER+44,tmp_Piano.F,0);
			SendDlgItemMessage(dialog,IDC_PIANO_FS,WM_USER+44,tmp_Piano.FS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_G,WM_USER+44,tmp_Piano.G,0);
			SendDlgItemMessage(dialog,IDC_PIANO_GS,WM_USER+44,tmp_Piano.GS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_A,WM_USER+44,tmp_Piano.A,0);
			SendDlgItemMessage(dialog,IDC_PIANO_AS,WM_USER+44,tmp_Piano.AS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_B,WM_USER+44,tmp_Piano.B,0);
			SendDlgItemMessage(dialog,IDC_PIANO_HIC,WM_USER+44,tmp_Piano.HIC,0);
		return TRUE;

		case WM_USER+43:
			//MessageBox(hDlg,"USER+43 CAUGHT","moo",MB_OK);
			which = GetDlgCtrlID((HWND)lparam);
			switch(which)
			{
			case IDC_PIANO_C: tmp_Piano.C = wparam; break;
			case IDC_PIANO_CS: tmp_Piano.CS = wparam; break;
			case IDC_PIANO_D: tmp_Piano.D = wparam; break;
			case IDC_PIANO_DS: tmp_Piano.DS = wparam; break;
			case IDC_PIANO_E: tmp_Piano.E = wparam; break;
			case IDC_PIANO_F: tmp_Piano.F = wparam; break;
			case IDC_PIANO_FS: tmp_Piano.FS = wparam; break;
			case IDC_PIANO_G: tmp_Piano.G = wparam; break;
			case IDC_PIANO_GS: tmp_Piano.GS = wparam; break;
			case IDC_PIANO_A: tmp_Piano.A = wparam; break;
			case IDC_PIANO_AS: tmp_Piano.AS = wparam; break;
			case IDC_PIANO_B: tmp_Piano.B = wparam; break;
			case IDC_PIANO_HIC: tmp_Piano.HIC = wparam; break;

			}

			SendDlgItemMessage(dialog,IDC_PIANO_C,WM_USER+44,tmp_Piano.C,0);
			SendDlgItemMessage(dialog,IDC_PIANO_CS,WM_USER+44,tmp_Piano.CS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_D,WM_USER+44,tmp_Piano.D,0);
			SendDlgItemMessage(dialog,IDC_PIANO_DS,WM_USER+44,tmp_Piano.DS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_E,WM_USER+44,tmp_Piano.E,0);
			SendDlgItemMessage(dialog,IDC_PIANO_F,WM_USER+44,tmp_Piano.F,0);
			SendDlgItemMessage(dialog,IDC_PIANO_FS,WM_USER+44,tmp_Piano.FS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_G,WM_USER+44,tmp_Piano.G,0);
			SendDlgItemMessage(dialog,IDC_PIANO_GS,WM_USER+44,tmp_Piano.GS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_A,WM_USER+44,tmp_Piano.A,0);
			SendDlgItemMessage(dialog,IDC_PIANO_AS,WM_USER+44,tmp_Piano.AS,0);
			SendDlgItemMessage(dialog,IDC_PIANO_B,WM_USER+44,tmp_Piano.B,0);
			SendDlgItemMessage(dialog,IDC_PIANO_HIC,WM_USER+44,tmp_Piano.HIC,0);
			PostMessage(dialog,WM_NEXTDLGCTL,0,0);
		return true;
	}
	return FALSE;
}