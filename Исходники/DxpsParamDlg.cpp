void CDxpsParamDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if(nIDCtl==IDC_COMBO_COLOR)
	{	char str[30];
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		CRect rect;
		rect=lpDrawItemStruct->rcItem;

		if (lpDrawItemStruct->itemState & ODS_SELECTED)
		{
			dc.SetTextColor(0xFFFFFF&(~theApp.m_pMainFrame->m_pDxpsDlg->m_ColorIndex[lpDrawItemStruct->itemID]));
			if(lpDrawItemStruct->itemID==7 || lpDrawItemStruct->itemID == 12)
				dc.SetTextColor(RGB(255,255,255));
		}
		else
		{
			dc.SetTextColor(RGB(0,0,0));
			if(lpDrawItemStruct->itemID == 3 || lpDrawItemStruct->itemID==11)
				dc.SetTextColor(RGB(196,196,196));
		}
		dc.SetBkColor(RGB(255,255,255));
		m_ComboColor.GetLBText(lpDrawItemStruct->itemID,str);
		dc.FillSolidRect(rect,theApp.m_pMainFrame->m_pDxpsDlg->m_ColorIndex[lpDrawItemStruct->itemID]);
		CRect rect2=rect;
		rect2.left+=3;
		dc.DrawText(str,rect2,DT_LEFT | DT_WORDBREAK);  
		if (lpDrawItemStruct->itemState & ODS_SELECTED)
		{
			CBrush brush(RGB(0,0,0));
			dc.FrameRect(&rect,&brush);
		}
		dc.Detach(); 
		return;
	}
	
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}