static DWORD WINAPI PerformancePageRefreshThread(void *lpParameter)
{
	ULONG	CommitChargeTotal;
	ULONG	CommitChargeLimit;
	ULONG	CommitChargePeak;

	ULONG	KernelMemoryTotal;
	ULONG	KernelMemoryPaged;
	ULONG	KernelMemoryNonPaged;

	ULONG	PhysicalMemoryTotal;
	ULONG	PhysicalMemoryAvailable;
	ULONG	PhysicalMemorySystemCache;

	ULONG	TotalHandles;
	ULONG	TotalThreads;
	ULONG	TotalProcesses;

	TCHAR	Text[260];

	/*  Create the event */
	hPerformancePageEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

	/*  If we couldn't create the event then exit the thread */
	if (!hPerformancePageEvent)
		return 0;

	while (1)
	{
		DWORD	dwWaitVal;

		/*  Wait on the event */
		dwWaitVal = WaitForSingleObject(hPerformancePageEvent, INFINITE);

		/*  If the wait failed then the event object must have been */
		/*  closed and the task manager is exiting so exit this thread */
		if (dwWaitVal == WAIT_FAILED)
			return 0;

		if (dwWaitVal == WAIT_OBJECT_0)
		{
			ULONG CpuUsage;
			ULONG CpuKernelUsage;
			int nBarsUsed1;
			int nBarsUsed2;

			/*  Reset our event */
			ResetEvent(hPerformancePageEvent);

			/* 
			 *  Update the commit charge info
			 */ 
			CommitChargeTotal = PerfDataGetCommitChargeTotalK();
			CommitChargeLimit = PerfDataGetCommitChargeLimitK();
			CommitChargePeak = PerfDataGetCommitChargePeakK();
			_ultoa(CommitChargeTotal, Text, 10);
			SetWindowText(hPerformancePageCommitChargeTotalEdit, Text);
			_ultoa(CommitChargeLimit, Text, 10);
			SetWindowText(hPerformancePageCommitChargeLimitEdit, Text);
			_ultoa(CommitChargePeak, Text, 10);
			SetWindowText(hPerformancePageCommitChargePeakEdit, Text);
			wsprintf(Text, _T("Mem Usage: %dK / %dK"), CommitChargeTotal, CommitChargeLimit);
			SendMessage(hStatusWnd, SB_SETTEXT, 2, (LPARAM)Text);

			/* 
			 *  Update the kernel memory info
			 */ 
			KernelMemoryTotal = PerfDataGetKernelMemoryTotalK();
			KernelMemoryPaged = PerfDataGetKernelMemoryPagedK();
			KernelMemoryNonPaged = PerfDataGetKernelMemoryNonPagedK();
			_ultoa(KernelMemoryTotal, Text, 10);
			SetWindowText(hPerformancePageKernelMemoryTotalEdit, Text);
			_ultoa(KernelMemoryPaged, Text, 10);
			SetWindowText(hPerformancePageKernelMemoryPagedEdit, Text);
			_ultoa(KernelMemoryNonPaged, Text, 10);
			SetWindowText(hPerformancePageKernelMemoryNonPagedEdit, Text);

			/* 
			 *  Update the physical memory info
			 */ 
			PhysicalMemoryTotal = PerfDataGetPhysicalMemoryTotalK();
			PhysicalMemoryAvailable = PerfDataGetPhysicalMemoryAvailableK();
			PhysicalMemorySystemCache = PerfDataGetPhysicalMemorySystemCacheK();
			_ultoa(PhysicalMemoryTotal, Text, 10);
			SetWindowText(hPerformancePagePhysicalMemoryTotalEdit, Text);
			_ultoa(PhysicalMemoryAvailable, Text, 10);
			SetWindowText(hPerformancePagePhysicalMemoryAvailableEdit, Text);
			_ultoa(PhysicalMemorySystemCache, Text, 10);
			SetWindowText(hPerformancePagePhysicalMemorySystemCacheEdit, Text);

			/* 
			 *  Update the totals info
			 */ 
			TotalHandles = PerfDataGetSystemHandleCount();
			TotalThreads = PerfDataGetTotalThreadCount();
			TotalProcesses = PerfDataGetProcessCount();
			_ultoa(TotalHandles, Text, 10);
			SetWindowText(hPerformancePageTotalsHandleCountEdit, Text);
			_ultoa(TotalThreads, Text, 10);
			SetWindowText(hPerformancePageTotalsThreadCountEdit, Text);
			_ultoa(TotalProcesses, Text, 10);
			SetWindowText(hPerformancePageTotalsProcessCountEdit, Text);

			/* 
			 *  Redraw the graphs
			 */ 
			InvalidateRect(hPerformancePageCpuUsageGraph, NULL, FALSE);
			InvalidateRect(hPerformancePageMemUsageGraph, NULL, FALSE);

                        /*
                         *  Get the CPU usage
                         */
                        CpuUsage = PerfDataGetProcessorUsage();
                        CpuKernelUsage = PerfDataGetProcessorSystemUsage();

                        /*
                         *  Get the memory usage
                         */
                        CommitChargeTotal = (ULONGLONG)PerfDataGetCommitChargeTotalK();
                        CommitChargeLimit = (ULONGLONG)PerfDataGetCommitChargeLimitK();
                        nBarsUsed1 = CommitChargeLimit ? ((CommitChargeTotal * 100) / CommitChargeLimit) : 0;

                        PhysicalMemoryTotal = PerfDataGetPhysicalMemoryTotalK();
                        PhysicalMemoryAvailable = PerfDataGetPhysicalMemoryAvailableK();
                        nBarsUsed2 = PhysicalMemoryTotal ? ((PhysicalMemoryAvailable * 100) / PhysicalMemoryTotal) : 0;


                        GraphCtrl_AppendPoint(&PerformancePageCpuUsageHistoryGraph, CpuUsage, CpuKernelUsage, 0.0, 0.0);
                        GraphCtrl_AppendPoint(&PerformancePageMemUsageHistoryGraph, nBarsUsed1, nBarsUsed2, 0.0, 0.0);
                        /* PerformancePageMemUsageHistoryGraph.SetRange(0.0, 100.0, 10) ; */
                        InvalidateRect(hPerformancePageMemUsageHistoryGraph, NULL, FALSE);
                        InvalidateRect(hPerformancePageCpuUsageHistoryGraph, NULL, FALSE);
                }
	}
        return 0;
}