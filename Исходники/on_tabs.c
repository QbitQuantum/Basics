void WINAPI
threads_on_win7(void)
{
    if (!init_uia())
    {
        return;
    }
    message_hook = SetWindowsHookExW(WH_GETMESSAGE, mouse_message, dll_module, GetCurrentThreadId());
    if (message_hook == NULL)
    {
    #ifdef _LOGDEBUG
        logmsg("SetWindowsHookEx false, error = %lu!\n", GetLastError());
    #endif
        return;
    }
}