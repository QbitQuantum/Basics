static vm_status vm_sys_info_remove_cpu_data(struct VM_SYSINFO_CPULOAD *dbuf) {
  vm_status rtval = VM_NULL_PTR;
  if (dbuf != NULL) {
    if (dbuf[0].CpuLoadQuery != 0)
      PdhCloseQuery(dbuf[0].CpuLoadQuery);
    if (dbuf[0].cpudes != NULL)
      free(dbuf[0].cpudes);
    free(dbuf);
    }
  return rtval;
  }