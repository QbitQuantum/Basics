int Child2(char *arg) 
{
    int i;

    USLOSS_Console("\n%s(): starting\n", arg);
    for (i = 0; i < 5; i++) {
        SemV(sem1);
        USLOSS_Console("%s(): After V attempt #%d\n", arg, i);
    }
    USLOSS_Console("%s(): done\n", arg);
    Terminate(10);
    return 0;
} /* Child2 */