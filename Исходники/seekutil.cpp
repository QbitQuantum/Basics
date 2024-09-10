HRESULT ConfigureSeekbar(IMediaSeeking *pMS, CSliderCtrl Seekbar, CStatic& strPosition, HWND hwndOwner)
{
    HRESULT hr;

    // Disable seekbar for new file and reset tracker/position label
    Seekbar.SetPos(0);
    Seekbar.EnableWindow(FALSE);
    g_rtTotalTime=0;

	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch (dwLanguageID)
	{
	case LANG_SPANISH :
		strPosition.SetWindowText(TEXT("Position: 00m:00s\0"));
		break;
	default:
		strPosition.SetWindowText(TEXT("Position: 00m:00s\0"));
		break;
	}	

    DWORD dwSeekCaps = AM_SEEKING_CanSeekAbsolute | AM_SEEKING_CanGetDuration;

    // Can we seek this file?  If so, enable trackbar.
    if (pMS && (S_OK == pMS->CheckCapabilities(&dwSeekCaps))) 
    {
        hr = pMS->GetDuration(&g_rtTotalTime);
        Seekbar.EnableWindow(TRUE);
    }

    g_hwnd = hwndOwner;

    return hr;
}