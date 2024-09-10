BOOL VBoxHookRemoveActiveDesktopTracker()
{
    if (g_hDesktopEventHook)
    {
        UnhookWinEvent(g_hDesktopEventHook);
        CoUninitialize();
    }
    g_hDesktopEventHook = 0;
    return TRUE;
}