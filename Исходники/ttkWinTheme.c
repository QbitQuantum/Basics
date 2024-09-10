static void TroughElementDraw(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    Drawable d, Ttk_Box b, unsigned int state)
{
    TroughClientData *cd = clientData;
    TkWinDCState dcState;
    HDC hdc = TkWinGetDrawableDC(Tk_Display(tkwin), d, &dcState);
    HBRUSH hbr;
    COLORREF bk, oldbk, oldtxt;

    hbr = SelectObject(hdc, GetSysColorBrush(COLOR_SCROLLBAR));
    bk = GetSysColor(COLOR_3DHIGHLIGHT);
    oldtxt = SetTextColor(hdc, GetSysColor(COLOR_3DFACE));
    oldbk = SetBkColor(hdc, bk);

    /* WAS: if (bk (COLOR_3DHIGHLIGHT) == GetSysColor(COLOR_WINDOW)) ... */
    if (GetSysColor(COLOR_SCROLLBAR) == GetSysColor(COLOR_BTNFACE)) {
	/* Draw using the pattern brush */
	SelectObject(hdc, cd->PatternBrush);
    }

    PatBlt(hdc, b.x, b.y, b.width, b.height, PATCOPY);
    SetBkColor(hdc, oldbk);
    SetTextColor(hdc, oldtxt);
    SelectObject(hdc, hbr);
    TkWinReleaseDrawableDC(d, hdc, &dcState);
}