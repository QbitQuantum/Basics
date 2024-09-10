bool CNoteDlg::PrintPage(UINT nPage, HDC hDC)
{
	if (nPage >= (UINT)m_arrPages.GetSize())
		return false;
	
	RECT rcPage;
	rcPage.left = rcPage.top = 0;
	rcPage.bottom = GetDeviceCaps(hDC, PHYSICALHEIGHT);
	rcPage.right = GetDeviceCaps(hDC, PHYSICALWIDTH);
	
	rcPage.right = MulDiv(rcPage.right, 1440, GetDeviceCaps(hDC, LOGPIXELSX));
	rcPage.bottom = MulDiv(rcPage.bottom, 1440, GetDeviceCaps(hDC, LOGPIXELSY));
	
	RECT rcOutput = rcPage;
	// Convert from 1/1000" to twips
	rcOutput.left += MulDiv(m_rcMargin.left, 1440, 1000);
	rcOutput.right -= MulDiv(m_rcMargin.right, 1440, 1000);
	rcOutput.top += MulDiv(m_rcMargin.top, 1440, 1000);
	rcOutput.bottom -= MulDiv(m_rcMargin.bottom, 1440, 1000);
	
	
	FORMATRANGE fr;
	fr.hdc = hDC;
	fr.hdcTarget = hDC;
	fr.rc = rcOutput;
	fr.rcPage = rcPage;
	fr.chrg.cpMin = 0;
	fr.chrg.cpMax = -1;
	fr.chrg.cpMin = m_arrPages[nPage];
	
	// We have to adjust the origin because 0,0 is not at the corner of the paper
	// but is at the corner of the printable region
	int nOffsetX = GetDeviceCaps(hDC, PHYSICALOFFSETX);
	int nOffsetY = GetDeviceCaps(hDC, PHYSICALOFFSETY);
	SetViewportOrgEx(hDC, -nOffsetX, -nOffsetY, NULL);
	m_wndEdit.FormatRange(fr, TRUE);
	m_wndEdit.DisplayBand(&rcOutput);
	
	// Tell the control to release cached information
	m_wndEdit.FormatRange(NULL, FALSE);
	return true;
}