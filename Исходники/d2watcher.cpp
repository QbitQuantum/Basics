//-------------------------------------------------------------------------------------------------
void D2Watcher::flashWindow(uint count) {
    FLASHWINFO flash;
    flash.cbSize = sizeof(FLASHWINFO);
    flash.hwnd = mD2Hwnd;
    flash.dwFlags = FLASHW_TRAY;
    flash.uCount = count;
    flash.dwTimeout = 0;
    FlashWindowEx(&flash);
}