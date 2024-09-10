LRESULT COXCoolComboBox::OnSetFont(WPARAM wParam,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

    Default();

    CDC* pDC=GetDC();
    pDC->SelectObject(GetFont());
    TEXTMETRIC tm;
    pDC->GetTextMetrics(&tm);
    m_nDefaultFontHeight=tm.tmHeight;
    m_nDefaultFontHeightSansLeading=pDC->GetTextExtent(_T("ygaQ!|")).cy;
    ReleaseDC(pDC);    

    int nCurrentHeight=PtrToInt(SendMessage(CB_GETITEMHEIGHT,(WPARAM)-1,0));

    if (nCurrentHeight!=m_nDefaultFontHeight+1)
        SendMessage(CB_SETITEMHEIGHT,(WPARAM)-1,m_nDefaultFontHeight+1);        

	return 0;
}