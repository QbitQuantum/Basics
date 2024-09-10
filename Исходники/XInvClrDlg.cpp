void CXInvClrDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    if (!pDC) return;
    int nSavedDC = pDC->SaveDC();
    if(nIDCtl==IDC_SPLINESTYLE)
    {
        LOGBRUSH lb;
        lb.lbStyle = BS_SOLID;
        lb.lbColor = RGB(100,100,100);
        CPen DotPen(PS_GEOMETRIC | PS_DOT, 1, &lb);
        CPen *pOldPen =  pDC->SelectObject(&DotPen);
        CBrush FillBrush(GetSysColor(COLOR_3DFACE));
        CBrush* pOldBrush = pDC->SelectObject(&FillBrush);
        CRect SRect ;
        GetDlgItem(IDC_SPLINESTYLE)->GetClientRect(&SRect);
        SRect.DeflateRect(2,2,2,2);
        pDC->Rectangle(&SRect);

        lb.lbStyle = BS_SOLID;
        lb.lbColor = m_SplineClr;
        CPen CurvePen(PS_GEOMETRIC | m_SplineStyle, GetPenWidth(m_SplineWidth,false), &lb);

        pDC->SelectObject(&CurvePen);
        pDC->MoveTo(5,8);
        pDC->LineTo(SRect.right-5,8);
        pDC->SelectObject(pOldPen);
        pDC->SelectObject(pOldBrush);
        pDC->RestoreDC(nSavedDC);
    }
    if(nIDCtl==IDC_REFLECTEDSTYLE)
    {
        LOGBRUSH lb;
        lb.lbStyle = BS_SOLID;
        lb.lbColor = RGB(100,100,100);
        CPen DotPen(PS_GEOMETRIC | PS_DOT, 1, &lb);
        CPen *pOldPen =  pDC->SelectObject(&DotPen);
        CBrush FillBrush(GetSysColor(COLOR_3DFACE));
        CBrush* pOldBrush = pDC->SelectObject(&FillBrush);
        CRect SRect ;
        GetDlgItem(IDC_REFLECTEDSTYLE)->GetClientRect(&SRect);
        SRect.DeflateRect(2,2,2,2);
        pDC->Rectangle(&SRect);

        lb.lbStyle = BS_SOLID;
        lb.lbColor = m_ReflectedClr;
        CPen CurvePen(PS_GEOMETRIC | m_ReflectedStyle, GetPenWidth(m_ReflectedWidth,false), &lb);

        pDC->SelectObject(&CurvePen);
        pDC->MoveTo(5,8);
        pDC->LineTo(SRect.right-5,8);
        pDC->SelectObject(pOldPen);
        pDC->SelectObject(pOldBrush);
        pDC->RestoreDC(nSavedDC);
    }
    else if(nIDCtl==IDC_MODFOIL)
    {
        LOGBRUSH lb;
        lb.lbStyle = BS_SOLID;
        lb.lbColor = RGB(100,100,100);
        CPen DotPen(PS_GEOMETRIC | PS_DOT, 1, &lb);
        CPen *pOldPen =  pDC->SelectObject(&DotPen);
        CBrush FillBrush(GetSysColor(COLOR_3DFACE));
        CBrush* pOldBrush = pDC->SelectObject(&FillBrush);
        CRect SRect ;
        GetDlgItem(IDC_MODFOIL)->GetClientRect(&SRect);
        SRect.DeflateRect(2,2,2,2);
        pDC->Rectangle(&SRect);

        lb.lbStyle = BS_SOLID;
        lb.lbColor = m_ModFoilClr;
        CPen CurvePen(PS_GEOMETRIC | m_ModFoilStyle, GetPenWidth(m_ModFoilWidth,false), &lb);

        pDC->SelectObject(&CurvePen);
        pDC->MoveTo(5,8);
        pDC->LineTo(SRect.right-5,8);
        pDC->SelectObject(pOldPen);
        pDC->SelectObject(pOldBrush);
        pDC->RestoreDC(nSavedDC);
    }
    else if(nIDCtl==IDC_REFFOIL)
    {
        LOGBRUSH lb;
        lb.lbStyle = BS_SOLID;
        lb.lbColor = RGB(100,100,100);
        CPen DotPen(PS_GEOMETRIC | PS_DOT, 1, &lb);
        CPen *pOldPen =  pDC->SelectObject(&DotPen);
        CBrush FillBrush(GetSysColor(COLOR_3DFACE));
        CBrush* pOldBrush = pDC->SelectObject(&FillBrush);
        CRect SRect ;
        GetDlgItem(IDC_REFFOIL)->GetClientRect(&SRect);
        SRect.DeflateRect(2,2,2,2);
        pDC->Rectangle(&SRect);

        lb.lbStyle = BS_SOLID;
        lb.lbColor = m_RefFoilClr;
        CPen CurvePen(PS_GEOMETRIC | m_RefFoilStyle, GetPenWidth(m_RefFoilWidth,false), &lb);

        pDC->SelectObject(&CurvePen);
        pDC->MoveTo(5,8);
        pDC->LineTo(SRect.right-5,8);
        pDC->SelectObject(pOldPen);
        pDC->SelectObject(pOldBrush);
        pDC->RestoreDC(nSavedDC);
    }
}