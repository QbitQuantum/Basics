/**
 * @file
 * @brief 
 * Total Ram
 *
 * @details
 * This function looks up the total ram in bytes.
 *
 * @param totalram
 * Output, passed by reference.  On successful return, the value
 * is set to the total ram (in bytes) available on the system.
 *
 * @return
 * The return value indicates the status of the function.
 */
int meminfo_totalram(memsize_t *totalram)
{
  int ret = MEMINFO_OK;
  *totalram = 0L;
  
  
#if OS_LINUX
  struct sysinfo info;
  int test = sysinfo(&info);
  chkret(test, FAILURE);
  
  *totalram = (memsize_t) info.totalram * info.mem_unit;
#elif OS_MAC
  int test = sysctl_val("hw.memsize", totalram);
  chkret(test, FAILURE);
#elif OS_WINDOWS
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(status);
  
  int test = GlobalMemoryStatusEx(&status);
  winchkret(test, FAILURE);
  
  *totalram = (memsize_t) status.ullTotalPhys;
#elif OS_FREEBSD
  int test = sysctl_val("hw.physmem", totalram);
  chkret(test, FAILURE);
#elif OS_NIX
  memsize_t npages, pagesize;
  
  npages = sysconf(_SC_PHYS_PAGES);
  if (npages == FAILURE)
    return FAILURE;
  
  pagesize = sysconf(_SC_PAGESIZE);
  if (pagesize == FAILURE)
    return FAILURE;
  
  *totalram = (memsize_t) npages * pagesize;
#else
  ret = PLATFORM_ERROR;
#endif
  
  return ret;
}