PerformanceMonitor::PerformanceMonitor(){
    HANDLE thisProcessHande = GetCurrentProcess();
    SYSTEM_INFO sysInfo;
    BOOL runningInWow64 = false;
    IsWow64Process(thisProcessHande, &runningInWow64);
    if(runningInWow64){
        GetNativeSystemInfo(&sysInfo);
    }
    else{
        GetSystemInfo(&sysInfo);
    }
    this->processorsCount = sysInfo.dwNumberOfProcessors;
}