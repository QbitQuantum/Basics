static int
mymain(void)
{
    int ret = 0;
    char *map = NULL;

    abs_top_srcdir = getenv("abs_top_srcdir");
    if (!abs_top_srcdir)
        abs_top_srcdir = "..";

    if (virAsprintf(&map, "%s/src/cpu/cpu_map.xml", abs_top_srcdir) < 0 ||
        cpuMapOverride(map) < 0) {
        VIR_FREE(map);
        return EXIT_FAILURE;
    }

#define DO_TEST(arch, api, name, host, cpu,                             \
                models, nmodels, preferred, result)                     \
    do {                                                                \
        struct data data = {                                            \
            arch, api, host, cpu, models,                               \
            models == NULL ? NULL : #models,                            \
            nmodels, preferred, result    \
        };                                                              \
        if (cpuTestRun(name, &data) < 0)                                \
            ret = -1;                                                   \
    } while (0)

#define DO_TEST_COMPARE(arch, host, cpu, result)                        \
    DO_TEST(arch, API_COMPARE,                                          \
            host "/" cpu " (" #result ")",                              \
            host, cpu, NULL, 0, NULL, result)

#define DO_TEST_UPDATE(arch, host, cpu, result)                         \
    do {                                                                \
        DO_TEST(arch, API_UPDATE,                                       \
                cpu " on " host,                                        \
                host, cpu, NULL, 0, NULL, 0);                           \
        DO_TEST_COMPARE(arch, host, host "+" cpu, result);              \
    } while (0)

#define DO_TEST_BASELINE(arch, name, result)                            \
    DO_TEST(arch, API_BASELINE, name, NULL, "baseline-" name,           \
            NULL, 0, NULL, result)

#define DO_TEST_HASFEATURE(arch, host, feature, result)                 \
    DO_TEST(arch, API_HAS_FEATURE,                                      \
            host "/" feature " (" #result ")",                          \
            host, feature, NULL, 0, NULL, result)

