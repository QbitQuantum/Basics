void CTextInputCtrl::SetCompositionFont()
{
    HIMC himc = ImmGetContext(_hwnd);
    if (himc)
    {
        ImmSetCompositionFont(himc, &_lfCurrentFont);
    }
    ImmReleaseContext(_hwnd, himc);
}