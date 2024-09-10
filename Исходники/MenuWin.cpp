/*static*/
void MenuWin::ApplyNotifyByPositionStyleToNativeMenu(HMENU nativeMenu)
{
    MENUINFO menuInfo;
    ZeroMemory(&menuInfo, sizeof(MENUINFO)); 
    menuInfo.cbSize = sizeof(MENUINFO);
    menuInfo.fMask = MIM_APPLYTOSUBMENUS | MIM_STYLE;
    menuInfo.dwStyle = MNS_CHECKORBMP | MNS_NOTIFYBYPOS; 
    BOOL success = SetMenuInfo(nativeMenu, &menuInfo);

    if (!success) {
        string error = Win32Utils::QuickFormatMessage(GetLastError());
        throw ValueException::FromString("Could not set native menu style: " + error);
    }
}