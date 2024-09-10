VOID PhpUpdateThreadDetails(
    _In_ HWND hwndDlg,
    _In_ PPH_THREADS_CONTEXT Context,
    _In_ BOOLEAN Force
    )
{
    PPH_THREAD_ITEM *threads;
    ULONG numberOfThreads;
    PPH_THREAD_ITEM threadItem;
    PPH_STRING startModule = NULL;
    PPH_STRING started = NULL;
    WCHAR kernelTime[PH_TIMESPAN_STR_LEN_1] = L"N/A";
    WCHAR userTime[PH_TIMESPAN_STR_LEN_1] = L"N/A";
    PPH_STRING contextSwitches = NULL;
    PPH_STRING cycles = NULL;
    PPH_STRING state = NULL;
    WCHAR priority[PH_INT32_STR_LEN_1] = L"N/A";
    WCHAR basePriority[PH_INT32_STR_LEN_1] = L"N/A";
    PWSTR ioPriority = L"N/A";
    PWSTR pagePriority = L"N/A";
    WCHAR idealProcessor[PH_INT32_STR_LEN + 1 + PH_INT32_STR_LEN + 1] = L"N/A";
    HANDLE threadHandle;
    SYSTEMTIME time;
    IO_PRIORITY_HINT ioPriorityInteger;
    ULONG pagePriorityInteger;
    PROCESSOR_NUMBER idealProcessorNumber;
    ULONG suspendCount;

    PhGetSelectedThreadItems(&Context->ListContext, &threads, &numberOfThreads);

    if (numberOfThreads == 1)
        threadItem = threads[0];
    else
        threadItem = NULL;

    PhFree(threads);

    if (numberOfThreads != 1 && !Force)
        return;

    if (numberOfThreads == 1)
    {
        startModule = threadItem->StartAddressFileName;

        PhLargeIntegerToLocalSystemTime(&time, &threadItem->CreateTime);
        started = PhaFormatDateTime(&time);

        PhPrintTimeSpan(kernelTime, threadItem->KernelTime.QuadPart, PH_TIMESPAN_HMSM);
        PhPrintTimeSpan(userTime, threadItem->UserTime.QuadPart, PH_TIMESPAN_HMSM);

        contextSwitches = PhaFormatUInt64(threadItem->ContextSwitchesDelta.Value, TRUE);

        if (WINDOWS_HAS_CYCLE_TIME)
            cycles = PhaFormatUInt64(threadItem->CyclesDelta.Value, TRUE);

        if (threadItem->State != Waiting)
        {
            if ((ULONG)threadItem->State < MaximumThreadState)
                state = PhaCreateString(PhKThreadStateNames[(ULONG)threadItem->State]);
            else
                state = PhaCreateString(L"Unknown");
        }
        else
        {
            if ((ULONG)threadItem->WaitReason < MaximumWaitReason)
                state = PhaConcatStrings2(L"Wait:", PhKWaitReasonNames[(ULONG)threadItem->WaitReason]);
            else
                state = PhaCreateString(L"Waiting");
        }

        PhPrintInt32(priority, threadItem->Priority);
        PhPrintInt32(basePriority, threadItem->BasePriority);

        if (NT_SUCCESS(PhOpenThread(&threadHandle, ThreadQueryAccess, threadItem->ThreadId)))
        {
            if (NT_SUCCESS(PhGetThreadIoPriority(threadHandle, &ioPriorityInteger)) &&
                ioPriorityInteger < MaxIoPriorityTypes)
            {
                ioPriority = PhIoPriorityHintNames[ioPriorityInteger];
            }

            if (NT_SUCCESS(PhGetThreadPagePriority(threadHandle, &pagePriorityInteger)) &&
                pagePriorityInteger <= MEMORY_PRIORITY_NORMAL)
            {
                pagePriority = PhPagePriorityNames[pagePriorityInteger];
            }

            if (NT_SUCCESS(NtQueryInformationThread(threadHandle, ThreadIdealProcessorEx, &idealProcessorNumber, sizeof(PROCESSOR_NUMBER), NULL)))
            {
                PH_FORMAT format[3];

                PhInitFormatU(&format[0], idealProcessorNumber.Group);
                PhInitFormatC(&format[1], ':');
                PhInitFormatU(&format[2], idealProcessorNumber.Number);
                PhFormatToBuffer(format, 3, idealProcessor, sizeof(idealProcessor), NULL);
            }

            if (threadItem->WaitReason == Suspended && NT_SUCCESS(NtQueryInformationThread(threadHandle, ThreadSuspendCount, &suspendCount, sizeof(ULONG), NULL)))
            {
                PH_FORMAT format[4];

                PhInitFormatSR(&format[0], state->sr);
                PhInitFormatS(&format[1], L" (");
                PhInitFormatU(&format[2], suspendCount);
                PhInitFormatS(&format[3], L")");
                state = PH_AUTO(PhFormat(format, 4, 30));
            }

            NtClose(threadHandle);
        }
    }

    if (Force)
    {
        // These don't change...

        SetDlgItemText(hwndDlg, IDC_STARTMODULE, PhGetStringOrEmpty(startModule));
        EnableWindow(GetDlgItem(hwndDlg, IDC_OPENSTARTMODULE), !!startModule);

        SetDlgItemText(hwndDlg, IDC_STARTED, PhGetStringOrDefault(started, L"N/A"));
    }

    SetDlgItemText(hwndDlg, IDC_KERNELTIME, kernelTime);
    SetDlgItemText(hwndDlg, IDC_USERTIME, userTime);
    SetDlgItemText(hwndDlg, IDC_CONTEXTSWITCHES, PhGetStringOrDefault(contextSwitches, L"N/A"));
    SetDlgItemText(hwndDlg, IDC_CYCLES, PhGetStringOrDefault(cycles, L"N/A"));
    SetDlgItemText(hwndDlg, IDC_STATE, PhGetStringOrDefault(state, L"N/A"));
    SetDlgItemText(hwndDlg, IDC_PRIORITY, priority);
    SetDlgItemText(hwndDlg, IDC_BASEPRIORITY, basePriority);
    SetDlgItemText(hwndDlg, IDC_IOPRIORITY, ioPriority);
    SetDlgItemText(hwndDlg, IDC_PAGEPRIORITY, pagePriority);
    SetDlgItemText(hwndDlg, IDC_IDEALPROCESSOR, idealProcessor);
}