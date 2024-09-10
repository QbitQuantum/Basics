int
Child(char *arg)
{
    int    pid;
    char   str[64]= "This is the first page";

    GetPID(&pid);
    Tconsole("\nChild(%d): starting\n", pid);

    Tconsole("Child(%d): str = %s\n", pid, str);
    Tconsole("Child(%d): strlen(str) = %d\n", pid, strlen(str));

    memcpy(vmRegion, str, strlen(str)+1);  // +1 to copy nul character

    Tconsole("Child(%d): after memcpy\n", pid);

    if (strcmp(vmRegion, str) == 0)
        Tconsole("Child(%d): strcmp first attempt worked!\n", pid);
    else
        Tconsole("Child(%d): Wrong string read, first attempt\n", pid);

    assert(vmStats.faults == 1);
    assert(vmStats.new == 1);

    SemV(sem);  // forces a context switch with start5

    if (strcmp(vmRegion, str) == 0)
        Tconsole("Child(%d): strcmp second attempt worked!\n", pid);
    else
        Tconsole("Child(%d): Wrong string read, second attempt\n", pid);

    Tconsole("Child(%d): checking various vmStats\n", pid);
    assert(vmStats.faults == 1);
    assert(vmStats.new == 1);
    assert(vmStats.pageOuts == 0);
    assert(vmStats.pageIns == 0);

    Tconsole("Child(%d): terminating\n\n", pid);

    Terminate(117);
    return 0;
} /* Child */