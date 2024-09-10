bool CIVStatusBar::IsOverURL(CPoint pt, CString & rstr )
{

	if ( ! IsWindowEnabled()  || !GetTopLevelParent()->IsWindowEnabled()   )
		return false;

	CStatusBarCtrl & sb = GetStatusBarCtrl();
	int iPart = -1;
	CRect rc;
	for (int i=0; i < sb.GetParts(0, NULL); i++ )
	{
		sb.GetRect (i, rc);
		if (rc.PtInRect(pt) && ( GetPaneStyle(i) & SBT_OWNERDRAW )  )
		{
			iPart = i;
			break;
		}
	}

	if (iPart == -1)
		return false;

	if ( ! (GetPaneStyle(iPart)  & SBPS_NOBORDERS) )
		rc.InflateRect(-GetSystemMetrics(SM_CYBORDER), -GetSystemMetrics(SM_CXBORDER));

	if (!rc.PtInRect(pt))
		return false;

	CString strText = GetPaneText(iPart);
	CDC * pDC = GetDC();

	CFont * pFont = GetFont();
	CFont fntURL;
	GetLinkFont(fntURL);
	
	CFont * pOldFont =  pDC->SelectObject (pFont);

	int x = CalcX (pDC, rc, strText);

	bool bFound = false;
	for (int i = 0; i < strText.GetLength();)
	{
		CSize szPos = FindURL (strText, i );
		if (szPos.cx != -1)
		{
			CString strStart = strText.Mid (i, szPos.cx-i);
			CRect rcURL;
			x += pDC->GetTextExtent (strStart).cx;
			rcURL.left = x;
	
			pFont = pDC->SelectObject (&fntURL);
		
			CString strURL = strText.Mid(szPos.cx, szPos.cy);
			
			CSize szURL =  pDC->GetTextExtent (strURL);
			x += szURL.cx;
			
			rcURL.right = x;
			rcURL.top = rc.top;
			rcURL.bottom = rc.top + szURL.cy;

			pDC->SelectObject (pFont);
			
			if (rcURL.PtInRect(pt))
			{
				rstr = strURL;
				bFound = true;
				break;
			}

			i = szPos.cx + szPos.cy;
		}
		else
			break;

	}

	pDC->SelectObject (pOldFont);


	return bFound;
}