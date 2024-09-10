uint32_t Platform::getIdleTime()
{
    LASTINPUTINFO info = {0, 0};
    info.cbSize = sizeof(info);
    if (GetLastInputInfo(&info))
        return GetTickCount() - info.dwTime;
    return 0;
}