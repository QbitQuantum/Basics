void acquire(int* lock)
{
        int ll = LOCKED;
        int ul = UNLOCKED;
        do {
                ul = UNLOCKED;
                _mm_pause();
        } while (
                __atomic_compare_exchange_n(lock,
                                            &ul,
                                            ll,
                                            1,
                                            __ATOMIC_ACQUIRE,
                                            __ATOMIC_ACQUIRE) != 1);
}