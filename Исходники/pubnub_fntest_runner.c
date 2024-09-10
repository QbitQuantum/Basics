static int run_tests(struct TestData aTest[], unsigned test_count, unsigned max_conc_thread, char const *pubkey, char const *keysub, char const *origin)
{
    unsigned next_test = 0;
    unsigned failed_count = 0;
    unsigned passed_count = 0;
    unsigned indete_count = 0;
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
    WORD wOldColorAttrs = FOREGROUND_INTENSITY;

    PUBNUB_ASSERT_OPT(max_conc_thread <= TEST_MAX_HANDLES);
    PUBNUB_ASSERT_OPT(hstdout != INVALID_HANDLE_VALUE);

    g_pubkey = pubkey;
    g_keysub = keysub;
    g_origin = origin;

    printf("Starting Run of %d tests\n", test_count);
    if (GetConsoleScreenBufferInfo(hstdout, &csbiInfo)) {
        wOldColorAttrs = csbiInfo.wAttributes; 
    }

    while (next_test < test_count) {
        unsigned i;
        unsigned in_this_pass = max_conc_thread;
        HANDLE aHa[TEST_MAX_HANDLES];

        if (next_test + in_this_pass > test_count) {
            in_this_pass = test_count - next_test;
        }
        for (i = next_test; i < next_test+in_this_pass; ++i) {
            printf("Creating a thread for test %d\n", i);
            aHa[i - next_test] = aTest[i].pth = (HANDLE)_beginthreadex(NULL, 0, aTest[i].pf, &aTest[i].result, 0, NULL);
        }
        /* This is the simplest way to do it - wait for all threads to finish.
          With a little tweak, we could wait for the first that finishes and
          launch the next test (thread) "in its place". That's a TODO for
          next version.
         */
        if (WAIT_OBJECT_0 != WaitForMultipleObjects(in_this_pass, aHa, TRUE, INFINITE)) {
            SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\n ! WaitForMultipleObjects failed abandonding tests!\n\n");
            SetConsoleTextAttribute(hstdout, wOldColorAttrs);
            return -1;
        }
        for (i = next_test; i < next_test+in_this_pass; ++i) {
            switch (aTest[i].result) {
	    case trFail:
                SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("\n!!!!!!! The %d. test ('%s') failed!\n\n", i + 1, aTest[i].name);
                ++failed_count;
                SetConsoleTextAttribute(hstdout, wOldColorAttrs);
		break;
	    case trPass:
                ++passed_count;
		break;
            case trIndeterminate:
                ++indete_count;
                SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf(" Indeterminate %d. test ('%s') of %d\t", i+1, aTest[i].name, test_count);
                SetConsoleTextAttribute(hstdout, wOldColorAttrs);
                /* Should restart the test... */
		//printf("\x1b[33m ReStarting %d. test of %ld\x1b[m\t", i + 1, test_count);
                break;
            }
        }
        next_test = i;
    }
    
    puts("Test run over.");
    if (passed_count == test_count) {
        SetConsoleTextAttribute(hstdout, FOREGROUND_GREEN);
        printf(" All %d tests passed.\n", test_count);
        SetConsoleTextAttribute(hstdout, wOldColorAttrs);
        return 0;
    }
    else {
        SetConsoleTextAttribute(hstdout, FOREGROUND_GREEN);
        printf("%d tests passed, ", passed_count);
        SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("%d tests failed, ", failed_count);
        SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("%d tests indeterminate\n", indete_count);
        SetConsoleTextAttribute(hstdout, wOldColorAttrs);
        return failed_count + indete_count;
    }
}