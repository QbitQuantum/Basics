    void lock() const
    {
        while (!try_lock)
        {
#if defined(__i386__) || defined(__x86_64__)
# ifdef __clang__
            _mm_pause();
# else
            __builtin_ia32_pause();
# endif
#endif
        }
    }