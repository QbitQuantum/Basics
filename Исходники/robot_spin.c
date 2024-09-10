static void* thread_proc(void* param) {
    int robot_n = (int) param;
    for (;;) {
        long long start = microseconds();
        long long count = 0;
        while (microseconds() - start < 1000000) {
            long long iterations = 10000;
            for (int i = 0; i < iterations; ++i) {
                while (__atomic_load_n(&current, __ATOMIC_SEQ_CST) != robot_n * 2) {
#ifdef USE_PAUSE
                    _mm_pause();
#endif
                }
                __atomic_store_n(&current, robot_n * 2 + 1, __ATOMIC_SEQ_CST);
                //printf("%d\n", robot_n);
                __atomic_store_n(&current, (robot_n + 1) % thread_count * 2, __ATOMIC_SEQ_CST);
            }
            count += iterations;
        }
        if (robot_n == 0) {
            long long dns = 1000ll * (microseconds() - start);
            long long ns_per_call = dns / count;
            printf("%lld ns per step\n", ns_per_call);
        }
    }
}