void CPtEmtDytCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	pdc->FillRect(rcBounds.operator LPCRECT(), CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	if (FALSE == m_PtEmt.IsGrayOK())	{
		pdc->SetTextAlign(TA_CENTER|TA_BASELINE);
		CString pszText = _T("PtEmtDyt");
		pdc->TextOut(rcBounds.Width() / 2, rcBounds.Height() / 2, pszText);
	}	else	{
		CRect rect(rcBounds);

		FLOAT winDiameter = rect.Width() * 1.0f;
		
		if (rect.Width() > rect.Height()) {
			winDiameter = rect.Height() * 1.0f;
		}

		winDiameter *= 0.9f;
		const FLOAT Diameter = 0.13f;
		m_Scale = winDiameter /Diameter;
		m_Center = CPoint(rect.right / 2, rect.bottom / 2);
		
		FLOAT mingray(1e20f), maxgray(-1e20f);
		
		for(SHORT i = 0; i < TotalElement; i++)
		{
			maxgray = max(maxgray, m_PtEmt.GetMGray(i));
			mingray = min(mingray, m_PtEmt.GetMGray(i));
		}
		
		TEXTMETRIC tm;
		CString str;
		CRgn rgn;
		CBrush br;	
		pdc->GetTextMetrics(&tm);
		CPoint ColorBarPoint(10, int(m_Center.y * 2.0 / 3 + 10 * tm.tmHeight));
		for(i = 0; i < lColorNum ;i++)
		{
			CRect rt(ColorBarPoint.x, ColorBarPoint.y-tm.tmHeight,
				ColorBarPoint.x+20, ColorBarPoint.y);
			br.CreateSolidBrush(lColorBegin + lColorEnd * (lColorNum-i-1) * lColorNum);
			pdc->FillRect(rt.operator LPCRECT(), &br);
			FLOAT ruler = mingray + (maxgray-mingray)*FLOAT(i)/(lColorNum - 1);
			str.Format(_T("%e"), ruler);
			ColorBarPoint.y -= tm.tmHeight;
			pdc->TextOut(ColorBarPoint.x + 23, ColorBarPoint.y, str);
			br.DeleteObject();
		}
		
		// Draw Gray Picture
		for (i = 0 ; i < InsideElement; i++)
		{
			if (fabs(m_PtEmt.GetMGray(i)) > 0.000001) 
			{
				CPoint point[4];
				for(SHORT j = 0; j < 4; j++)	{
					point[j] = _PToL(m_PtEmt.GetNodes(i, j));
				}
				
				SHORT clrLevel = SHORT((lColorNum-1) * (m_PtEmt.GetMGray(i)-mingray) / (maxgray-mingray));
				rgn.CreatePolygonRgn(point,4, ALTERNATE); 
				br.CreateSolidBrush(lColorBegin + lColorEnd * (lColorNum-clrLevel-1) * lColorNum);
				pdc->FillRgn(&rgn, &br);
				br.DeleteObject();
				rgn.DeleteObject();
			}
		}
		
		for (i=0; i < DetectorNum; i++)
		{
			FLOAT startangle,stopangle;
			POINT startpoint,stoppoint;
			COMPLEX startnode,stopnode;
			int CurDR = int(DetectorRadius * m_Scale);
			
			startangle = FLOAT(PIE*(2*i+1)/DetectorNum-DetectorAngle/2.0*PIE/180.0);
			stopangle = FLOAT(startangle+DetectorAngle*PIE/180.0);		
			startnode = COMPLEX(DetectorRadius*cos(startangle), DetectorRadius*sin(startangle));
			stopnode = COMPLEX(DetectorRadius*cos(stopangle), DetectorRadius*sin(stopangle));
			startpoint = _PToL(startnode);
			stoppoint = _PToL(stopnode);
			pdc->Arc(m_Center.x-CurDR + 60,m_Center.y-CurDR,m_Center.x+CurDR + 60,m_Center.y+CurDR,
				startpoint.x,startpoint.y,stoppoint.x,stoppoint.y);
		}
		
		CPoint pul, plr, pst;
		pul = _PToL(COMPLEX(-PipeRadius, -PipeRadius));
		plr = _PToL(COMPLEX(PipeRadius, PipeRadius));
		pst = _PToL(COMPLEX(PipeRadius, 0.0));
		pdc->Arc(pul.x,pul.y,plr.x,plr.y,pst.x,pst.y,pst.x,pst.y);
		
		pul = _PToL(COMPLEX(-ScreenRadius, -ScreenRadius));
		plr = _PToL(COMPLEX(ScreenRadius, ScreenRadius));
		pst = _PToL(COMPLEX(ScreenRadius, 0.0));
		pdc->Arc(pul.x,pul.y,plr.x,plr.y,pst.x,pst.y,pst.x,pst.y);			
	}
}