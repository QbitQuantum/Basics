/** 
 *  \brief Maps the calling thread to the given CPU.
 *
 *  It maps the calling thread to the given core. It works on Linux OS, Apple
 *  OS, Windows.
 *
 *  \param cpu_id the ID of the CPU to which the thread will be attached.
 *  \param priority_level TODO
 *
 *  \return An integet value showing the priority level is returned if
 *  successful. Otherwise \p EINVAL is returned.
 */
static inline int ff_mapThreadToCpu(int cpu_id, int priority_level=0) {
    if (cpu_id > ff_numCores()) return EINVAL;
#if defined(__linux__) && defined(CPU_SET)
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu_id, &mask);
    if (sched_setaffinity(gettid(), sizeof(mask), &mask) != 0) 
        return EINVAL;
    return (ff_setPriority(priority_level));
#elif defined(__APPLE__) && MAC_OS_X_HAS_AFFINITY
    // Mac OS does not implement direct pinning of threads onto cores.
    // Threads can be organised in affinity set. Using requested CPU
    // tag for the set. Cores under the same L2 cache are not distinguished. 
    // Should be called before running the thread.
#define CACHE_LEVELS 3
    #define CACHE_L2 2
    size_t len;

    if (sysctlbyname("hw.cacheconfig",NULL, &len, NULL, 0) != 0) {
        perror("sysctl");
    } else {
      int64_t cacheconfig[len];
      if (sysctlbyname("hw.cacheconfig", &cacheconfig[0], &len, NULL, 0) != 0)
        perror("sysctl: unable to get hw.cacheconfig");
      else {
      /*
          for (size_t i=0;i<CACHE_LEVELS;i++)
          std::cerr << " Cache " << i << " shared by " <<  cacheconfig[i] << " cores\n";
      */
      struct thread_affinity_policy mypolicy;
      // Define sets taking in account pinning is performed on L2
      mypolicy.affinity_tag = cpu_id/cacheconfig[CACHE_L2];
      if ( thread_policy_set(mach_thread_self(), THREAD_AFFINITY_POLICY, (integer_t*) &mypolicy, THREAD_AFFINITY_POLICY_COUNT) != KERN_SUCCESS ) {
      std::cerr << "Setting affinity of thread ? (" << mach_thread_self() << ") failed!" << std::endl;
      return EINVAL;
      } // else {
      //   std::cerr << "Sucessfully set affinity of thread (" << 
      //   mach_thread_self() << ") to core " << cpu_id/cacheconfig[CACHE_L2] << "\n";
      // }
      }
   }

    return(ff_setPriority(priority_level));
#elif (defined(_MSC_VER) || defined(__INTEL_COMPILER)) && defined(_WIN32)
    if (-1==SetThreadIdealProcessor(GetCurrentThread(),cpu_id)) {
        perror("ff_mapThreadToCpu:SetThreadIdealProcessor");
        return EINVAL;
    }
    //std::cerr << "Successfully set affinity of thread " << GetCurrentThreadId() << " to core " << cpu_id << "\n";
#else 
#warning "CPU_SET not defined, cannot map thread to specific CPU"
#endif
    return 0;
}