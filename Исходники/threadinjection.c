int
main(int argc, char *argv[]) /* Thread One */
{

    DWORD dwThreadID;
    HANDLE hProcess;
    HANDLE hThread1, hThread2, hThread3, hThread4;
    char szCommandLine[1024];
    int i;
    PARAMETERS myParameters;

    INIT();
    /* set exception handler */

    strcpy(szCommandLine, "\0");
    ThreadNr = 0;

    InitializeArguments(&myParameters);
    ParseArguments(argc, argv, &myParameters);

    if (argc == 1) {
        myParameters.bAll = TRUE;
    }

    // On initial call, no args are present; execute each subtest below
    if (myParameters.bAll == TRUE) {
        LaunchAllTests(argv, myParameters);
    } else {
        print("Entering thread with options:\n");
        for (i = 1; i < argc; i++) {
            if (!strncmp(argv[i], "/PID", 4)) {
                strcat(szCommandLine, "/PID");
            } else {
                strcat(szCommandLine, argv[i]);
            }
        }
        print("%s\n", szCommandLine);

        do {
            hThread1 = CreateThread(NULL, 0, &ThreadProc, &(myParameters.nSleepTime), 0,
                                    &dwThreadID);
            ExerciseThread(hThread1, myParameters);
            WaitForSingleObject(hThread1, INFINITE);
            ThreadNr++;

            thread_proc_wait = TRUE;
            hThread2 = CreateThread(NULL, 0, &ThreadProc, &(myParameters.nSleepTime), 0,
                                    &dwThreadID);
            while (!thread_proc_waiting) {
                YIELD();
            }
            TerminateThread(hThread2, -1);
            thread_proc_wait = FALSE;
            thread_proc_waiting = FALSE;
            ThreadNr++;

            // ThreadProc2 calls ExitThread() immediately
            hThread3 = CreateThread(NULL, 0, &ThreadProc2, &ThreadNr, 0, &dwThreadID);
            WaitForSingleObject(hThread3, INFINITE);
            ThreadNr++;

            if (hThread1 != NULL) {
                CloseHandle(hThread1);
            }
            if (hThread2 != NULL) {
                CloseHandle(hThread2);
            }
            if (hThread3 != NULL) {
                CloseHandle(hThread3);
            }

        } while (ThreadNr < MAX_THREADS);

        if (myParameters.nPID != 0) {
            // Prints out results in host PID
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, myParameters.nPID);
            if ((hProcess == NULL) && (myParameters.bVerbose == TRUE)) {
                print("Error in OpenProcess(Code %d)\n", GetLastError());
            }

            hThread4 = CreateRemoteThread(hProcess, 0, 0, &ThreadProc,
                                          &(myParameters.nSleepTime), 0, &dwThreadID);

            if ((hThread4 == NULL) && (myParameters.bVerbose == TRUE)) {
                print("Error in CreateRemoteThread(Code %d)\n", GetLastError());
            }
            WaitForSingleObject(hThread4, INFINITE);

            if (hThread4 != NULL) {
                CloseHandle(hThread4);
            }
        }
        print("Exiting thread with options:\n");
        print("%s\n", szCommandLine);
    }

    return 0;
}