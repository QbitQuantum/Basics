void pypy_setup_profiling() { 
    if (!profiling_setup) {
        DWORD_PTR affinity_mask, system_affinity_mask;
        GetProcessAffinityMask(GetCurrentProcess(),
            &base_affinity_mask, &system_affinity_mask);
        affinity_mask = 1;
        /* Pick one cpu allowed by the system */
        if (system_affinity_mask)
            while ((affinity_mask & system_affinity_mask) == 0)
                affinity_mask <<= 1;
        SetProcessAffinityMask(GetCurrentProcess(), affinity_mask);
        profiling_setup = 1;
    }
}