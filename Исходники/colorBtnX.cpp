void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    CDC* pDC = CDC::FromHandle(lpDIS->hDC);

    UINT state = lpDIS->itemState;
    CRect focusRect, btnRect;
    focusRect.CopyRect(&lpDIS->rcItem);
    btnRect.CopyRect(&lpDIS->rcItem);

    //
    // Set the focus rectangle to just past the border decoration
    //
    focusRect.left += 4;
    focusRect.right -= 4;
    focusRect.top += 4;
    focusRect.bottom -= 4;

    //
    // Retrieve the button's caption
    //
    const int bufSize = 512;
    TCHAR buffer[bufSize];
    GetWindowText(buffer, bufSize);


    //
    // Draw and label the button using draw methods
    //
    DrawFilledRect(pDC, btnRect, GetBGColor());
    DrawFrame(pDC, btnRect, GetBevel());
    DrawButtonText(pDC, btnRect, buffer, GetFGColor());


    //
    // Now, depending upon the state, redraw the button (down image) if it is selected,
    // place a focus rectangle on it, or redisplay the caption if it is disabled
    //
    if (state & ODS_FOCUS) {
        DrawFocusRect(lpDIS->hDC, (LPRECT)&focusRect);
        if (state & ODS_SELECTED) {
            DrawFilledRect(pDC, btnRect, GetBGColor());
            DrawFrame(pDC, btnRect, -1);


// ----> Changes!	// changes by RW:

            // move the button text if it is pressed...
            CRect rectPressedBtnText = btnRect;

            // to the right and bottom...
            rectPressedBtnText.OffsetRect( 1, 1 );

            // ... and now paint it!
            DrawButtonText(pDC, rectPressedBtnText, buffer, GetFGColor());

            // DrawButtonText(pDC, btnRect, buffer, GetFGColor());
            DrawFocusRect(lpDIS->hDC, (LPRECT)&focusRect);
        }
    }
    else if (state & ODS_DISABLED) {
        //COLORREF disabledColor = bg ^ 0xFFFFFF; // contrasting color
        DrawButtonText(pDC, btnRect, buffer, GetDisabledColor());
    }
}