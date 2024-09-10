void InitPerfClockFrequency()
{
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    frequency /= 1000;
}