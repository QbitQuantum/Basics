int main(int argc, char* argv[])
{
    int rcErrors = 0;

    /*
     * Initialize the runtime.
     */
    RTR3InitExe(argc, &argv, RTR3INIT_FLAGS_SUPLIB);

#ifndef AUTO_TEST_ARGS
    if (argc < 2)
    {
        RTPrintf("syntax: %s command [args]\n"
                    "\n"
                    "command    Command to run under child process in fork.\n"
                    "[args]     Arguments to command.\n", argv[0]);
        return 1;
    }
#endif

    /*
     * Create empty VM.
     */
    RTPrintf(TESTCASE ": Initializing...\n");
    PVM pVM;
    int rc = VMR3Create(1, NULL, NULL, NULL, NULL, NULL, &pVM);
    if (RT_SUCCESS(rc))
    {
        /*
         * Do testing.
         */
        int iCowTester = 0;
        char cCowTester = 'a';

#ifndef AUTO_TEST_ARGS
        int cArgs = argc - 1;
        char **ppszArgs = &argv[1];
#else
        int cArgs = 2;
        char *ppszArgs[3];
        ppszArgs[0] = (char *)"/bin/sleep";
        ppszArgs[1] = (char *)"3";
        ppszArgs[2] = NULL;
#endif

        RTPrintf(TESTCASE ": forking current process...\n");
        pid_t pid = fork();
        if (pid < 0)
        {
            /* Bad. fork() failed! */
            RTPrintf(TESTCASE ": error: fork() failed.\n");
            rcErrors++;
        }
        else if (pid == 0)
        {
            /*
             * The child process.
             * Write to some local variables to trigger copy-on-write if it's used.
             */
            RTPrintf(TESTCASE ": running child process...\n");
            RTPrintf(TESTCASE ": writing local variables...\n");
            iCowTester = 2;
            cCowTester = 'z';

            RTPrintf(TESTCASE ": calling execv() with command-line:\n");
            for (int i = 0; i < cArgs; i++)
                RTPrintf(TESTCASE ": ppszArgs[%d]=%s\n", i, ppszArgs[i]);
            execv(ppszArgs[0], ppszArgs);
            RTPrintf(TESTCASE ": error: execv() returned to caller. errno=%d.\n", errno);
            _exit(-1);
        }
        else
        {
            /*
             * The parent process.
             * Wait for child & run VMM test to ensure things are fine.
             */
            int result;
            while (waitpid(pid, &result, 0) < 0)
                ;
            if (!WIFEXITED(result) || WEXITSTATUS(result) != 0)
            {
                RTPrintf(TESTCASE ": error: failed to run child process. errno=%d\n", errno);
                rcErrors++;
            }

            if (rcErrors == 0)
            {
                RTPrintf(TESTCASE ": fork() returned fine.\n");
                RTPrintf(TESTCASE ": testing VM after fork.\n");
                VMR3ReqCallWait(pVM, VMCPUID_ANY, (PFNRT)VMMDoTest, 1, pVM);

                STAMR3Dump(pVM, "*");
            }
        }

        if (rcErrors > 0)
            RTPrintf(TESTCASE ": error: %d error(s) during fork(). Cannot proceed to test the VM.\n");
        else
            RTPrintf(TESTCASE ": fork() and VM test, SUCCESS.\n");

        /*
         * Cleanup.
         */
        rc = VMR3PowerOff(pVM);
        if (!RT_SUCCESS(rc))
        {
            RTPrintf(TESTCASE ": error: failed to power off vm! rc=%Rrc\n", rc);
            rcErrors++;
        }
        rc = VMR3Destroy(pVM);
        if (!RT_SUCCESS(rc))
        {
            RTPrintf(TESTCASE ": error: failed to destroy vm! rc=%Rrc\n", rc);
            rcErrors++;
        }
    }
    else
    {
        RTPrintf(TESTCASE ": fatal error: failed to create vm! rc=%Rrc\n", rc);
        rcErrors++;
    }

    return rcErrors;
}