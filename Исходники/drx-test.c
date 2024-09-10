int
main(int argc, char **argv)
{
#ifdef WINDOWS
    HANDLE event;
    char cmdline[128];

    if (argc == 1) {
        /* parent process */
        STARTUPINFO si = { sizeof(STARTUPINFO) };
        PROCESS_INFORMATION pi;
        HANDLE job, job2, job3;
        JOBOBJECT_EXTENDED_LIMIT_INFORMATION limit = {0,};
        DWORD exitcode = (DWORD)-1;

        /* For synchronization we create an inherited event */
        SECURITY_ATTRIBUTES sa = {sizeof(sa), NULL, TRUE/*inherit*/};
        event = CreateEvent(&sa, FALSE/*manual reset*/, FALSE/*start unset*/, NULL);
        if (event == NULL)
            print("Failed to create event");

        _snprintf(cmdline, BUFFER_SIZE_ELEMENTS(cmdline), "%s %p", argv[0], event);

        print("creating child #1\n");
        if (!CreateProcess(argv[0], cmdline, NULL, NULL, TRUE/*inherit handles*/,
                           0, NULL, NULL, &si, &pi))
            print("CreateProcess failure\n");
        WaitForSingleObject(event, INFINITE);
        print("terminating child #1 by NtTerminateProcess\n");
        TerminateProcess(pi.hProcess, 42);
        WaitForSingleObject(pi.hProcess, INFINITE);
        GetExitCodeProcess(pi.hProcess, &exitcode);
        print("child #1 exit code = %d\n", exitcode);
        if (!ResetEvent(event))
            print("Failed to reset event\n");

        print("creating child #2\n");
        if (!CreateProcess(argv[0], cmdline, NULL, NULL, TRUE/*inherit handles*/,
                           CREATE_SUSPENDED, NULL, NULL, &si, &pi))
            print("CreateProcess failure\n");
        job = CreateJobObject(NULL, "drx-test job");
        AssignProcessToJobObject(job, pi.hProcess);
        ResumeThread(pi.hThread);
        CloseHandle(pi.hThread);
        WaitForSingleObject(event, INFINITE);
        print("terminating child #2 by NtTerminateJobObject\n");
        TerminateJobObject(job, 123456);
        CloseHandle(job);
        WaitForSingleObject(pi.hProcess, INFINITE);
        GetExitCodeProcess(pi.hProcess, &exitcode);
        print("child #2 exit code = %d\n", exitcode);
        if (!ResetEvent(event))
            print("Failed to reset event\n");

        print("creating child #3\n");
        if (!CreateProcess(argv[0], cmdline, NULL, NULL, TRUE/*inherit handles*/,
                           CREATE_SUSPENDED, NULL, NULL, &si, &pi))
            print("CreateProcess failure\n");
        job = CreateJobObject(NULL, "drx-test job");
        AssignProcessToJobObject(job, pi.hProcess);
        limit.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
        if (!SetInformationJobObject(job, JobObjectExtendedLimitInformation,
                                     &limit, sizeof(limit)))
            print("SetInformationJobObject failed\n");
        ResumeThread(pi.hThread);
        CloseHandle(pi.hThread);
        WaitForSingleObject(event, INFINITE);
        print("terminating child #3 by closing job handle\n");
        CloseHandle(job);
        WaitForSingleObject(pi.hProcess, INFINITE);
        GetExitCodeProcess(pi.hProcess, &exitcode);
        print("child #3 exit code = %d\n", exitcode);

        /* Test DuplicateHandle (DrMem i#1401) */
        print("creating child #4\n");
        if (!CreateProcess(argv[0], cmdline, NULL, NULL, TRUE/*inherit handles*/,
                           CREATE_SUSPENDED, NULL, NULL, &si, &pi))
            print("CreateProcess failure\n");
        job = CreateJobObject(NULL, "drx-test job");
        AssignProcessToJobObject(job, pi.hProcess);
        limit.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
        if (!SetInformationJobObject(job, JobObjectExtendedLimitInformation,
                                     &limit, sizeof(limit)))
            print("SetInformationJobObject failed\n");
        if (!DuplicateHandle(GetCurrentProcess(), job, GetCurrentProcess(), &job2,
                             0, FALSE, DUPLICATE_SAME_ACCESS))
            print("DuplicateHandle failed\n");
        if (!DuplicateHandle(GetCurrentProcess(), job, GetCurrentProcess(), &job3,
                             0, FALSE, DUPLICATE_CLOSE_SOURCE | DUPLICATE_SAME_ACCESS))
            print("DuplicateHandle failed\n");
        ResumeThread(pi.hThread);
        CloseHandle(pi.hThread);
        WaitForSingleObject(event, INFINITE);
        print("terminating child #4 by closing both job handles\n");
        CloseHandle(job2);
        CloseHandle(job3);
        WaitForSingleObject(pi.hProcess, INFINITE);
        GetExitCodeProcess(pi.hProcess, &exitcode);
        print("child #4 exit code = %d\n", exitcode);
    }
    else { /* child process */
        int iter = 0;
        if (sscanf(argv[1], "%p", &event) != 1) {
            print("Failed to obtain event handle from %s\n", argv[1]);
            return -1;
        }
        if (!SetEvent(event))
            print("Failed to set event\n");
        /* spin until parent kills us or we time out */
        while (iter++ < 12) {
            Sleep(5000);
        }
    }

    CloseHandle(event);

#else /* WINDOWS */

    int pipefd[2];
    pid_t cpid;
    char buf = 0;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    print("creating child\n");
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(1);
    } else if (cpid > 0) {
        /* parent */
        int status;
        close(pipefd[1]); /* close unused write end */
        if (read(pipefd[0], &buf, sizeof(buf)) <= 0) {
            perror("pipe read failed");
            exit(1);
        }
        print("terminating child by sending SIGKILL\n");
        kill(cpid, SIGKILL);
        wait(&status); /* wait for child */
        close(pipefd[0]);
        print("child exit code = %d\n", status);
    } else {
        /* child */
        int iter = 0;
        close(pipefd[0]); /* close unused read end */
        write(pipefd[1], &buf, sizeof(buf));
        close(pipefd[1]);
        /* spin until parent kills us or we time out */
        while (iter++ < 12) {
            sleep(5);
        }
    }

#endif /* UNIX */

    return 0;
}