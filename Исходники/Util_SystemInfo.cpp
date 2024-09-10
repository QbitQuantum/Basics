// Returns if the computer is currently locked
bool CheckIsComputerLocked()
{
#ifdef OVR_OS_MS
    LPWSTR pBuf = nullptr;
    DWORD bytesReturned = 0;

    if (::WTSQuerySessionInformationW(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSSessionInfoEx, &pBuf, &bytesReturned))
    {
        if (pBuf && bytesReturned >= sizeof(WTSINFOEX))
        {
            WTSINFOEXW* info = (WTSINFOEXW*)pBuf;

            WTSINFOEX_LEVEL1_W* level1 = (WTSINFOEX_LEVEL1_W*)&info->Data;


            bool isLocked = false;

            if (level1->SessionFlags == WTS_SESSIONSTATE_LOCK)
            {
                isLocked = true;
            }
            else if (level1->SessionFlags != WTS_SESSIONSTATE_UNLOCK) // if not unlocked, we expect locked
            {
                LogError("Unknown Lock State = %d", (int)level1->SessionFlags);
            }

            // Note: On Windows 7, the locked and unlocked flags are reversed!
            // See: https://msdn.microsoft.com/en-us/library/windows/desktop/ee621019(v=vs.85).aspx
            if (IsAtMostWindowsVersion(WindowsVersion::Windows7_SP1))
            {
                isLocked = !isLocked;
            }

            return isLocked;
        }
        else
        {
            LogError("Wrong return size from WTSQuerySessionInformation %u", bytesReturned );
        }
        if ( pBuf )
        {
            WTSFreeMemory(pBuf);
        }
    }
#endif // OVR_OS_MS
    return false;
}