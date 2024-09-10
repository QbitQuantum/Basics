void CListBoxEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    CDC dc;
    dc.Attach(lpDrawItemStruct->hDC);
    dc.SaveDC();

    RECT& r = lpDrawItemStruct->rcItem;

    if(lpDrawItemStruct->itemID != -1 &&
            (lpDrawItemStruct->itemAction == ODA_DRAWENTIRE ||
             lpDrawItemStruct->itemAction == ODA_SELECT))
    {
        LBEXTITEMSTRUCT& item = Items[lpDrawItemStruct->itemID];
        dc.SetROP2(R2_COPYPEN);

        int iBackIndex = COLOR_WINDOW;
        int iForeIndex = COLOR_WINDOWTEXT;
        BOOL bDrawCaptionOnly = FALSE;

        if(lpDrawItemStruct->itemAction == ODA_SELECT &&
                (lpDrawItemStruct->itemState & ODS_SELECTED))
        {
            iBackIndex = COLOR_HIGHLIGHT;
            iForeIndex = COLOR_HIGHLIGHTTEXT;
            bDrawCaptionOnly = item.iDataType != lbdBool ? TRUE : FALSE;
        }

        // draw background
        CBrush brush;
        brush.CreateSolidBrush(GetSysColor(iBackIndex));

        if(0)//!bDrawCaptionOnly)
            dc.FillRect(&r, &brush);
        else
        {
            CRect r2(&r);
            r2.right = iCaptionWidthPixels;
            dc.FillRect(r2, &brush);
        }

        // first, draw text
        dc.SetTextColor(GetSysColor(iForeIndex));
        dc.SetBkColor(GetSysColor(iBackIndex));
        dc.TextOut(r.left + 1, r.top+ 1, item.szCaption,
                   strlen(item.szCaption));

        if(!bDrawCaptionOnly)
        {
            // draw value ..
            char szText[128];
            GetItemText(lpDrawItemStruct->itemID, szText);
            dc.TextOut(r.left + iCaptionWidthPixels + 1, r.top + 1,
                       szText, strlen(szText));
        }

        // draw border.
        CPen pen(PS_SOLID, 1, RGB(200, 200, 200));
        dc.SelectObject(pen);
        dc.MoveTo(r.left, r.bottom-1);
        dc.LineTo(r.right, r.bottom-1);
        dc.MoveTo(r.left + iCaptionWidthPixels, r.top);
        dc.LineTo(r.left + iCaptionWidthPixels, r.bottom-1);
    }
    else if(lpDrawItemStruct->itemAction == ODA_FOCUS)
    {
        dc.DrawFocusRect(&r);
    }

    dc.RestoreDC(-1);
}