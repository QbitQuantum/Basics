INT_PTR GetContactLocalTime_old(WPARAM wParam, LPARAM lParam)
{
    MTime	now;
    now.GetLocalTime(wParam);

    LPSYSTEMTIME pSystemTime = (LPSYSTEMTIME)lParam;
    *pSystemTime = now.SystemTime();
    return 0;
}