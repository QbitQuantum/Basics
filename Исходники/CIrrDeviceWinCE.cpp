//! sets the caption of the window
void CIrrDeviceWinCE::setWindowCaption(const wchar_t* text)
{
    SetWindowTextW(HWnd, text);
}