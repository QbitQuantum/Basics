void CNewHeaderCtrl::DoPaint(CDC *pDC)
{
	CRect rect, rcItem;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap bmp;
	memDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBmp = memDC.SelectObject(&bmp);

	memDC.SetBkMode(TRANSPARENT);
	memDC.SetTextColor(m_colorText);
	memDC.SetStretchBltMode(HALFTONE);

	CFont* pOldFont = memDC.SelectObject(&m_font);

	// Ìî³ä±³¾°
	if (m_imgHeader.IsNull())
	{
		memDC.FillRect(&rect, &m_brushBack);
	}
	else
	{
		m_imgHeader.Draw(memDC, rect);
	}

	CPen *pOldPen;

	int nItems = GetItemCount();
	for (int i = 0; i < nItems; ++i)
	{
		TCHAR buf[256];
		HDITEM hditem;

		hditem.mask = HDI_TEXT | HDI_FORMAT | HDI_ORDER;
		hditem.pszText = buf;
		hditem.cchTextMax = 255;
		GetItem(i, &hditem);
		GetItemRect(i, &rcItem);

		if (rcItem.IsRectEmpty())
		{
			continue;
		}

		// »­·Ö¸îÏß
		pOldPen = memDC.SelectObject(&m_penVerticalLine);
		memDC.MoveTo(rcItem.right-1, 0);
		memDC.LineTo(rcItem.right-1, rcItem.bottom);
		memDC.SelectObject(pOldPen);
		//image.LoadFromResource(AfxGetResourceHandle(), IDB_BITMAP_HEADER_SPLIT);
		//image.Draw(memDC, rcItem.right - 1, rcItem.top);
		//image.Destroy();

		CRect rcText = rcItem;
		rcText.DeflateRect(4, 0, 10, 0);
		if (i == m_nCheckColumn)
		{
			CPen pen(PS_SOLID, 1, RGB(0,0,0));
			pOldPen = memDC.SelectObject(&pen);
			CRect rcCheck = rcText;
			rcCheck.right = rcCheck.left + 12;
			rcCheck.top = rcCheck.top + rcCheck.Height()/2 - 5;
			rcCheck.bottom = rcCheck.top + 12;
			memDC.Rectangle(&rcCheck);
			if (m_bAllCheck)
			{
				int nArray[] = {1,7,1,8, 2,6,2,8, 3,7,3,9, 4,8,4,10, 5,8,5,10, 6,6,6,9, 7,4,7,7, 8,2,8,5, 9,2,9,3};
				int nCount = sizeof(nArray) / sizeof(nArray[0]) / 4;
				int nPot = 0;
				for (int n=0; n<nCount; ++n)
				{
					nPot = n * 4;
					memDC.MoveTo(rcCheck.left+nArray[nPot], rcCheck.top+nArray[nPot+1]);
					memDC.LineTo(rcCheck.left+nArray[nPot+2], rcCheck.top+nArray[nPot+3]);
				}
			}
			memDC.SelectObject(pOldPen);
			rcText.left = rcCheck.right + 2;
		}

		// »­ÎÄ×ÖºÍÅÅÐò¼ýÍ·
		UINT uFormat = DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX;
		if (hditem.fmt & HDF_RIGHT)
		{
			uFormat |= DT_RIGHT;
		}
		else if (hditem.fmt & HDF_CENTER)
		{
			uFormat |= DT_CENTER;
		}

		memDC.DrawText(buf, static_cast<int> (_tcslen(buf)), &rcText, uFormat);
		rcText.right = rcItem.right;
		rcText.left = rcText.right - 15;
		if (rcText.left >= rcItem.left)
		{
			if (hditem.fmt & HDF_SORTUP)
			{
				pOldPen = memDC.SelectObject(&m_penArrow);
				CPoint pt = rcText.CenterPoint();
				pt.Offset(0, -2);
				for (int j=0; j<5; ++j)
				{
					memDC.MoveTo(pt.x-j, pt.y);
					memDC.LineTo(pt.x+j, pt.y);
					++pt.y;
				}
				memDC.SelectObject(pOldPen);
			}
			else if (hditem.fmt & HDF_SORTDOWN)
			{
				pOldPen = memDC.SelectObject(&m_penArrow);
				CPoint pt = rcText.CenterPoint();
				pt.Offset(0, 2);
				for (int j=0; j<5; ++j)
				{
					memDC.MoveTo(pt.x-j, pt.y);
					memDC.LineTo(pt.x+j, pt.y);
					--pt.y;
				}
				memDC.SelectObject(pOldPen);
			}
		}
	}

	memDC.SelectObject(pOldFont);

	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);
	memDC.SelectObject(pOldBmp);
}