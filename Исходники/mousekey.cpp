// This is less nice but more compatible for Notepad and MSWord for example
void PressKey(wchar key, bool hold = false, bool release = false) {
    if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9')) {
        HKL hKeyboardLayout = ::GetKeyboardLayout(0);
        SHORT nVK = VkKeyScanExW(key, hKeyboardLayout);
        UINT nScan = MapVirtualKeyExW(nVK, MAPVK_VK_TO_CHAR, hKeyboardLayout);
        if (!release)
            keybd_event((BYTE)nVK, (BYTE)nScan, 0, 0);
        if (!hold)
            keybd_event((BYTE)nVK, (BYTE)nScan, KEYEVENTF_KEYUP, 0);
    } else {
        String numStr = FormatIntDec(key, 5, '0');
        PressKeyVK(VK_LMENU, true);
        PressKeyVK(VK_NUMPAD0 + numStr[0] - '0');
        PressKeyVK(VK_NUMPAD0 + numStr[1] - '0');
        PressKeyVK(VK_NUMPAD0 + numStr[2] - '0');
        PressKeyVK(VK_NUMPAD0 + numStr[3] - '0');
        PressKeyVK(VK_NUMPAD0 + numStr[4] - '0');
        PressKeyVK(VK_LMENU, false, true);
    }
}