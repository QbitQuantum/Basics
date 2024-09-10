void Dlg_OnTimer(HWND hwnd, UINT id) {

   // Initialize the structure length before calling GlobalMemoryStatus.
   MEMORYSTATUS ms = { sizeof(ms) };
   GlobalMemoryStatus(&ms);

   TCHAR szData[512] = { 0 };
   StringCchPrintf(szData, _countof(szData), 
      TEXT("%d\n%d\n%I64d\n%I64d\n%I64d\n%I64d\n%I64d"),
      ms.dwMemoryLoad, ms.dwTotalPhys, 
      (__int64) ms.dwAvailPhys,     (__int64) ms.dwTotalPageFile, 
      (__int64) ms.dwAvailPageFile, (__int64) ms.dwTotalVirtual, 
      (__int64) ms.dwAvailVirtual);

   SetDlgItemText(hwnd, IDC_DATA, szData);

   // Get the current process working set and private bytes.
   PROCESS_MEMORY_COUNTERS_EX pmc = { sizeof(PROCESS_MEMORY_COUNTERS_EX) };
   GetProcessMemoryInfo(GetCurrentProcess(), (PPROCESS_MEMORY_COUNTERS)&pmc, sizeof(pmc));
   StringCchPrintf(szData, _countof(szData), 
      TEXT("%I64d K\n%I64d K"),
      (__int64) pmc.WorkingSetSize / 1024,
      (__int64) pmc.PrivateUsage / 1024);
   SetDlgItemText(hwnd, IDC_PROCESSDATA, szData);
}