void CGradientProgressCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	CRect rectClient;
	GetClientRect(&rectClient);
	// If the current positionis  invalid then we should fade into the  background
	if (m_nCurrentPosition < m_nLower || m_nCurrentPosition > m_nUpper)
	{
		CRect rect;
		GetClientRect(rect);
		CBrush brush;
		brush.CreateSolidBrush(::GetSysColor(COLOR_3DFACE));
		dc.FillRect(&rect, &brush);
		VERIFY(brush.DeleteObject());
		return;
	}
	
	// The actions to take depend on whether or not we are a vertical control
	DWORD dwStyles = GetStyle();
	BOOL bVertical = (BOOL)(dwStyles & PBS_VERTICAL);
	
	
	// Figure out what part should be visible so we can stop the gradient when needed
	float maxWidth;
	if (bVertical)
		maxWidth = ((float)m_nCurrentPosition/(float)m_nUpper * (float)rectClient.bottom);		
	else
		maxWidth = ((float)m_nCurrentPosition/(float)m_nUpper * (float)rectClient.right);
	
	
	// Draw the gradient
		DrawGradient(&dc, rectClient, (int)maxWidth, bVertical);

	// Show percent indicator if needed
	if (m_bShowPercent)
	{
		CString strPercent;
		float fp = 100.0f; 
		fp *= (float)(m_nCurrentPosition-m_nLower); 
		fp /= (float)(m_nUpper-m_nLower); 
		strPercent.Format(_T("%ld/%ld"), m_nCurrentPosition, m_nUpper);
		
		dc.SetTextColor(m_clrText);
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(strPercent, &rectClient, DT_VCENTER |  DT_CENTER | DT_SINGLELINE);
	}

	// Do not call CProgressCtrl::OnPaint() for painting messages
}