VOID PhpUpdateProcessStatistics(
    _In_ HWND hwndDlg,
    _In_ PPH_PROCESS_ITEM ProcessItem,
    _In_ PPH_STATISTICS_CONTEXT Context
    )
{
    WCHAR timeSpan[PH_TIMESPAN_STR_LEN_1];

    SetDlgItemInt(hwndDlg, IDC_ZPRIORITY_V, ProcessItem->BasePriority, TRUE); // priority
    PhPrintTimeSpan(timeSpan, ProcessItem->KernelTime.QuadPart, PH_TIMESPAN_HMSM); // kernel time
    SetDlgItemText(hwndDlg, IDC_ZKERNELTIME_V, timeSpan);
    PhPrintTimeSpan(timeSpan, ProcessItem->UserTime.QuadPart, PH_TIMESPAN_HMSM); // user time
    SetDlgItemText(hwndDlg, IDC_ZUSERTIME_V, timeSpan);
    PhPrintTimeSpan(timeSpan,
        ProcessItem->KernelTime.QuadPart + ProcessItem->UserTime.QuadPart, PH_TIMESPAN_HMSM); // total time
    SetDlgItemText(hwndDlg, IDC_ZTOTALTIME_V, timeSpan);

    SetDlgItemText(hwndDlg, IDC_ZPRIVATEBYTES_V,
        PhaFormatSize(ProcessItem->VmCounters.PagefileUsage, -1)->Buffer); // private bytes (same as PrivateUsage)
    SetDlgItemText(hwndDlg, IDC_ZPEAKPRIVATEBYTES_V,
        PhaFormatSize(ProcessItem->VmCounters.PeakPagefileUsage, -1)->Buffer); // peak private bytes
    SetDlgItemText(hwndDlg, IDC_ZVIRTUALSIZE_V,
        PhaFormatSize(ProcessItem->VmCounters.VirtualSize, -1)->Buffer); // virtual size
    SetDlgItemText(hwndDlg, IDC_ZPEAKVIRTUALSIZE_V,
        PhaFormatSize(ProcessItem->VmCounters.PeakVirtualSize, -1)->Buffer); // peak virtual size
    SetDlgItemText(hwndDlg, IDC_ZPAGEFAULTS_V,
        PhaFormatUInt64(ProcessItem->VmCounters.PageFaultCount, TRUE)->Buffer); // page faults
    SetDlgItemText(hwndDlg, IDC_ZWORKINGSET_V,
        PhaFormatSize(ProcessItem->VmCounters.WorkingSetSize, -1)->Buffer); // working set
    SetDlgItemText(hwndDlg, IDC_ZPEAKWORKINGSET_V,
        PhaFormatSize(ProcessItem->VmCounters.PeakWorkingSetSize, -1)->Buffer); // peak working set

    SetDlgItemText(hwndDlg, IDC_ZIOREADS_V,
        PhaFormatUInt64(ProcessItem->IoCounters.ReadOperationCount, TRUE)->Buffer); // reads
    SetDlgItemText(hwndDlg, IDC_ZIOREADBYTES_V,
        PhaFormatSize(ProcessItem->IoCounters.ReadTransferCount, -1)->Buffer); // read bytes
    SetDlgItemText(hwndDlg, IDC_ZIOWRITES_V,
        PhaFormatUInt64(ProcessItem->IoCounters.WriteOperationCount, TRUE)->Buffer); // writes
    SetDlgItemText(hwndDlg, IDC_ZIOWRITEBYTES_V,
        PhaFormatSize(ProcessItem->IoCounters.WriteTransferCount, -1)->Buffer); // write bytes
    SetDlgItemText(hwndDlg, IDC_ZIOOTHER_V,
        PhaFormatUInt64(ProcessItem->IoCounters.OtherOperationCount, TRUE)->Buffer); // other
    SetDlgItemText(hwndDlg, IDC_ZIOOTHERBYTES_V,
        PhaFormatSize(ProcessItem->IoCounters.OtherTransferCount, -1)->Buffer); // read bytes

    SetDlgItemText(hwndDlg, IDC_ZHANDLES_V,
        PhaFormatUInt64(ProcessItem->NumberOfHandles, TRUE)->Buffer); // handles

    // Optional information
    if (!PH_IS_FAKE_PROCESS_ID(ProcessItem->ProcessId))
    {
        PPH_STRING peakHandles = NULL;
        PPH_STRING gdiHandles = NULL;
        PPH_STRING userHandles = NULL;
        PPH_STRING cycles = NULL;
        ULONG pagePriority = -1;
        IO_PRIORITY_HINT ioPriority = -1;
        PPH_STRING privateWs = NULL;
        PPH_STRING shareableWs = NULL;
        PPH_STRING sharedWs = NULL;
        BOOLEAN gotCycles = FALSE;
        BOOLEAN gotWsCounters = FALSE;

        if (ProcessItem->QueryHandle)
        {
            ULONG64 cycleTime;

            if (WindowsVersion >= WINDOWS_7)
            {
                PROCESS_HANDLE_INFORMATION handleInfo;

                if (NT_SUCCESS(NtQueryInformationProcess(
                    ProcessItem->QueryHandle,
                    ProcessHandleCount,
                    &handleInfo,
                    sizeof(PROCESS_HANDLE_INFORMATION),
                    NULL
                    )))
                {
                    peakHandles = PhaFormatUInt64(handleInfo.HandleCountHighWatermark, TRUE);
                }
            }

            gdiHandles = PhaFormatUInt64(GetGuiResources(ProcessItem->QueryHandle, GR_GDIOBJECTS), TRUE); // GDI handles
            userHandles = PhaFormatUInt64(GetGuiResources(ProcessItem->QueryHandle, GR_USEROBJECTS), TRUE); // USER handles

            if (WINDOWS_HAS_CYCLE_TIME &&
                NT_SUCCESS(PhGetProcessCycleTime(ProcessItem->QueryHandle, &cycleTime)))
            {
                cycles = PhaFormatUInt64(cycleTime, TRUE);
                gotCycles = TRUE;
            }

            if (WindowsVersion >= WINDOWS_VISTA)
            {
                PhGetProcessPagePriority(ProcessItem->QueryHandle, &pagePriority);
                PhGetProcessIoPriority(ProcessItem->QueryHandle, &ioPriority);
            }
        }

        if (Context->ProcessHandle)
        {
            PH_PROCESS_WS_COUNTERS wsCounters;

            if (NT_SUCCESS(PhGetProcessWsCounters(Context->ProcessHandle, &wsCounters)))
            {
                privateWs = PhaFormatSize((ULONG64)wsCounters.NumberOfPrivatePages * PAGE_SIZE, -1);
                shareableWs = PhaFormatSize((ULONG64)wsCounters.NumberOfShareablePages * PAGE_SIZE, -1);
                sharedWs = PhaFormatSize((ULONG64)wsCounters.NumberOfSharedPages * PAGE_SIZE, -1);
                gotWsCounters = TRUE;
            }
        }

        if (WindowsVersion >= WINDOWS_7)
        {
            if (!gotCycles)
                cycles = PhaFormatUInt64(ProcessItem->CycleTimeDelta.Value, TRUE);
            if (!gotWsCounters)
                privateWs = PhaFormatSize(ProcessItem->WorkingSetPrivateSize, -1);
        }

        if (WindowsVersion >= WINDOWS_7)
            SetDlgItemText(hwndDlg, IDC_ZPEAKHANDLES_V, PhGetStringOrDefault(peakHandles, L"Unknown"));
        else
            SetDlgItemText(hwndDlg, IDC_ZPEAKHANDLES_V, L"N/A");

        SetDlgItemText(hwndDlg, IDC_ZGDIHANDLES_V, PhGetStringOrDefault(gdiHandles, L"Unknown"));
        SetDlgItemText(hwndDlg, IDC_ZUSERHANDLES_V, PhGetStringOrDefault(userHandles, L"Unknown"));
        SetDlgItemText(hwndDlg, IDC_ZCYCLES_V,
            PhGetStringOrDefault(cycles, WINDOWS_HAS_CYCLE_TIME ? L"Unknown" : L"N/A"));

        if (WindowsVersion >= WINDOWS_VISTA)
        {
            if (pagePriority != -1 && pagePriority <= MEMORY_PRIORITY_NORMAL)
                SetDlgItemText(hwndDlg, IDC_ZPAGEPRIORITY_V, PhPagePriorityNames[pagePriority]);
            else
                SetDlgItemText(hwndDlg, IDC_ZPAGEPRIORITY_V, L"Unknown");

            if (ioPriority != -1 && ioPriority < MaxIoPriorityTypes)
                SetDlgItemText(hwndDlg, IDC_ZIOPRIORITY_V, PhIoPriorityHintNames[ioPriority]);
            else
                SetDlgItemText(hwndDlg, IDC_ZIOPRIORITY_V, L"Unknown");
        }
        else
        {
            SetDlgItemText(hwndDlg, IDC_ZPAGEPRIORITY_V, L"N/A");
            SetDlgItemText(hwndDlg, IDC_ZIOPRIORITY_V, L"N/A");
        }

        SetDlgItemText(hwndDlg, IDC_ZPRIVATEWS_V, PhGetStringOrDefault(privateWs, L"Unknown"));
        SetDlgItemText(hwndDlg, IDC_ZSHAREABLEWS_V, PhGetStringOrDefault(shareableWs, L"Unknown"));
        SetDlgItemText(hwndDlg, IDC_ZSHAREDWS_V, PhGetStringOrDefault(sharedWs, L"Unknown"));
    }
    else
    {
        SetDlgItemText(hwndDlg, IDC_ZPEAKHANDLES_V, L"N/A");
        SetDlgItemText(hwndDlg, IDC_ZGDIHANDLES_V, L"N/A");
        SetDlgItemText(hwndDlg, IDC_ZUSERHANDLES_V, L"N/A");
        SetDlgItemText(hwndDlg, IDC_ZCYCLES_V, L"N/A");
        SetDlgItemText(hwndDlg, IDC_ZPAGEPRIORITY_V, L"N/A");
        SetDlgItemText(hwndDlg, IDC_ZIOPRIORITY_V, L"N/A");
        SetDlgItemText(hwndDlg, IDC_ZPRIVATEWS_V, L"N/A");
        SetDlgItemText(hwndDlg, IDC_ZSHAREABLEWS_V, L"N/A");
        SetDlgItemText(hwndDlg, IDC_ZSHAREDWS_V, L"N/A");
    }
}