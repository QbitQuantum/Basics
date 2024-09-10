static int
hwloc_win_set_proc_cpubind(hwloc_topology_t topology __hwloc_attribute_unused, hwloc_pid_t proc, hwloc_const_bitmap_t hwloc_set, int flags)
{
  DWORD_PTR mask;

  assert(nr_processor_groups == 1);

  if (flags & HWLOC_CPUBIND_NOMEMBIND) {
    errno = ENOSYS;
    return -1;
  }

  /* TODO: SetThreadGroupAffinity() for all threads doesn't enforce the whole process affinity,
   * maybe because of process-specific resource locality */
  /* TODO: if we are in a single group (check with GetProcessGroupAffinity()),
   * SetProcessAffinityMask() changes the binding within that same group.
   */
  /* TODO: NtSetInformationProcess() works very well for binding to any mask in a single group,
   * but it's an internal routine.
   */
  /* TODO: checks whether hwloc-bind.c needs to pass INHERIT_PARENT_AFFINITY to CreateProcess() instead of execvp(). */

  /* The resulting binding is always strict */
  mask = hwloc_bitmap_to_ULONG_PTR(hwloc_set);
  if (!SetProcessAffinityMask(proc, mask))
    return -1;
  return 0;
}