/*----------------------------------------------------------------------------*/
void set_update(HWND hwnd) {

    void checkcomment(int oo, int yn);
    int nextcmt(int);

    static int ac; RECT rect;

    if (caret==3)
        HideCaret(hwnd), caret=1;

    if (edp==NULL) {
        InvalidateRect(hwnd, NULL, FALSE);
        return;
    }

    if (upd) checkcomment(fpga,pgy+2);
    setsb(hwnd);

    if (GetFocus() == hwnd)
        SetCaretPos(zx0+(curx-clft)*zx-My_CaretSize/2, zy0+cury*zy);

    //if (chg_0!=changed()) setwtext();

    rect.top   = rect.left=0;
    rect.right = cwx+FRM;

    switch (upd) {
    case 16:                        // color update
    case 4:                         // scroll up
    case 2:                         // scroll dn
    case 1:                         // update all
        rect.bottom = cwy+FRM;
        break;

    case 8:                         // line update
        if (langflg && ac!=nextcmt(fpos))
        {
            rect.bottom = cwy + FRM;
            break;
        }

        rect.top    = zy0+zy*cury;
        rect.bottom = rect.top+zy;
        InvalidateRect(hwnd, &rect, FALSE);
        rect.top    = 0;

    case 0:
    default:
        rect.bottom=title_h;
    }

    InvalidateRect(hwnd, &rect, FALSE);
    if (langflg) ac=nextcmt(fpos);
    upd=0;
}