int Child2(char *arg)
{
    int pid, i;

    GetPID(&pid);
    USLOSS_Console("%s(): starting, pid = %d\n", arg, pid);
    for (i = 0; i != MAXPROC; i++){
        Spawn("Child2a", Child2a, "Child2a", USLOSS_MIN_STACK, 3, &pid);
        if (pid >= 0)
            USLOSS_Console("%s(): spawned process %d\n", arg, pid);
        else
            USLOSS_Console("%s(): spawned attempt failed, pid = %d\n",
                           arg, pid);
        }

    USLOSS_Console("\n%s(): Terminating self and all my children\n", arg);
    Terminate(10);

     return 0;
} /* Child2 */