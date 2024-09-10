HRESULT CEffectsListDlg::doAddEffect()
{
	int sel = SendMessage(lHwnd, LB_GETCURSEL, 0, 0);
	if(sel == LB_ERR)return sel;
	GUID* pGUID = (GUID*)SendMessage(lHwnd, LB_GETITEMDATA, sel, 0);
	WCHAR sguid[256];
	StringFromGUID2(*pGUID, sguid, 256);
//	OutputDebugString(_bstr_t(sguid).operator wchar_t*());
//	OutputDebugString(_T("\r\n"));
	TCHAR buff[128];
	SendMessage(t1Hwnd, WM_GETTEXT, 128, (LPARAM)buff);
	REFERENCE_TIME start = _ttoi64(buff);
	SendMessage(t2Hwnd, WM_GETTEXT, 128, (LPARAM)buff);
	REFERENCE_TIME stop = _ttoi64(buff);
	SendMessage(trkHwnd, WM_GETTEXT, 128, (LPARAM)buff);
	int track = _ttoi(buff);
	if(SendMessage(swapHwnd, BM_GETCHECK, 0, 0) == BST_UNCHECKED)swap = false;
	else swap = true;

	if(type)return pem->addTransition(track, *pGUID, start, stop, 0, swap, NULL);
	else return pem->addEffect(track, *pGUID, start, stop, 0, NULL);
}