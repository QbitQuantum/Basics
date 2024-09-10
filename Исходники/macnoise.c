static void noise_get_processes(void (*func) (void *, int))
{
    ProcessSerialNumber psn = {0, kNoProcess};
    ProcessInfoRec info;

    for (;;) {
        GetNextProcess(&psn);
        if (psn.highLongOfPSN == 0 && psn.lowLongOfPSN == kNoProcess) return;
        info.processInfoLength = sizeof(info);
        info.processName = NULL;
        info.processAppSpec = NULL;
        GetProcessInformation(&psn, &info);
        func(&info, sizeof(info));
    }
}