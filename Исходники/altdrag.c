int UnhookSystem() {
    if (!keyhook && !msghook) {
        // System not hooked
        return 1;
    }

    // Remove keyboard hook
    if (keyhook) {
        if (UnhookWindowsHookEx(keyhook) == 0) {
#ifdef DEBUG
            Error(L"UnhookWindowsHookEx(keyhook)", L"Could not unhook keyboard. Try restarting "APP_NAME".", GetLastError());
#else
            if (showerror) {
                MessageBox(NULL, l10n->unhook_error, APP_NAME, MB_ICONINFORMATION|MB_OK|MB_TOPMOST|MB_SETFOREGROUND);
            }
#endif
        }
        keyhook = NULL;
    }

    // Remove message hook
    if (msghook) {
        if (UnhookWindowsHookEx(msghook) == 0) {
#ifdef DEBUG
            Error(L"UnhookWindowsHookEx(msghook)", L"Could not unhook message hook. Try restarting "APP_NAME".", GetLastError());
#endif
        }
        msghook = NULL;

        // Close HookWindows_x64.exe
        if (x64) {
            HWND window = FindWindow(L"AltDrag-x64", NULL);
            if (window != NULL) {
                PostMessage(window, WM_CLOSE, 0, 0);
            }
        }

        // Send dummy messages to all processes to make them unload hooks.dll
        EnumWindows(EnumWindowsProc, 0);
    }

    // Tell dll file that we are unloading
    void (*Unload)() = (void*) GetProcAddress(hinstDLL, "Unload");
    if (Unload == NULL) {
        Error(L"GetProcAddress('Unload')", L"This probably means that the file hooks.dll is from an old version or corrupt. You can try reinstalling "APP_NAME".", GetLastError());
    }
    else {
        Unload();
    }

    // Unload library
    if (hinstDLL) {
        if (FreeLibrary(hinstDLL) == 0) {
            Error(L"FreeLibrary()", L"Could not free hooks.dll. Try restarting "APP_NAME".", GetLastError());
        }
        hinstDLL = NULL;
    }

    // Success
    UpdateTray();
    return 0;
}