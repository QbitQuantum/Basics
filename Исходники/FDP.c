__inline void ttas_spinlock_lock(volatile bool* lock)
{
    uint16_t test_counter = 0;
    while (true)
    {
        if (*lock == 0)
        {
            test_counter = 0;
            if (_InterlockedCompareExchange8((volatile char*)lock, 1, 0) == 0)
            {
                //MemoryBarrier();
                return;
            }
        }
        else
        {
            if ((test_counter & 0xFFFF) == 0xFFFF)
            {
#if FDP_POWER_SAVE == 1
                Sleep(10);
#endif
            }
            else
            {
                test_counter++;
            }
        }
    }
}