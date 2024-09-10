void SoraGetLock(IN OUT volatile LONG *pLock) // Flag lock
{
    LONG Origin;
    do{
        while ( *pLock == 1 ) 
        {
            _mm_pause();
        }
        Origin = InterlockedExchange(pLock, 1);
        if (Origin == 0)
            break;
    } while(TRUE);
}