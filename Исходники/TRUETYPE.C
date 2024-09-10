//*************************************************************************
// DoPaint -- this is the WM_PAINT action routine for the main window.
// It places the TrueType logo in the upper left corner of the window, draws
// a "fan hub" around it, and draws "fan leaves" of text out from the hub.
// These leaves are scaled to reach the bottom and the right edge of the
// window, by defining an ellipse centered on the TrueType logo which just
// touches those two edges.  The text strings span the distance from the
// hub to the ellipse along radial lines, and are both scaled and rotated.
//     Depending on user-set state variables, the ellipse and baselines
// for the text fan may be shown (ShowAlignmentMarks), and/or the text may
// be shadowed (ShadowAll).  Other attributes, such as bolding or
// italicization, may be selected from the font dialog box.
//*************************************************************************
void DoPaint()
{
    PAINTSTRUCT       PaintInfo;
    HDC               hDC;
    LOGFONT           FontRec;
    OUTLINETEXTMETRIC FontMetric;
    int               FontHeight, x, y, j, k;
    WORD              BaseWidth, DesiredExtent, FanTextLen;
    float             Theta;
    LPCSTR            P;
    RECT              R;
    long              TE;
    int               d;

    BeginPaint(hwnd, &PaintInfo);

    hDC = PaintInfo.hdc;
    P = ArcText;
    FanTextLen = strlen(FanText);

    // save device context; easiest way to preserve current state
    SaveDC(hDC);

    // set initial font data (for TrueType logo)
    FontRec = CornerFontRec;
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(128,128,128));
    FontRec.lfHeight = FontRec.lfHeight * 2;
    FontRec.lfWidth = floor(FontRec.lfWidth * 2.1);

    // create the TrueType logo
    SelectObject(hDC, CreateFontIndirect(&FontRec));
    TextOut(hDC, 18, 5, "T", 1);
    SetTextColor(hDC, RGB(0,0,0));
    TextOut(hDC, 32, 13,"T", 1);

    // determine window dimensions & set up fan text parameters
    GetClientRect(hwnd, &R);
    FontRec = MainFontRec;
    DeleteObject(SelectObject(hDC, CreateFontIndirect(&FontRec)));
    GetOutlineTextMetrics(hDC, sizeof(FontMetric), &FontMetric);
    FontHeight = FontMetric.otmTextMetrics.tmHeight;
    SetViewportOrg(hDC, FontHeight+2, 0);
    R.right -= FontHeight+2;
    BaseWidth = LOWORD(GetTextExtent(hDC, FanText, FanTextLen));

    // get a "black brush" for drawing operations
    SelectObject(hDC, GetStockObject(NULL_BRUSH));

    // if we want to show the alignment marks, draw the bounding ellipse
    if (ShowAlignmentMarks)
    {
        Ellipse(hDC, -R.right, -R.bottom, R.right, R.bottom);
    }

    // draw the "hub" of the fan
    Ellipse(hDC, -(Radius-5), -(Radius-5), (Radius-5), Radius-5);
    Ellipse(hDC, -(Radius-10), -(Radius-10), (Radius-10), Radius-10);

    SetTextColor(hDC, FanColor[0]);

    // loop over the "fan leaves"
    for ( d = 27; d <= 36; d++)
    {
        x = ROUND(Radius * cos(d * Deg2Rad));
        y = ROUND(Radius * sin(-d * Deg2Rad)); // -d because y axis is inverted

        Theta = -d * Deg2Rad;
        if (x)
        {
            Theta = atan((R.right / (R.bottom * 1.0)) * (y / (x * 1.0)));
        }

        j = ROUND(R.right * cos(Theta));
        k = ROUND(R.bottom * sin(Theta));

        if (ShowAlignmentMarks)
        {
            MoveTo(hDC, x,y);
            LineTo(hDC, j,k);
        }

        DesiredExtent = ROUND(sqrt(SQR(x*1.0 - j) + SQR(y*1.0 - k))) - 5;
        FontRec = MainFontRec;
        FontRec.lfEscapement = d * 100;
        FontRec.lfWidth = floor((FontMetric.otmTextMetrics.tmAveCharWidth) *
                                (DesiredExtent / (BaseWidth * 1.0)));
        DeleteObject(SelectObject(hDC, CreateFontIndirect(&FontRec)));
        TE = GetTextExtent(hDC, FanText, FanTextLen);

        for ( ;(LOWORD(TE) > DesiredExtent) && (FontRec.lfWidth);
             FontRec.lfWidth-- )
        {
            // Shave off some character width until the string fits 
            DeleteObject(SelectObject(hDC, CreateFontIndirect(&FontRec)));
            TE = GetTextExtent(hDC, FanText, FanTextLen);
        }

        // Expand the string if necessary to make it fit the desired extent 
        if (LOWORD(TE) < DesiredExtent)
          { SetTextJustification(hDC,DesiredExtent - LOWORD(TE), 3); }
        if (ShadowAll)
        {
            SetTextColor(hDC, RGB(0,0,0));
            TextOut(hDC, x+2, y+1, FanText, FanTextLen);
        }
        SetTextColor(hDC, FanColor[d - 27]);
        TextOut(hDC, x, y, FanText, FanTextLen);
        // clear justifier's internal error accumulator 
        SetTextJustification(hDC,0,0);

        if (P[0])
        {
            FontRec = CornerFontRec;
            FontRec.lfEscapement = (d+10) * 100;
            FontRec.lfWidth = 0;
            DeleteObject(SelectObject(hDC, CreateFontIndirect(&FontRec)));
            SetTextColor(hDC, 0);
            x = floor((Radius - FontHeight - 5) * cos(d * Deg2Rad));
            y = floor((Radius - FontHeight - 5) * sin(-d * Deg2Rad));
            TextOut(hDC, x, y, P, 1);
            P++;
        } // if
    } // for d

    // lose the fan font, selecting in the Borland text font
    DeleteObject(SelectObject(hDC, CreateFontIndirect(&BorlandFontRec)));
    TE = GetTextExtent(hDC, BorlandText, strlen(BorlandText));
    SetTextColor(hDC, RGB(0,0,0));
    // write the Borland text in the lower right corner, with a shadow effect
    TextOut(hDC, R.right - LOWORD(TE), R.bottom - HIWORD(TE), BorlandText,
            strlen(BorlandText));
    SetTextColor(hDC, RGB(255,0,0));
    TextOut(hDC, R.right - LOWORD(TE) - 5, R.bottom - HIWORD(TE), BorlandText,
            strlen(BorlandText));

    DeleteObject(SelectObject(hDC, GetStockObject(SYSTEM_FONT)));
    // restore the saved DC; easiest way to reset to entry state
    RestoreDC(hDC, -1);
    EndPaint(hwnd, &PaintInfo);
} // end of DoPaint()