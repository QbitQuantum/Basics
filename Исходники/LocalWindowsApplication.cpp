LocalWindowsApplication::LocalWindowsApplication(HINSTANCE hInstance,
        const TCHAR *windowClassName)
    : WindowsApplication(hInstance, windowClassName)
{
    HWINSTA winSta = 0;

    winSta = OpenWindowStation(_T("WinSta0"), TRUE, GENERIC_ALL);

    if (winSta== 0) {
        throw SystemException();
    }

    if (SetProcessWindowStation(winSta) == 0) {
        CloseWindowStation(winSta);
        throw SystemException();
    }

    CloseWindowStation(winSta);

    // FIXME: why we don't check returning values?
    DesktopSelector::selectDesktop();
}