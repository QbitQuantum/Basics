void endParallel()
{
    __sync_fetch_and_add(&gActiveThreadCount, -1);
    while (gActiveThreadCount > 0)
        ;

    if (getCurrentThreadId() == 0)
    {
        // Stop all but me
        *((unsigned int*) 0xffff0064) = ~1;
    }
}