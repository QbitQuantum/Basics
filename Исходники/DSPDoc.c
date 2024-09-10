INT_PTR CALLBACK inputParaProc(HWND hwndDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hwndDlg,IDC_INPUTPARA_PERIOD,m_Period,TRUE);
		SetDlgItemInt(hwndDlg,IDC_INPUTPARA_AMPLITUDE,m_Amplitude,TRUE);
		SetDlgItemInt(hwndDlg,IDC_INPUTPARA_SAMPFREQ,m_SampleFreq,TRUE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			{
			BOOL Translated;
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_INPUTPARA_PERIOD,NULL,TRUE),
				4,320,m_Period,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_INPUTPARA_AMPLITUDE,NULL,TRUE),
				1,5,m_Amplitude,Translated);
			MinMaxInt(hwndDlg,GetDlgItemInt(hwndDlg,IDC_INPUTPARA_SAMPFREQ,NULL,TRUE),
				1,159,m_SampleFreq,Translated);
			if(!Translated) return FALSE;
			n_mCoordMode=SINSIGNAL_INPUT;
			InvalidateRgn(GetParent(hwndDlg),NULL,TRUE);
			}
		case IDCANCEL:
			EndDialog(hwndDlg,0);
			return TRUE;
		} 
	}
	return FALSE;
}