static LRESULT CALLBACK WndProcFrameRateAssociated(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    if (WM_MOVING == msg ||
        WM_SIZING == msg ||
        WM_WINDOWPOSCHANGED  == msg ||
        WM_MOVE == msg) {
        FrameRateWnd *w = (FrameRateWnd*) dwRefData;
        PositionWindow(w, w->maxSizeSoFar);
    }
    return DefSubclassProc(hwnd, msg, wp, lp);
}