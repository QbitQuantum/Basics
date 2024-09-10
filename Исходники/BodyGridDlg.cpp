void CBodyGridDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	if (!pDC) return;
//	int nSavedDC = dc.SaveDC();
	switch (nIDCtl)
	{

		case IDC_GRIDSTYLE:
		{
			LOGBRUSH lb;
			lb.lbStyle = BS_SOLID;
			lb.lbColor = RGB(100,100,100);
			CPen DotPen(PS_GEOMETRIC | PS_DOT, 1, &lb);
			CPen *pOldPen =  pDC->SelectObject(&DotPen);
			CBrush FillBrush(GetSysColor(COLOR_3DFACE));
			CBrush* pOldBrush = pDC->SelectObject(&FillBrush);
			CRect SRect ;
			GetDlgItem(IDC_GRIDSTYLE)->GetClientRect(&SRect);
			SRect.DeflateRect(2,2,2,2);
			pDC->Rectangle(&SRect);

			lb.lbStyle = BS_SOLID;
			lb.lbColor = m_Color;
			CPen CurvePen(PS_GEOMETRIC | m_Style, GetPenWidth(m_Width,false), &lb);

			pDC->SelectObject(&CurvePen);
			pDC->MoveTo(5,8);
			pDC->LineTo(SRect.right-5,8);
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrush);
			break;
		}

		case IDC_MINSTYLE:{
			LOGBRUSH lb;
			lb.lbStyle = BS_SOLID;
			lb.lbColor = RGB(100,100,100);
			CPen DotPen(PS_GEOMETRIC | PS_DOT, 1, &lb);
			CPen *pOldPen =  pDC->SelectObject(&DotPen);
			CBrush FillBrush(GetSysColor(COLOR_3DFACE));
			CBrush* pOldBrush = pDC->SelectObject(&FillBrush);
			CRect SRect ;
			GetDlgItem(IDC_MINSTYLE)->GetClientRect(&SRect);
			SRect.DeflateRect(2,2,2,2);
			pDC->Rectangle(&SRect);

			lb.lbStyle = BS_SOLID;
			lb.lbColor = m_MinColor;
			CPen CurvePen(PS_GEOMETRIC | m_MinStyle, GetPenWidth(m_MinWidth,false), &lb);

			pDC->SelectObject(&CurvePen);
			pDC->MoveTo(5,8);
			pDC->LineTo(SRect.right-5,8);
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrush);
			break;
		}


		case IDC_GRIDSTYLE2:{
			LOGBRUSH lb;
			lb.lbStyle = BS_SOLID;
			lb.lbColor = RGB(100,100,100);
			CPen DotPen(PS_GEOMETRIC | PS_DOT, 1, &lb);
			CPen *pOldPen =  pDC->SelectObject(&DotPen);
			CBrush FillBrush(GetSysColor(COLOR_3DFACE));
			CBrush* pOldBrush = pDC->SelectObject(&FillBrush);
			CRect SRect ;
			GetDlgItem(IDC_GRIDSTYLE2)->GetClientRect(&SRect);
			SRect.DeflateRect(2,2,2,2);
			pDC->Rectangle(&SRect);

			lb.lbStyle = BS_SOLID;
			lb.lbColor = m_Color2;
			CPen CurvePen(PS_GEOMETRIC | m_Style2, GetPenWidth(m_Width2,false), &lb);

			pDC->SelectObject(&CurvePen);
			pDC->MoveTo(5,8);
			pDC->LineTo(SRect.right-5,8);
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrush);
			break;
		}

		case IDC_MINSTYLE2:{
			LOGBRUSH lb;
			lb.lbStyle = BS_SOLID;
			lb.lbColor = RGB(100,100,100);
			CPen DotPen(PS_GEOMETRIC | PS_DOT, 1, &lb);
			CPen *pOldPen =  pDC->SelectObject(&DotPen);
			CBrush FillBrush(GetSysColor(COLOR_3DFACE));
			CBrush* pOldBrush = pDC->SelectObject(&FillBrush);
			CRect SRect ;
			GetDlgItem(IDC_MINSTYLE2)->GetClientRect(&SRect);
			SRect.DeflateRect(2,2,2,2);
			pDC->Rectangle(&SRect);

			lb.lbStyle = BS_SOLID;
			lb.lbColor = m_MinColor2;
			CPen CurvePen(PS_GEOMETRIC | m_MinStyle2, GetPenWidth(m_MinWidth2,false), &lb);

			pDC->SelectObject(&CurvePen);
			pDC->MoveTo(5,8);
			pDC->LineTo(SRect.right-5,8);
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrush);
			break;
		}

	}
}