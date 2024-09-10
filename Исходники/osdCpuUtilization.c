int devIocStatsInitCpuUtilization(loadInfo *pval) {

 
     GetSystemTimes(&Prev_Sys_IdleTime, &Prev_Sys_KernelTime, &Prev_Sys_UserTime);
    GetProcessTimes(GetCurrentProcess(),&Proc_Creationtime,&Prev_Proc_IdleTime, &Prev_Proc_KernelTime, &Prev_Proc_UserTime);

    
    myprocessid = GetCurrentProcessId();
    
#ifdef _WIN64
    pval->noOfCpus = GetMaximumProcessorCount(ALL_PROCESSOR_GROUPS);
#else
    
    pval->noOfCpus = strtol(getenv("NUMBER_OF_PROCESSORS"),NULL,10);
#endif    
    
    return 0;
}