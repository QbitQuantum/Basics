int
Child(char *arg)
{
    int   pid;
    char  *zeros;

    GetPID(&pid);
    Tconsole("Child(): starting (pid = %d)\n", pid);

    zeros = calloc(USLOSS_MmuPageSize(), 1);
    if (memcmp(vmRegion, zeros, USLOSS_MmuPageSize()) != 0) {
        Tconsole("Child(): VmRegion is not zero-filled\n");
        abort();
    }
    verify(vmStats.faults == 1);

    SemV(sem);

    Terminate(117);
    return 0;
} /* Child */