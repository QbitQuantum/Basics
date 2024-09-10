int
test_ok(int passed, const char *description, const char *directive,
        const char *reason, const char *file, unsigned line,
        const char *fmt, ...)
{
    int is_todo = !passed && directive && !strcmp(directive, "TODO");
    int is_setup = directive && !is_todo && !strcmp(directive, "SETUP");

    if (is_setup)
    {
        if (!passed)
        {
            fflush(stdout);
            fprintf(stderr, "# SETUP not ok%s%s%s%s\n",
                    description ? " - " : "",
                    description ? description : "",
                    reason ? " - " : "",
                    reason ? reason : "");
        }
    }
    else
    {
        if (!test_cases)
        {
            atexit(test_plan_exit);
            fprintf(stderr, "You tried to run a test without a plan!  "
                    "Gotta have a plan. at %s line %u\n", file, line);
            fflush(stderr);
            exit(255);
        }

        ++test_num;
        if (test_num > test_cases || (!passed && !is_todo))
            ++test_fails;
        /* We dont need to print this unless we want to */
#if 0
        fprintf(stderr, "%s:%u: note: %sok %d%s%s%s%s%s%s\n", file, line, passed ? "" : "not ", test_num,
                description ? " - " : "",
                description ? description : "",
                directive ? " # " : "",
                directive ? directive : "",
                reason ? " " : "",
                reason ? reason : "");
#endif
    }

    if (passed)
        fflush(stdout);
    else
    {
        va_list args;

        va_start(args, fmt);

        if (is_todo)
        {
            /* Enable this to output TODO as warning */
#if 0
            printf("%s:%d: warning: Failed (TODO) test\n", file, line);
            if (fmt)
                vprintf(fmt, args);
#endif
            fflush(stdout);
        }
        else
        {
            fflush(stdout);
            fprintf(stderr, "%s:%d: error: Failed test\n", file, line);
            if (fmt)
                vfprintf(stderr, fmt, args);
            fflush(stderr);
        }

        va_end(args);
    }

    return passed;
}