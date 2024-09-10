BOOL CXTPSkinManagerClass::DrawThemeText(CDC* pDC, int iPartId, int iStateId, const CString& strText, DWORD dwFormat, const RECT *pRect)
{
    pDC->SetBkMode(TRANSPARENT);


    CRect rcCaptionMargins = GetThemeRect(iPartId, iStateId, TMT_CAPTIONMARGINS);
    rcCaptionMargins.top = rcCaptionMargins.bottom = 0;

    CRect rc(pRect);
    rc.DeflateRect(rcCaptionMargins);

    if (GetThemeEnumValue(iPartId, iStateId, TMT_CONTENTALIGNMENT) == CA_CENTER)
    {
        dwFormat |=  DT_CENTER;

    }

    pDC->SetTextColor(GetThemeColor(iPartId, iStateId, TMT_TEXTCOLOR, pDC->GetTextColor()));


    if (GetThemeEnumValue(iPartId, iStateId, TMT_TEXTSHADOWTYPE) == TST_SINGLE)
    {
        CSize sz = GetThemeSize(iPartId, iStateId, TMT_TEXTSHADOWOFFSET);

        if (sz != CSize(0, 0))
        {

            COLORREF clrShadow = GetThemeColor(iPartId, iStateId, TMT_TEXTSHADOWCOLOR);
            CRect rcShadow(rc);
            rcShadow.OffsetRect(sz);

            COLORREF clr = pDC->SetTextColor(clrShadow);
            pDC->DrawText(strText, rcShadow, dwFormat);
            pDC->SetTextColor(clr);
        }
    }

    pDC->DrawText(strText, rc, dwFormat);



    return TRUE;
}