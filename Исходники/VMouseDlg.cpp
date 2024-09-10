void CVMouseDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if(lpMeasureItemStruct->CtlType == ODT_MENU)
	{
		if(IsMenu((HMENU)lpMeasureItemStruct->itemID) 
			&& IsMenu((HMENU)lpMeasureItemStruct->itemID))
		{
			m_trayIcon.m_menu.MeasureItem(lpMeasureItemStruct);
		}
	}
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}