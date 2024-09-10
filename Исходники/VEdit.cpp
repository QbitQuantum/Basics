void CVEdit::DrawBkAndFrame()
{
	CRect rcClient, rcWnd;
	CDC* pDC = this->GetDC();
	GetClientRect(&rcClient);
	GetWindowRect(&rcWnd);
	ScreenToClient(&rcWnd);

	CRect rcFill;
	rcFill = rcWnd;
	rcFill.bottom = rcClient.top ;
	pDC->FillRect(rcFill, &m_bkBrush);

	rcFill = rcWnd;
	rcFill.top = rcClient.bottom ;
	pDC->FillRect(rcFill, &m_bkBrush);

	pDC->FrameRect(rcWnd, &m_bkFMBrush);


	ReleaseDC(pDC);
}