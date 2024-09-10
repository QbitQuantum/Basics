bool btSpinMutex::tryLock()
{
    volatile long* aDest = reinterpret_cast<long*>(&mLock);
    return ( 0 == _InterlockedCompareExchange( aDest, 1, 0) );
}