//im --- override to over the spot composition
void AwtTextComponent::SetCompositionWindow(RECT& rc)
{
    HWND hwnd = ImmGetHWnd();
    HIMC hIMC = ImmGetContext(hwnd);
    // rc is not used for text component.
    COMPOSITIONFORM cf = { CFS_FORCE_POSITION, {0,0}, {0,0,0,0} };
    GetCaretPos(&(cf.ptCurrentPos));
    // the proxy is the native focus owner and it contains the composition window
    // let's convert the position to a coordinate space relative to proxy
    ::MapWindowPoints(GetHWnd(), GetProxyFocusOwner(), (LPPOINT)&cf.ptCurrentPos, 1);
    ImmSetCompositionWindow(hIMC, &cf);

    LOGFONT lf;
    GetObject(m_hFont, sizeof(LOGFONT), &lf);
    ImmSetCompositionFont(hIMC, &lf);
    ImmReleaseContext(hwnd, hIMC);
}