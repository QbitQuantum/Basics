// CFileOpenDlg::DoPaint
//
//		Paints the splitter if it is displayed
//
void CFileOpenDlg::DoPaint(CPaintDC& dc) 
{
	if(m_nState == vsStandard)
	{
		CRect	rcClient;
		int		y;

		GetClientRect(&rcClient);

		y = m_ySplit;

		dc.MoveTo(0, y);
		dc.LineTo(rcClient.right, y);

		y += 6;		// This is the splitter height

		dc.MoveTo(0, y);
		dc.LineTo(rcClient.right, y);
	}
}