void HandleMouseScrollEvents(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LPSCROLLSTATE state)
{
    SCROLLINFO si;
    int Delta;
    int NewPos;

    si.cbSize = sizeof(si);
    si.fMask = SIF_PAGE;
    GetScrollInfo(hWnd, SB_VERT, &si);

    if (Globals.uLinesToScroll == WHEEL_PAGESCROLL)
    {
        NewPos = si.nPage;
    }
    else
    {
        NewPos = Globals.uLinesToScroll * 5;
    }

    if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
    {
        NewPos = state->CurrentY - NewPos;
    }
    else
    {
        NewPos = state->CurrentY + NewPos;
    }

    NewPos = min(state->MaxY, max(0, NewPos));

    if (NewPos == state->CurrentY)
    {
        return;
    }

    Delta = NewPos - state->CurrentY;

    state->CurrentY = NewPos;

    ScrollWindowEx(hWnd, 0, -Delta, NULL, NULL, NULL, NULL, SW_INVALIDATE);

    si.cbSize = sizeof(si);
    si.fMask = SIF_POS;
    si.nPos = state->CurrentY;
    SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
}