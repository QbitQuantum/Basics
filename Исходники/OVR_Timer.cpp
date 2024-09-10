void Timer::initializeTimerSystem()
{
    timeBeginPeriod(1);
    InitializeCriticalSection(&WinAPI_GetTimeCS);

}