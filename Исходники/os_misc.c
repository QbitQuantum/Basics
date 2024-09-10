/**
 * Return the size of the total physical memory.
 * \param size returns the size of the total physical memory
 * \return true for success, or false on failure
 */
bool
os_get_total_physical_memory(uint64_t *size)
{
#if defined(PIPE_OS_LINUX)
   const long phys_pages = sysconf(_SC_PHYS_PAGES);
   const long page_size = sysconf(_SC_PAGE_SIZE);

   *size = phys_pages * page_size;
   return (phys_pages > 0 && page_size > 0);
#elif defined(PIPE_OS_APPLE) || defined(PIPE_OS_BSD)
   size_t len = sizeof(size);
   int mib[2];

   mib[0] = CTL_HW;
#if defined(PIPE_OS_APPLE)
   mib[1] = HW_MEMSIZE;
#elif defined(PIPE_OS_NETBSD) || defined(PIPE_OS_OPENBSD)
   mib[1] = HW_PHYSMEM64;
#elif defined(PIPE_OS_FREEBSD)
   mib[1] = HW_REALMEM;
#else
#error Unsupported *BSD
#endif

   return (sysctl(mib, 2, &size, &len, NULL, 0) == 0);
#elif defined(PIPE_OS_HAIKU)
   system_info info;
   status_t ret;

   ret = get_system_info(&info);
   *size = info.max_pages * B_PAGE_SIZE;
   return (ret == B_OK);
#elif defined(PIPE_OS_WINDOWS)
   MEMORYSTATUSEX status;
   BOOL ret;

   status.dwLength = sizeof(status);
   ret = GlobalMemoryStatusEx(&status);
   *size = status.ullTotalPhys;
   return (ret == TRUE);
#else
#error unexpected platform in os_sysinfo.c
   return false;
#endif
}