#define DO_TEST_GUESTDATA(arch, host, cpu, models, preferred, result)   \
    DO_TEST(arch, API_GUEST_DATA,                                       \
            host "/" cpu " (" #models ", pref=" #preferred ")",         \
            host, cpu, models,                                          \
            models == NULL ? 0 : sizeof(models) / sizeof(char *),       \
            preferred, result)

    /* host to host comparison */
    DO_TEST_COMPARE("x86", "host", "host", IDENTICAL);
    DO_TEST_COMPARE("x86", "host", "host-better", INCOMPATIBLE);
    DO_TEST_COMPARE("x86", "host", "host-worse", SUPERSET);
    DO_TEST_COMPARE("x86", "host", "host-amd-fake", INCOMPATIBLE);
    DO_TEST_COMPARE("x86", "host", "host-incomp-arch", INCOMPATIBLE);
    DO_TEST_COMPARE("x86", "host", "host-no-vendor", IDENTICAL);
    DO_TEST_COMPARE("x86", "host-no-vendor", "host", INCOMPATIBLE);

    /* guest to host comparison */
    DO_TEST_COMPARE("x86", "host", "bogus-model", ERROR);
    DO_TEST_COMPARE("x86", "host", "bogus-feature", ERROR);
    DO_TEST_COMPARE("x86", "host", "min", SUPERSET);
    DO_TEST_COMPARE("x86", "host", "pentium3", SUPERSET);
    DO_TEST_COMPARE("x86", "host", "exact", SUPERSET);
    DO_TEST_COMPARE("x86", "host", "exact-forbid", INCOMPATIBLE);
    DO_TEST_COMPARE("x86", "host", "exact-forbid-extra", SUPERSET);
    DO_TEST_COMPARE("x86", "host", "exact-disable", SUPERSET);
    DO_TEST_COMPARE("x86", "host", "exact-disable2", SUPERSET);
    DO_TEST_COMPARE("x86", "host", "exact-disable-extra", SUPERSET);
    DO_TEST_COMPARE("x86", "host", "exact-require", SUPERSET);
    DO_TEST_COMPARE("x86", "host", "exact-require-extra", INCOMPATIBLE);
    DO_TEST_COMPARE("x86", "host", "exact-force", SUPERSET);
    DO_TEST_COMPARE("x86", "host", "strict", INCOMPATIBLE);
    DO_TEST_COMPARE("x86", "host", "strict-full", IDENTICAL);
    DO_TEST_COMPARE("x86", "host", "strict-disable", IDENTICAL);
    DO_TEST_COMPARE("x86", "host", "strict-force-extra", IDENTICAL);
    DO_TEST_COMPARE("x86", "host", "guest", SUPERSET);
    DO_TEST_COMPARE("x86", "host", "pentium3-amd", INCOMPATIBLE);
    DO_TEST_COMPARE("x86", "host-amd", "pentium3-amd", SUPERSET);
    DO_TEST_COMPARE("x86", "host-worse", "nehalem-force", IDENTICAL);

    /* guest updates for migration
     * automatically compares host CPU with the result */
    DO_TEST_UPDATE("x86", "host", "min", IDENTICAL);
    DO_TEST_UPDATE("x86", "host", "pentium3", IDENTICAL);
    DO_TEST_UPDATE("x86", "host", "guest", SUPERSET);
    DO_TEST_UPDATE("x86", "host", "host-model", IDENTICAL);
    DO_TEST_UPDATE("x86", "host", "host-model-nofallback", IDENTICAL);
    DO_TEST_UPDATE("x86", "host", "host-passthrough", IDENTICAL);

    /* computing baseline CPUs */
    DO_TEST_BASELINE("x86", "incompatible-vendors", -1);
    DO_TEST_BASELINE("x86", "no-vendor", 0);
    DO_TEST_BASELINE("x86", "some-vendors", 0);
    DO_TEST_BASELINE("x86", "1", 0);
    DO_TEST_BASELINE("x86", "2", 0);

    /* CPU features */
    DO_TEST_HASFEATURE("x86", "host", "vmx", YES);
    DO_TEST_HASFEATURE("x86", "host", "lm", YES);
    DO_TEST_HASFEATURE("x86", "host", "sse4.1", YES);
    DO_TEST_HASFEATURE("x86", "host", "3dnowext", NO);
    DO_TEST_HASFEATURE("x86", "host", "skinit", NO);
    DO_TEST_HASFEATURE("x86", "host", "foo", FAIL);

    /* computing guest data and decoding the data into a guest CPU XML */
    DO_TEST_GUESTDATA("x86", "host", "guest", NULL, NULL, 0);
    DO_TEST_GUESTDATA("x86", "host-better", "pentium3", NULL, NULL, 0);
    DO_TEST_GUESTDATA("x86", "host-better", "pentium3", NULL, "pentium3", 0);
    DO_TEST_GUESTDATA("x86", "host-better", "pentium3", NULL, "core2duo", 0);
    DO_TEST_GUESTDATA("x86", "host-worse", "guest", NULL, NULL, 0);
    DO_TEST_GUESTDATA("x86", "host", "strict-force-extra", NULL, NULL, 0);
    DO_TEST_GUESTDATA("x86", "host", "nehalem-force", NULL, NULL, 0);
    DO_TEST_GUESTDATA("x86", "host", "guest", model486, NULL, 0);
    DO_TEST_GUESTDATA("x86", "host", "guest", models, NULL, 0);
    DO_TEST_GUESTDATA("x86", "host", "guest", models, "Penryn", 0);
    DO_TEST_GUESTDATA("x86", "host", "guest", models, "qemu64", 0);
    DO_TEST_GUESTDATA("x86", "host", "guest", nomodel, NULL, -1);
    DO_TEST_GUESTDATA("x86", "host", "guest-nofallback", models, "Penryn", -1);
    DO_TEST_GUESTDATA("x86", "host", "host+host-model", models, "Penryn", 0);
    DO_TEST_GUESTDATA("x86", "host", "host+host-model-nofallback",
                      models, "Penryn", -1);

    VIR_FREE(map);
    return (ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}