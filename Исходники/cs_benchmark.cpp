void CLIENT_STATE::start_cpu_benchmarks() {
    int i;

    if (benchmarks_running) {
        msg_printf(0, MSG_INFO,
            "Can't start benchmarks - they're already running"
        );
        return;
    }

    if (config.skip_cpu_benchmarks) {
        if (log_flags.benchmark_debug) {
            msg_printf(0, MSG_INFO,
                "[benchmark] start_cpu_benchmarks(): Skipping CPU benchmarks"
            );
        }
        cpu_benchmarks_set_defaults();
        return;
    }
    msg_printf(NULL, MSG_INFO, "Running CPU benchmarks");

    cpu_benchmarks_pending = false;

    bm_state = BM_FP_INIT;
    remove_benchmark_file(BM_TYPE_FP);
    remove_benchmark_file(BM_TYPE_INT);
    cpu_benchmarks_start = dtime();

    if (benchmark_descs) {
        free(benchmark_descs);
    }
    bm_ncpus = ncpus;
    benchmark_descs = (BENCHMARK_DESC*)calloc(bm_ncpus, sizeof(BENCHMARK_DESC));
    benchmarks_running = true;

    for (i=0; i<bm_ncpus; i++) {
        benchmark_descs[i].ordinal = i;
        benchmark_descs[i].done = false;
        benchmark_descs[i].error = false;
#ifdef _WIN32
        benchmark_descs[i].handle = CreateThread(
            NULL, 0, win_cpu_benchmarks, benchmark_descs+i, 0,
            &benchmark_descs[i].pid
        );
        SetThreadAffinityMask(benchmark_descs[i].handle, 1<<i);
        SetThreadPriority(benchmark_descs[i].handle, THREAD_PRIORITY_IDLE);
#else
        sprintf(benchmark_descs[i].filename, "%s_%d.xml", CPU_BENCHMARKS_FILE_NAME, i);
        PROCESS_ID pid = fork();
        if (pid == 0) {
#if HAVE_SETPRIORITY
            if (setpriority(PRIO_PROCESS, 0, PROCESS_IDLE_PRIORITY)) {
                perror("setpriority");
            }
#endif
            int retval = cpu_benchmarks(benchmark_descs+i);
            fflush(NULL);
            _exit(retval);
        } else {
            benchmark_descs[i].pid = pid;
        }
#endif
    }
}