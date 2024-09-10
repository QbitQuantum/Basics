void CDonutView::OnMultiDlImages(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
{
	ATLTRACE2( atlTraceGeneral, 4, _T("CDonutView::OnMultiDlImages\n") );

	if ( _ToggleFlag(ID_DLCTL_DLIMAGES, DLCTL_DLIMAGES) )
		_LightRefresh();
}