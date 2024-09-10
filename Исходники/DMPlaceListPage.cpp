void CDMPlaceListPage::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{

	HICON hIco;
	switch(nIDCtl)
	{
	case IDC_ADD:
		hIco = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ADD), IMAGE_ICON, 16, 16, 0);
		break;
	case IDC_DELETE:
		hIco = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_DEL), IMAGE_ICON, 16, 16, 0);
		break;
	case IDC_NEW:
		hIco = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_NEW), IMAGE_ICON, 16, 16, 0);
		break;
	default:
		CPropertyPage::OnDrawItem(nIDCtl, lpDrawItemStruct);
		return;
	}


	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	if((lpDrawItemStruct->itemAction&ODA_SELECT) && (lpDrawItemStruct->itemState&ODS_SELECTED))
	{
		CBrush br(RGB(0,0,0));
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, RGB(255,255,255));
		dc.FrameRect(&lpDrawItemStruct->rcItem, &br);
	}
	else
	{
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_BTNFACE));
	}

	dc.DrawIcon(2, 2, hIco);
	dc.Detach();
}