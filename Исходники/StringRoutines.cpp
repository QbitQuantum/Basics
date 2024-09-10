static long long AvailableMemory() {
#ifdef _MSC_VER
  MEMORYSTATUS status;
  GlobalMemoryStatus(&status);
  if (status.dwLength != sizeof(status))
    return -1;
  return (long long)status.dwAvailPhys;
#elif defined(__APPLE__)
  mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
  vm_statistics_data_t vmstat;
  if (KERN_SUCCESS == host_statistics(mach_host_self(), HOST_VM_INFO,
                                      (host_info_t)&vmstat, &count)) {
    double total = vmstat.wire_count + vmstat.active_count +
                   vmstat.inactive_count + vmstat.free_count;
    double free = vmstat.free_count / total; // fraction
    return (long long)(TotalGlobalMemory() * free);
  }
  return -1;
#elif defined(_SC_AVPHYS_PAGES) && defined(_SC_PAGE_SIZE)
  long pages = sysconf(_SC_AVPHYS_PAGES);
  long page_size = sysconf(_SC_PAGE_SIZE);
  if (pages < 0L || page_size < 0L) return -1;
  return (long long)(pages * page_size);
#else
  return -1;
#endif
}