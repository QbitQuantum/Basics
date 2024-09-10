int main(int    argc,
         char **argv)
{
char        *str, *results_file;
char         command[256], buf[256];
l_int32      i, ntests, dotest, nfail, ret, start, stop;
SARRAY      *sa;
static char  mainName[] = "alltests_reg";

    if (argc != 2)
        return ERROR_INT(" Syntax alltests_reg [generate | compare | display]",
                         mainName, 1);

    l_getCurrentTime(&start, NULL);
    ntests = sizeof(tests) / sizeof(char *);
    fprintf(stderr, "Running alltests_reg:\n"
            "This currently tests %d of the 127 regression test\n"
            "programs in the /prog directory.\n", ntests);

        /* Clear the output file if we're doing the set of reg tests */
    dotest = strcmp(argv[1], "compare") ? 0 : 1;
    if (dotest) {
        results_file = genPathname("/tmp/lept", "reg_results.txt");
        sa = sarrayCreate(3);
        sarrayAddString(sa, (char *)header, L_COPY);
        sarrayAddString(sa, getLeptonicaVersion(), L_INSERT);
        sarrayAddString(sa, getImagelibVersions(), L_INSERT);
        str = sarrayToString(sa, 1);
        sarrayDestroy(&sa);
        l_binaryWrite("/tmp/lept/reg_results.txt", "w", str, strlen(str));
        lept_free(str);
    }

    nfail = 0;
    for (i = 0; i < ntests; i++) {
#ifndef  _WIN32
        snprintf(command, sizeof(command) - 2, "./%s %s", tests[i], argv[1]);
#else  /* windows interprets '/' as a commandline flag */
        snprintf(command, sizeof(command) - 2, "%s %s", tests[i], argv[1]);
#endif  /* ! _WIN32 */
        ret = system(command);
        if (ret) {
            snprintf(buf, sizeof(buf), "Failed to complete %s\n", tests[i]);
            if (dotest) {
                l_binaryWrite("/tmp/lept/reg_results.txt", "a",
                              buf, strlen(buf));
                nfail++;
            }
            else
                fprintf(stderr, "%s", buf);
        }
    }

    if (dotest) {
#ifndef _WIN32
        snprintf(command, sizeof(command) - 2, "cat %s", results_file);
#else
        snprintf(command, sizeof(command) - 2, "type \"%s\"", results_file);
#endif  /* !_WIN32 */
        lept_free(results_file);
        ret = system(command);
        fprintf(stderr, "Success in %d of %d *_reg programs (output matches"
                " the \"golden\" files)\n", ntests - nfail, ntests);
    }

    l_getCurrentTime(&stop, NULL);
    fprintf(stderr, "Time for all regression tests: %d sec\n", stop - start);
    return 0;
}