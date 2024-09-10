static
void MSWDrawXPBackground(wxButton *button, WXDRAWITEMSTRUCT *wxdis)
{
    LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT)wxdis;
    HDC hdc = lpDIS->hDC;
    UINT state = lpDIS->itemState;
    RECT rectBtn;
    CopyRect(&rectBtn, &lpDIS->rcItem);

    wxUxThemeHandle theme(button, L"BUTTON");
    int iState;

    if ( state & ODS_SELECTED )
    {
        iState = PBS_PRESSED;
    }
    else if ( button->HasCapture() || button->IsMouseInWindow() )
    {
        iState = PBS_HOT;
    }
    else if ( state & ODS_FOCUS )
    {
        iState = PBS_DEFAULTED;
    }
    else if ( state & ODS_DISABLED )
    {
        iState = PBS_DISABLED;
    }
    else
    {
        iState = PBS_NORMAL;
    }

    // draw parent background if needed
    if ( wxUxThemeEngine::Get()->IsThemeBackgroundPartiallyTransparent(theme,
                                                                       BP_PUSHBUTTON,
                                                                       iState) )
    {
        wxUxThemeEngine::Get()->DrawThemeParentBackground(GetHwndOf(button), hdc, &rectBtn);
    }

    // draw background
    wxUxThemeEngine::Get()->DrawThemeBackground(theme, hdc, BP_PUSHBUTTON, iState,
                                                &rectBtn, NULL);

    // calculate content area margins
    MARGINS margins;
    wxUxThemeEngine::Get()->GetThemeMargins(theme, hdc, BP_PUSHBUTTON, iState,
                                            TMT_CONTENTMARGINS, &rectBtn, &margins);
    RECT rectClient;
    ::CopyRect(&rectClient, &rectBtn);
    ::InflateRect(&rectClient, -margins.cxLeftWidth, -margins.cyTopHeight);

    // if focused and !nofocus rect
    if ( (state & ODS_FOCUS) && !(state & ODS_NOFOCUSRECT) )
    {
        DrawFocusRect(hdc, &rectClient);
    }

    if ( button->UseBgCol() )
    {
        COLORREF colBg = wxColourToRGB(button->GetBackgroundColour());
        HBRUSH hbrushBackground = ::CreateSolidBrush(colBg);

        // don't overwrite the focus rect
        ::InflateRect(&rectClient, -1, -1);
        FillRect(hdc, &rectClient, hbrushBackground);
        ::DeleteObject(hbrushBackground);
    }
}