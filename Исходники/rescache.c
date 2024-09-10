KHMEXP void KHMAPI
khui_ilist_draw(khui_ilist * il,
                int idx,
                HDC dc,
                int x,
                int y,
                int opt) {
    HDC dci;
    HBITMAP hb_oldi;

    if(idx < 0)
        return;

    dci = CreateCompatibleDC(dc);

    hb_oldi = SelectObject(dci, il->img);

    /*BitBlt(dc, x, y, il->cx, il->cy, dci, idx*il->cx, 0, SRCCOPY); */
    MaskBlt(dc, x, y, il->cx, il->cy, dci, idx * il->cx, 0, il->mask, idx * il->cx, 0, MAKEROP4(SRCPAINT, SRCCOPY));
/*    MaskBlt(dc, x, y, il->cx, il->cy, dci, idx * il->cx, 0, il->mask, idx * il->cx, 0, MAKEROP4(SRCINVERT, SRCCOPY)); */

    SelectObject(dci, hb_oldi);

    DeleteDC(dci);
}