int
main (int argc, char **argv)
{
    bool verbose = false;
    test_item_t *test = 0;
    int argn;
    for (argn = 1; argn < argc; argn++) {
        if (streq (argv [argn], "-v"))
            verbose = true;
        else
        if (streq (argv [argn], "--nb")) {
            printf("%d\n", test_get_number ());
            return 0;
        }
        else
        if (streq (argv [argn], "--list")) {
            test_print_list ();
            return 0;
        }
        else
        if (streq (argv [argn], "--test")) {
            argn++;
            if (argn >= argc) {
                fprintf (stderr, "--test needs an argument\n");
                return 1;
            }
            test = test_available (argv [argn]);
            if (!test) {
                fprintf (stderr, "%s is not available\n", argv [argn]);
                return 1;
            }
        }
        else
        if (streq (argv [argn], "-e")) {
#ifdef _MSC_VER
            //  When receiving an abort signal, only print to stderr (no dialog)
            _set_abort_behavior (0, _WRITE_ABORT_MSG);
#endif
        }
        else {
            printf ("Unknown option: %s\n", argv [argn]);
            return 1;
        }
    }
    if (test) {
        printf ("Running czmq selftest '%s'...\n", test->testname);
        test->test (verbose);
    }
    else
        test_runall (verbose);

    return 0;
}