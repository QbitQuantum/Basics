void CStaticMemDC::OnPaint()
{
	CPaintDC dc(this);
	CRect clip;
    GetWindowRect(&clip);		// get rect of the control
    ScreenToClient(&clip);
    CMemDC2 memDC(&dc,&clip);
	DefWindowProcA(WM_PAINT, (WPARAM)memDC->m_hDC, (LPARAM)0);
}