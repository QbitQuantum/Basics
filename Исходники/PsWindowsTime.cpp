PxU64 Time::getCurrentCounterValue()
{
	LARGE_INTEGER ticks;
	QueryPerformanceCounter (&ticks);
	return (PxU64)ticks.QuadPart;
}