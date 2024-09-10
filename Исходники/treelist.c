LRESULT TreeListCustomDraw(
    HWND hwndHeader,
    LPNMTVCUSTOMDRAW pdraw
)
{
    TCHAR               textbuf[MAX_PATH];
    TVITEMEX            item;
    HBRUSH              brush;
    HPEN                pen;
    RECT                hr, ir, subr;
    SIZE                tsz;
    LONG                i, c, cx;
    PTL_SUBITEMS        subitem;
    HGDIOBJ             prev;

    if ((pdraw->nmcd.dwDrawStage & CDDS_ITEM) == 0)
        return CDRF_NOTIFYITEMDRAW;

    RtlSecureZeroMemory(&item, sizeof(item));
    RtlSecureZeroMemory(&textbuf, sizeof(textbuf));
    item.mask = TVIF_TEXT | TVIF_HANDLE | TVIF_PARAM | TVIF_CHILDREN | TVIF_STATE;
    item.hItem = (HTREEITEM)pdraw->nmcd.dwItemSpec;
    item.cchTextMax = (sizeof(textbuf) / sizeof(TCHAR)) - 1;
    item.pszText = textbuf;
    TreeView_GetItem(pdraw->nmcd.hdr.hwndFrom, &item);
    subitem = (PTL_SUBITEMS)item.lParam;

    RtlSecureZeroMemory(&hr, sizeof(hr));
    TreeView_GetItemRect(pdraw->nmcd.hdr.hwndFrom, (HTREEITEM)pdraw->nmcd.dwItemSpec, &ir, TRUE);
    //FillRect(pdraw->nmcd.hdc, &pdraw->nmcd.rc, GetSysColorBrush(COLOR_WINDOW));

    if (item.cChildren == 1) {
        RtlSecureZeroMemory(&tsz, sizeof(tsz));
        if (GetThemePartSize(tl_theme, pdraw->nmcd.hdc, TVP_GLYPH, GLPS_CLOSED, NULL, TS_TRUE, &tsz) != S_OK) {
            tsz.cx = 8;
            tsz.cy = 8;
        }

        subr.top = ir.top + (((ir.bottom - ir.top) - tsz.cy) / 2);
        subr.bottom = subr.top + tsz.cy;
        subr.left = ir.left - tsz.cx - 3;
        subr.right = ir.left - 3;

        if ((item.state & TVIS_EXPANDED) == 0)
            i = GLPS_CLOSED;
        else
            i = GLPS_OPENED;

        DrawThemeBackground(tl_theme, pdraw->nmcd.hdc, TVP_GLYPH, i, &subr, NULL);
    }

    cx = 0;
    c = Header_GetItemCount(hwndHeader);
    for (i = 0; i < c; i++) {
        RtlSecureZeroMemory(&hr, sizeof(hr));
        Header_GetItemRect(hwndHeader, i, &hr);
        if (hr.right > cx)
            cx = hr.right;
    }

    if ((subitem) && ((pdraw->nmcd.uItemState & CDIS_FOCUS)) == 0) {
        if (subitem->ColorFlags & TLF_BGCOLOR_SET) {
            pdraw->clrTextBk = subitem->BgColor;
            SetBkColor(pdraw->nmcd.hdc, subitem->BgColor);
        }

        if (subitem->ColorFlags & TLF_FONTCOLOR_SET) {
            pdraw->clrText = subitem->FontColor;
            SetTextColor(pdraw->nmcd.hdc, subitem->FontColor);
        }
    }

    brush = CreateSolidBrush(pdraw->clrTextBk);
    subr.top = ir.top;
    subr.bottom = ir.bottom - 1;
    subr.left = ir.left;
    subr.right = cx;
    FillRect(pdraw->nmcd.hdc, &subr, brush);
    DeleteObject(brush);

    Header_GetItemRect(hwndHeader, 0, &hr);
    subr.right = hr.right - 3;
    subr.left += 3;
    DrawText(pdraw->nmcd.hdc, textbuf, -1, &subr, DT_END_ELLIPSIS | DT_VCENTER | DT_SINGLELINE);

    ir.right = cx;

    pen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_MENUBAR));
    prev = SelectObject(pdraw->nmcd.hdc, pen);

    for (i = 0; i < c; i++) {
        RtlSecureZeroMemory(&hr, sizeof(hr));
        Header_GetItemRect(hwndHeader, i, &hr);

        if ((i > 0) && subitem)
            if (i <= (LONG)subitem->Count)
                if (subitem->Text[i - 1]) {
                    subr.top = ir.top;
                    subr.bottom = ir.bottom;
                    subr.left = hr.left + 3;
                    subr.right = hr.right - 3;
                    DrawText(pdraw->nmcd.hdc, subitem->Text[i - 1], -1, &subr, DT_END_ELLIPSIS | DT_VCENTER | DT_SINGLELINE);
                }

        MoveToEx(pdraw->nmcd.hdc, hr.left, ir.bottom - 1, NULL);
        LineTo(pdraw->nmcd.hdc, hr.right - 1, ir.bottom - 1);
        LineTo(pdraw->nmcd.hdc, hr.right - 1, ir.top - 1);
    }

    SelectObject(pdraw->nmcd.hdc, prev);
    DeleteObject(pen);

    if ((pdraw->nmcd.uItemState & CDIS_FOCUS) != 0)
        DrawFocusRect(pdraw->nmcd.hdc, &ir);

    return CDRF_SKIPDEFAULT;
}