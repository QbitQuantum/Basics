int main(int argc, char* argv[]) {
    int opt;
    auto pss_sort = [](const Vma& a, const Vma& b) {
        uint64_t pss_a = show_wss ? a.wss.pss : a.usage.pss;
        uint64_t pss_b = show_wss ? b.wss.pss : b.usage.pss;
        return pss_a > pss_b;
    };

    auto uss_sort = [](const Vma& a, const Vma& b) {
        uint64_t uss_a = show_wss ? a.wss.uss : a.usage.uss;
        uint64_t uss_b = show_wss ? b.wss.uss : b.usage.uss;
        return uss_a > uss_b;
    };

    std::function<bool(const Vma& a, const Vma& b)> sort_func = nullptr;
    while ((opt = getopt(argc, argv, "himpuWw")) != -1) {
        switch (opt) {
            case 'h':
                hide_zeroes = true;
                break;
            case 'i':
                // TODO: libmeminfo doesn't support the flag to chose
                // between idle page tracking vs clear_refs. So for now,
                // this flag is unused and the library defaults to using
                // /proc/<pid>/clear_refs for finding the working set.
                use_pageidle = true;
                break;
            case 'm':
                // this is the default
                break;
            case 'p':
                sort_func = pss_sort;
                break;
            case 'u':
                sort_func = uss_sort;
                break;
            case 'W':
                reset_wss = true;
                break;
            case 'w':
                show_wss = true;
                break;
            case '?':
                usage(argv[0]);
                return 0;
            default:
                abort();
        }
    }

    if (optind != (argc - 1)) {
        fprintf(stderr, "Need exactly one pid at the end\n");
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = atoi(argv[optind]);
    if (pid == 0) {
        std::cerr << "Invalid process id" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (reset_wss) {
        if (!ProcMemInfo::ResetWorkingSet(pid)) {
            std::cerr << "Failed to reset working set of pid : " << pid << std::endl;
            exit(EXIT_FAILURE);
        }
        return 0;
    }

    ProcMemInfo proc(pid, show_wss);
    const MemUsage& proc_stats = show_wss ? proc.Wss() : proc.Usage();
    std::vector<Vma> maps(proc.Maps());
    if (sort_func != nullptr) {
        std::sort(maps.begin(), maps.end(), sort_func);
    }

    return show(proc_stats, maps);
}