VOID GetHardwareInfo()
{
    int i = 0;
    int monitorCount;
    HANDLE gdi32;
    int cores = 0;

    //use 64 bits to force allmul() on 32 bit builds
    UINT64 physicalPages;
    UINT64 pageSize;

    InitGpuHardware();
    GPU_Initialize(PushSharedMemory->HarwareInformation.DisplayDevice.pciAddress);

    PushSharedMemory->HarwareInformation.DisplayDevice.FrameBuffer.Total = GPU_GetTotalMemory();
    PushSharedMemory->HarwareInformation.DisplayDevice.EngineClockMax = GPU_GetMaximumEngineClock();
    PushSharedMemory->HarwareInformation.DisplayDevice.MemoryClockMax = GPU_GetMaximumMemoryClock();
    PushSharedMemory->HarwareInformation.DisplayDevice.VoltageMax = GPU_GetMaximumVoltage();

    if (Ini_ReadBoolean(L"Settings", L"GpuUsageD3DKMT", FALSE, L".\\" PUSH_SETTINGS_FILE))
        PushGpuLoadD3DKMT = TRUE;

    // Get the number of processors in the system
    NtQuerySystemInformation(SystemBasicInformation, &HwInfoSystemBasicInformation, sizeof(SYSTEM_BASIC_INFORMATION), 0);

    PushSharedMemory->HarwareInformation.Processor.NumberOfThreads = HwInfoSystemBasicInformation.NumberOfProcessors;

    physicalPages = HwInfoSystemBasicInformation.NumberOfPhysicalPages;
    pageSize = HwInfoSystemBasicInformation.PageSize;

    //byte => megabytes
    PushSharedMemory->HarwareInformation.Memory.Total = (physicalPages * pageSize) / 1048576;

    cores = CPU_Intialize();

    PushSharedMemory->HarwareInformation.Processor.NumberOfCores = cores;
    PushSharedMemory->HarwareInformation.Processor.TjMax = CPU_GetTemperatureMaximal();
    PushSharedMemory->HarwareInformation.Processor.MhzBase = CPU_GetBaseSpeed();

    // Monitors
    gdi32 = Module_Load(L"gdi32.dll");

    GetNumberOfPhysicalMonitors = Module_GetProcedureAddress(gdi32, "GetNumberOfPhysicalMonitors");
    GetPhysicalMonitors = Module_GetProcedureAddress(gdi32, "GetPhysicalMonitors");
    DDCCIGetTimingReport = Module_GetProcedureAddress(gdi32, "DDCCIGetTimingReport");
    DDCCIGetVCPFeature = Module_GetProcedureAddress(gdi32, "DDCCIGetVCPFeature");
    DDCCISetVCPFeature = Module_GetProcedureAddress(gdi32, "DDCCISetVCPFeature");

    monitorCount = GetSystemMetrics(SM_CMONITORS);
    MonitorWidth = GetSystemMetrics(SM_CXSCREEN);
    MonitorHeight = GetSystemMetrics(SM_CYSCREEN);

    MonitorHandles = Memory_Allocate(sizeof(HANDLE) * monitorCount);

    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, NULL);
}