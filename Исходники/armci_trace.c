int ARMCI_Init()
{
    int rval;
    static double stime, etime;
    stime = TIME();
    rval = PARMCI_Init();
    etime = TIME();
    ARMCI_Init_t += etime - stime;
    return rval;
}