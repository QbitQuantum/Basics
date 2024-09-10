void CardButton::Draw(HDC hdc, bool fNormal)
{
    SIZE textsize;
    int x, y;        //text x, y
    int ix, iy;        //icon x, y
    int iconwidth = 0;

    RECT cliprect;

    if(fVisible == 0) return;

    if(hFont == 0)
        SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
    else
        SelectObject(hdc, hFont);

    GetTextExtentPoint32(hdc, szText, lstrlen(szText), &textsize);

    if(hIcon)
    {
        x = rect.left + 32 + 8;
    }
    else
    {
        if(uStyle & CB_ALIGN_LEFT)
        {
            x = rect.left + iconwidth;
        }
        else if(uStyle & CB_ALIGN_RIGHT)
        {
            x = rect.left + (rect.right-rect.left-iconwidth-textsize.cx);
        }
        else    //centered
        {
            x = rect.right - rect.left - iconwidth;
            x = (x - textsize.cx) / 2;
            x += rect.left + iconwidth;
        }
    }

    y = rect.bottom - rect.top;
    y = (y - textsize.cy) / 2;
    y += rect.top;

    //calc icon position..
    ix = rect.left + 4;
    iy = rect.top + (rect.bottom-rect.top-32) / 2;

    //if button is pressed, then shift text
    if(fNormal == false && (uStyle & CB_PUSHBUTTON))
    {
        x += 1;
        y += 1;
        ix += 1;
        iy += 1;
    }

    SetRect(&cliprect, x, y, x+textsize.cx, y+textsize.cy);
    ExcludeClipRect(hdc, x, y, x+textsize.cx, y+textsize.cy);

    //
    //    Calc icon pos
    //

    if(hIcon)
    {
        ExcludeClipRect(hdc, ix, iy, ix + 32, iy + 32);
    }

    if(uStyle & CB_PUSHBUTTON)
    {
        DrawRect(hdc, &rect, fNormal);

        SetBkColor(hdc,   MAKE_PALETTERGB(crBack));
        SetTextColor(hdc, crText);//MAKE_PALETTERGB(crText));

        SelectClipRgn(hdc, 0);

        ExtTextOut(hdc, x, y, ETO_OPAQUE, &cliprect, szText, lstrlen(szText), 0);
    }
    else
    {
        SetBkColor(hdc,      MAKE_PALETTERGB(crBack));
        SetTextColor(hdc, crText);//MAKE_PALETTERGB(crText));

        SelectClipRgn(hdc, 0);

        ExtTextOut(hdc, x, y, ETO_OPAQUE, &rect, szText, lstrlen(szText), 0);
    }

    if(hIcon)
    {
        HBRUSH hbr = CreateSolidBrush(MAKE_PALETTERGB(crBack));
        DrawIconEx(hdc, ix, iy, hIcon, 32, 32, 0, hbr, 0);
        DeleteObject(hbr);
    }

}