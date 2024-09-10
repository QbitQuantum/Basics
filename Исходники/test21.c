int Child1(char *arg) 
{
    int pid;
    int status;

    GetPID(&pid);
    USLOSS_Console("%s(): starting, pid = %d\n", arg, pid);
    Spawn("Child2", Child2, "Child2", USLOSS_MIN_STACK, 2, &pid);
    USLOSS_Console("%s(): spawned process %d\n", arg, pid);
    Wait(&pid, &status);
    USLOSS_Console("\n%s(): child %d returned status of %d\n",
                   arg, pid, status);
    USLOSS_Console("%s(): done\n", arg);
    Terminate(9);

    return 0;
} /* Child1 */