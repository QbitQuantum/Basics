HBRUSH CMainTestView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
 	CRect rect; 
 	//CWnd*   hWndChild = ::GetWindow(m_hWnd,   GW_CHILD); 
 	CWnd*   hWndChild = GetWindow(GW_CHILD); 
 	while(hWndChild) 
 	{
 		if(hWndChild->GetDlgCtrlID()==331 && nCtlColor== CTLCOLOR_STATIC) 
 		{ 
 			COLORREF backColor = RGB(236, 233, 216);//这个颜色为Formview默认的面板颜色		
 			hWndChild->GetClientRect(&rect);
 			pDC->FillSolidRect(&rect,backColor);
 			pDC->SetBkColor(backColor);
 			return CreateSolidBrush(backColor);//创建背景刷子
 		}
 		hWndChild   =   hWndChild-> GetNextWindow(); 
 	} 
	
	return hbr;
}