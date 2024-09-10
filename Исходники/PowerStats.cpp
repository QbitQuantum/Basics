void PowerStats::GetWinCPUTime(ULARGE_INTEGER &cpu_time) {
  FILETIME idle_time, kernel_time, user_time;
  if (GetSystemTimes(&idle_time, &kernel_time, &user_time)) {
    ULARGE_INTEGER k, u, i, total;
    k.LowPart = kernel_time.dwLowDateTime;
    k.HighPart = kernel_time.dwHighDateTime;
    u.LowPart = user_time.dwLowDateTime;
    u.HighPart = user_time.dwHighDateTime;
    i.LowPart = idle_time.dwLowDateTime;
    i.HighPart = idle_time.dwHighDateTime;
    total.QuadPart = (k.QuadPart + u.QuadPart);
    cpu_time.QuadPart = total.QuadPart - i.QuadPart;
  }
}