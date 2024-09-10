void init_timing(void)
{   unsigned long long cycles;
    LARGE_INTEGER ll;

    lock_thread_to_core();
    cycles = __rdtsc();
    Sleep(1000);
    cycles = __rdtsc() - cycles;
    unlock_thread_from_core();
    seconds_per_cycle = 1.0 / (double)cycles;
    QueryPerformanceFrequency(&ll);
    seconds_per_tick = 1.0 / (double)ll.QuadPart;
    QueryPerformanceCounter(&ll);
    start = seconds_per_tick * ll.QuadPart;
		set_timing_seconds();
}