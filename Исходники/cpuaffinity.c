/* CPU affinity mask buffer instead, as the present code will fail beyond 32 CPUs */
int set_cpu_affinity(unsigned int cpuid) {
  unsigned long mask = 0xffffffff;
  unsigned int len = sizeof(mask);
  int retValue = 0;
  int pid;

 #ifdef _WIN32
   HANDLE hProcess;
 #endif
 
#ifdef _WIN32
  SET_MASK(cpuid)
  hProcess = GetCurrentProcess();
  if (SetProcessAffinityMask(hProcess, mask) == 0) {
    return -1;
  }
#elif CMK_HAS_BINDPROCESSOR
  pid = getpid();
  if (bindprocessor(BINDPROCESS, pid, cpuid) == -1) return -1;
#else
#ifdef CPU_ALLOC
 if ( cpuid >= CPU_SETSIZE ) {
  cpu_set_t *cpusetp;
  size_t size;
  int num_cpus;
  num_cpus = cpuid + 1;
  cpusetp = CPU_ALLOC(num_cpus);
  if (cpusetp == NULL) {
    perror("set_cpu_affinity CPU_ALLOC");
    return -1;
  }
  size = CPU_ALLOC_SIZE(num_cpus);
  CPU_ZERO_S(size, cpusetp);
  CPU_SET_S(cpuid, size, cpusetp);
  if (sched_setaffinity(0, size, cpusetp) < 0) {
    perror("sched_setaffinity dynamically allocated");
    CPU_FREE(cpusetp);
    return -1;
  }
  CPU_FREE(cpusetp);
 } else
#endif
 {
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(cpuid, &cpuset);
  /*SET_MASK(cpuid)*/

  /* PID 0 refers to the current process */
  /*if (sched_setaffinity(0, len, &mask) < 0) {*/
  if (sched_setaffinity(0, sizeof(cpuset), &cpuset) < 0) {
    perror("sched_setaffinity");
    return -1;
  }
 }
#endif

  return 0;
}