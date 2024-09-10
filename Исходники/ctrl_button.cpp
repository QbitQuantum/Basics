/**
 * name:	PaintThemeButton
 * desc:	Draws the themed button
 * param:	ctl			- BTNCTRL structure for the button
 *			hdcMem		- device context to draw to
 *			rcClient	- rectangle of the whole button
 * return:	nothing
 **/
static void __fastcall PaintThemeButton(BTNCTRL *ctl, HDC hdcMem, LPRECT rcClient)
{
    RECT rcText = { 0, 0, 0, 0 };
    WCHAR wszText[MAX_PATH] = { 0 };
    WORD ccText;

    // Draw the flat button
    if ((ctl->dwStyle & MBS_FLAT) && ctl->hThemeToolbar) {
        int state = IsWindowEnabled(ctl->hwnd)
                    ? (ctl->stateId == PBS_NORMAL && ctl->defbutton
                       ? PBS_DEFAULTED
                       : ctl->stateId)
                    : PBS_DISABLED;
        if (IsThemeBackgroundPartiallyTransparent(ctl->hThemeToolbar, TP_BUTTON, TBStateConvert2Flat(state))) {
            if (SUCCEEDED(DrawThemeParentBackground(ctl->hwnd, hdcMem, rcClient)))
                DrawThemeParentBackground(GetParent(ctl->hwnd), hdcMem, rcClient);
        }
        DrawThemeBackground(ctl->hThemeToolbar, hdcMem, TP_BUTTON, TBStateConvert2Flat(state), rcClient, rcClient);
    }
    else {
        // draw themed button background
        if (ctl->hThemeButton) {
            int state = IsWindowEnabled(ctl->hwnd)
                        ? (ctl->stateId == PBS_NORMAL && ctl->defbutton
                           ? PBS_DEFAULTED
                           : ctl->stateId)
                        : PBS_DISABLED;
            if (IsThemeBackgroundPartiallyTransparent(ctl->hThemeButton, BP_PUSHBUTTON, state)) {
                if (SUCCEEDED(DrawThemeParentBackground(ctl->hwnd, hdcMem, rcClient)))
                    DrawThemeParentBackground(GetParent(ctl->hwnd), hdcMem, rcClient);
            }
            DrawThemeBackground(ctl->hThemeButton, hdcMem, BP_PUSHBUTTON, state, rcClient, rcClient);
        }
    }

    // calculate text rect
    {
        RECT	sizeText;
        HFONT	hOldFont;

        ccText = GetWindowTextW(ctl->hwnd, wszText, _countof(wszText));

        if (ccText > 0) {
            hOldFont = (HFONT)SelectObject(hdcMem, ctl->hFont);

            GetThemeTextExtent(
                ctl->hThemeButton,
                hdcMem,
                BP_PUSHBUTTON,
                IsWindowEnabled(ctl->hwnd) ? ctl->stateId : PBS_DISABLED,
                wszText,
                ccText,
                DST_PREFIXTEXT,
                NULL,
                &sizeText);

            if (ctl->cHot) {
                RECT rcHot;

                GetThemeTextExtent(ctl->hThemeButton,
                                   hdcMem,
                                   BP_PUSHBUTTON,
                                   IsWindowEnabled(ctl->hwnd) ? ctl->stateId : PBS_DISABLED,
                                   L"&",
                                   1,
                                   DST_PREFIXTEXT,
                                   NULL,
                                   &rcHot);

                sizeText.right -= (rcHot.right - rcHot.left);
            }
            SelectObject(hdcMem, hOldFont);

            rcText.left = (ctl->hIcon) ? 0 : (rcClient->right - rcClient->left - (sizeText.right - sizeText.left)) / 2;
            rcText.top = (rcClient->bottom - rcClient->top - (sizeText.bottom - sizeText.top)) / 2;
            rcText.right = rcText.left + (sizeText.right - sizeText.left);
            rcText.bottom = rcText.top + (sizeText.bottom - sizeText.top);
            if (ctl->stateId == PBS_PRESSED) {
                OffsetRect(&rcText, 1, 1);
            }
        }
    }
    PaintIcon(ctl, hdcMem, &ccText, rcClient, &rcText);
    // draw text
    if (ccText > 0 && ctl->hThemeButton) {
        HFONT hOldFont = (HFONT)SelectObject(hdcMem, ctl->hFont);
        DrawThemeText(ctl->hThemeButton, hdcMem, BP_PUSHBUTTON, IsWindowEnabled(ctl->hwnd) ? ctl->stateId : PBS_DISABLED, wszText, ccText, DST_PREFIXTEXT, 0, &rcText);
        SelectObject(hdcMem, hOldFont);
    }
}