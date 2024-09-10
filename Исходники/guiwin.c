static void gwdraw(GUIWIN *gw, long fg, long bg, int bits, Char *text, int len)

{
    register int    i;
    GUI_WINDOW      *gwp = (GUI_WINDOW *)gw;
    COLORREF        fgc, bgc;
    HBRUSH	    hBrush, hPrevBrush;
    HPEN            hPen, hPrevPen;
    HDC		    hDC;
    HFONT           hFont;
    RECT            rect;
    int             ileft;
    int             xleft, xcenter, xright, ytop, ycenter, ybottom, radius;
    UINT	    options;

    /* Italics are slanted rightward from the bottom of the character cell.
     * We'd like for them to look slanted from the center of the characters,
     * and we can achieve that effect by shifting italic text slightly leftward.
     */
    ileft = 0;
    if ((bits & COLOR_GRAPHIC) != COLOR_GRAPHIC && (bits & COLOR_ITALIC))
        ileft = (gwp->ycsize - 3) / 6; /* just a guess */

    /* Convert fg and bg args into COLORREF values */
    fgc = (COLORREF)fg;
    bgc = (COLORREF)bg;

    /* compute the update RECT */
    rect.top = gwp->currow * gwp->ycsize;
    rect.left = gwp->curcol * gwp->xcsize + gwp->xcsize / 2;
    rect.bottom = rect.top + gwp->ycsize;
    rect.right = rect.left + gwp->xcsize * len;

    /* Get the window's DC */
    hDC = GetDC (gwp->clientHWnd);
    SetMapMode (hDC, MM_TEXT);

    /* hide caret */
    if (gwp->cursor_type != CURSOR_NONE && gwp->clientHWnd == GetFocus ())
    {
        HideCaret (gwp->clientHWnd);
        gwp->cursor_type = CURSOR_NONE;
    }

    /* graphic chars are a special case */
    if ((bits & COLOR_GRAPHIC) == COLOR_GRAPHIC)
    {
        /* Strip out the COLOR_GRAPHIC bits */
        bits &= ~COLOR_GRAPHIC;

        /* Erase the area */
#ifdef FEATURE_IMAGE
        if (normalimage && (long)bgc == colorinfo[COLOR_FONT_NORMAL].bg)
        {
            gw_erase_rect(hDC, &rect, normalimage, gwp->scrolled);
        }
        else if (idleimage && (long)bgc == colorinfo[COLOR_FONT_IDLE].bg)
        {
            gw_erase_rect(hDC, &rect, idleimage, gwp->scrolled);
        }
        else
#endif
        {
            hBrush = CreateSolidBrush (bgc);
            FillRect (hDC, &rect, hBrush);
            DeleteObject(hBrush);
        }

        /* Select the foreground color */
        hPen = CreatePen(PS_SOLID, 0, fgc);
        hPrevPen = SelectObject(hDC, hPen);

        /* Find special points in the first character cell */
        radius = gwp->xcsize / 3;
        xleft = rect.left;
        xright = xleft + gwp->xcsize;
        xcenter = (xleft + xright) / 2;
        ytop = rect.top;
        ybottom = rect.bottom;
        ycenter = (ytop + ybottom) / 2;

        /* For each graphic character... */
        for (i = 0; i < len; text++, i++)
        {
            /* Draw line segments, as appropriate for this character */
            if (strchr("123456|", *text))
            {
                MoveToEx(hDC, xcenter, ytop, NULL);
                LineTo(hDC, xcenter, ycenter);
            }
            if (strchr("456789|", *text))
            {
                MoveToEx(hDC, xcenter, ycenter, NULL);
                LineTo(hDC, xcenter, ybottom);
            }
            if (strchr("235689-", *text))
            {
                MoveToEx(hDC, xleft, ycenter, NULL);
                LineTo(hDC, xcenter, ycenter);
            }
            if (strchr("124578-", *text))
            {
                MoveToEx(hDC, xcenter, ycenter, NULL);
                LineTo(hDC, xright, ycenter);
            }
            if (*text == 'o')
            {
                Arc(hDC, xcenter - radius, ycenter - radius,
                    xcenter + radius, ycenter + radius,
                    xcenter - radius, ycenter,  xcenter - radius, ycenter);
            }
            if (*text == '*')
            {
                HBRUSH	oldbrush, newbrush;
                newbrush = CreateSolidBrush(fgc);
                oldbrush = SelectObject(hDC, newbrush);
                Pie(hDC, xcenter - radius, ycenter - radius,
                    xcenter + radius, ycenter + radius,
                    xcenter - radius, ycenter,  xcenter - radius, ycenter);
                SelectObject(hDC, oldbrush);
                DeleteObject(newbrush);
            }

            /* Advance the points to the next cell */
            xleft = xright;
            xcenter += gwp->xcsize;
            xright += gwp->xcsize;
        }

        /* Restore foreground color to its previous value, so we can delete
         * the local hPen object.
         */
        SelectObject(hDC, hPrevPen);
        DeleteObject(hPen);
    }
    else
    {
        /* Find a font with the right bold/italic/underlined attributes */
        i = 0;
        if (bits & COLOR_BOLD) i += 1;
        if (bits & COLOR_ITALIC) i += 2;
        if (bits & COLOR_UNDERLINED) i += 4;
        hFont = gwp->fonts[i];

        /* prepare DC & output text */
        SetTextColor(hDC, fgc);
        SetBkColor(hDC, bgc);
        SetBkMode(hDC, OPAQUE);
        SelectObject(hDC, hFont);
        options = ETO_OPAQUE | ETO_CLIPPED;
#ifdef FEATURE_IMAGE
        if (normalimage && (long)bgc == colorinfo[COLOR_FONT_NORMAL].bg)
        {
            gw_erase_rect(hDC, &rect, normalimage, gwp->scrolled);
            options = ETO_CLIPPED;
            SetBkMode(hDC, TRANSPARENT);
        }
        else if (idleimage && (long)bgc == colorinfo[COLOR_FONT_IDLE].bg)
        {
            gw_erase_rect(hDC, &rect, idleimage, gwp->scrolled);
            options = ETO_CLIPPED;
            SetBkMode(hDC, TRANSPARENT);
        }
#endif
        ExtTextOut(hDC, rect.left - ileft, rect.top, options, &rect,
                   (char *)text, len, gwp->font_size_array);
#ifdef FEATURE_IMAGE
        SetBkColor(hDC, bgc);
        SetBkMode(hDC, OPAQUE);
#endif
    }

    /* If COLOR_BOXED then draw a rectangle around the text */
    if (bits & (COLOR_BOXED | COLOR_LEFTBOX | COLOR_RIGHTBOX))
    {
        /* Select the foreground color */
        hPen = CreatePen(PS_SOLID, 0, fgc);
        hPrevPen = SelectObject(hDC, hPen);

        /* Draw the rectangle */
        if (bits & COLOR_BOXED)
        {
            MoveToEx(hDC, rect.left, rect.top, NULL);
            LineTo(hDC, rect.right, rect.top);
            MoveToEx(hDC, rect.left, rect.bottom - 1, NULL);
            LineTo(hDC, rect.right, rect.bottom - 1);
        }
        if (bits & COLOR_RIGHTBOX)
        {
            MoveToEx(hDC, rect.right - 1, rect.top, NULL);
            LineTo(hDC, rect.right - 1, rect.bottom);
        }
        if (bits & COLOR_LEFTBOX)
        {
            MoveToEx(hDC, rect.left, rect.top, NULL);
            LineTo(hDC, rect.left, rect.bottom);
        }

        /* Restore foreground color to its previous value, so we can delete
         * the local hPen object.
         */
        SelectObject(hDC, hPrevPen);
        DeleteObject(hPen);
    }

    /* release the window's device context */
    ReleaseDC(gwp->clientHWnd, hDC);

    /* update cursor position */
    gwp->curcol += len;
}