/*
 * Benchmarks Argon2 with salt length 16, password length 32, t_cost 3, and different threads and m_cost
 */
void Benchmark() {
    const uint32_t inlen = 32;

    unsigned char out[32];
    unsigned char zero_array[inlen];
    unsigned char one_array[256];

    uint32_t outlen = 16;
    uint32_t saltlen = 16;
    uint32_t t_cost = 1;

    memset(zero_array, 0, inlen);
    memset(one_array, 1, 256);
    std::vector<uint32_t> thread_test = {1, 2, 4, 6, 8, 16};

    for (uint32_t m_cost = (uint32_t) 1 << 10; m_cost <= (uint32_t) 1 << 22; m_cost *= 2) {
        for (uint32_t thread_n : thread_test) {

#ifdef _MEASURE
            uint64_t start_cycles, stop_cycles, stop_cycles_i, stop_cycles_di, stop_cycles_ds;
            uint32_t ui1, ui2, ui3, ui4, ui5;

            clock_t start_time = clock();
            start_cycles = __rdtscp(&ui1);
#endif

            Argon2_Context context(out, outlen, zero_array, inlen, one_array, saltlen, NULL, 0, NULL, 0, t_cost, m_cost, thread_n,NULL,NULL,false,false, false);
            Argon2d(&context);

#ifdef _MEASURE
            stop_cycles = __rdtscp(&ui2);
#endif
            Argon2i(&context);
#ifdef _MEASURE
            stop_cycles_i = __rdtscp(&ui3);
#endif
            Argon2id(&context);
#ifdef _MEASURE
            stop_cycles_di = __rdtscp(&ui4);
#endif
            Argon2ds(&context);
#ifdef _MEASURE
            stop_cycles_ds = __rdtscp(&ui5);
            clock_t stop_time = clock();

            uint64_t delta_d = (stop_cycles - start_cycles) / (m_cost);
            uint64_t delta_i = (stop_cycles_i - stop_cycles) / (m_cost);
            uint64_t delta_id = (stop_cycles_di - stop_cycles_i) / m_cost;
            uint64_t delta_ds = (stop_cycles_ds - stop_cycles_di) / m_cost;
            float mcycles_d = (float) (stop_cycles - start_cycles) / (1 << 20);
            float mcycles_i = (float) (stop_cycles_i - stop_cycles) / (1 << 20);
            float mcycles_id = (float) (stop_cycles_di - stop_cycles_i) / (1 << 20);
            float mcycles_ds = (float) (stop_cycles_ds - stop_cycles_di) / (1 << 20);
            printf("Argon2d %d pass(es)  %d Mbytes %d threads:  %2.2f cpb %2.2f Mcycles \n", t_cost, m_cost >> 10, thread_n, (float) delta_d / 1024, mcycles_d);
            printf("Argon2i %d pass(es)  %d Mbytes %d threads:  %2.2f cpb %2.2f Mcycles \n", t_cost, m_cost >> 10, thread_n, (float) delta_i / 1024, mcycles_i);
            printf("Argon2id %d pass(es)  %d Mbytes %d threads:  %2.2f cpb %2.2f Mcycles \n", t_cost, m_cost >> 10, thread_n, (float) delta_id / 1024, mcycles_id);
            printf("Argon2ds %d pass(es)  %d Mbytes %d threads:  %2.2f cpb %2.2f Mcycles \n", t_cost, m_cost >> 10, thread_n, (float) delta_ds / 1024, mcycles_ds);

            float run_time = ((float) stop_time - start_time) / (CLOCKS_PER_SEC);
            printf("%2.4f seconds\n\n", run_time);
#endif
        }
    }
}