void acquire_hle(unsigned int* lock)
{
        while (__hle_acquire_test_and_set4(lock) == 1) {
                while (*lock == 0)
                        _mm_pause();
        }
}