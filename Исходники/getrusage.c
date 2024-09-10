int getrusage(int who, struct rusage *usage)
{
  FILETIME creation_time, exit_time, kernel_time, user_time;
  PROCESS_MEMORY_COUNTERS pmc;

  memset(usage, 0, sizeof(struct rusage));

  if(who == RUSAGE_SELF)
  {
    if(!GetProcessTimes(GetCurrentProcess(), &creation_time, &exit_time, &kernel_time, &user_time))
    {
      fprintf(stdout, "failed at GetProcessTimes\n");
      return -1;
    }

    if(!GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
    {
      fprintf(stdout, "failed at GetProcessMemoryInfo\n");
      return -1;
    }

    usage_to_timeval(&kernel_time, &usage->ru_stime);
    usage_to_timeval(&user_time, &usage->ru_utime);
    usage->ru_majflt = pmc.PageFaultCount;
    usage->ru_maxrss = pmc.PeakWorkingSetSize / 1024;
    return 0;
  }
  else if(who == RUSAGE_THREAD)
  {
    if(!GetThreadTimes(GetCurrentThread(), &creation_time, &exit_time, &kernel_time, &user_time))
    {
      fprintf(stdout, "failed at GetThreadTimes\n");
      return -1;
    }
    usage_to_timeval(&kernel_time, &usage->ru_stime);
    usage_to_timeval(&user_time, &usage->ru_utime);
    return 0;
  }
  else
  {
    return -1;
  }
}