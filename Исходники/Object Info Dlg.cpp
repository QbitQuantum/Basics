void CEmptyListCtrl::OnPaint() 
{
    Default();
    if (GetItemCount() <= 0)
    {
        COLORREF clrText = ::g_PaintManager->GetColor(COLOR_WINDOWTEXT);
        COLORREF clrTextBk = ::g_PaintManager->GetColor(COLOR_WINDOW);

        CDC* pDC = GetDC();
        // Save dc state
        int nSavedDC = pDC->SaveDC();

        CRect rc;
        GetWindowRect(&rc);
        ScreenToClient(&rc);

        CHeaderCtrl* pHC;
        pHC = GetHeaderCtrl();
        if (pHC != NULL)
        {
            CRect rcH;
            pHC->GetItemRect(0, &rcH);
            rc.top += rcH.bottom;
        }
        rc.top += 10;

        CString strText; // The message you want!
		strText = OI_NONE;

        pDC->SetTextColor(clrText);
        pDC->SetBkColor(clrTextBk);
        pDC->FillRect(rc, &CBrush(clrTextBk));
        pDC->SelectObject(&m_Font);
        pDC->DrawText(strText, -1, rc, 
                      DT_CENTER | DT_WORDBREAK | DT_NOPREFIX | DT_NOCLIP);

        // Restore dc
        pDC->RestoreDC(nSavedDC);
        ReleaseDC(pDC);
    }
    // Do not call CListCtrl::OnPaint() for painting messages
}