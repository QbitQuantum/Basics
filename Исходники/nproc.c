/* Return the number of processors available to the current process, based
   on a modern system call that returns the "affinity" between the current
   process and each CPU.  Return 0 if unknown or if such a system call does
   not exist.  */
static unsigned long
num_processors_via_affinity_mask (void)
{
    /* glibc >= 2.3.3 with NPTL and NetBSD 5 have pthread_getaffinity_np,
       but with different APIs.  Also it requires linking with -lpthread.
       Therefore this code is not enabled.
       glibc >= 2.3.4 has sched_getaffinity whereas NetBSD 5 has
       sched_getaffinity_np.  */
#if HAVE_PTHREAD_GETAFFINITY_NP && defined __GLIBC__ && 0
    {
        cpu_set_t set;

        if (pthread_getaffinity_np (pthread_self (), sizeof (set), &set) == 0)
        {
            unsigned long count;

# ifdef CPU_COUNT
            /* glibc >= 2.6 has the CPU_COUNT macro.  */
            count = CPU_COUNT (&set);
# else
            size_t i;

            count = 0;
            for (i = 0; i < CPU_SETSIZE; i++)
                if (CPU_ISSET (i, &set))
                    count++;
# endif
            if (count > 0)
                return count;
        }
    }
#elif HAVE_PTHREAD_GETAFFINITY_NP && defined __NetBSD__ && 0
    {
        cpuset_t *set;

        set = cpuset_create ();
        if (set != NULL)
        {
            unsigned long count = 0;

            if (pthread_getaffinity_np (pthread_self (), cpuset_size (set), set)
                    == 0)
            {
                cpuid_t i;

                for (i = 0;; i++)
                {
                    int ret = cpuset_isset (i, set);
                    if (ret < 0)
                        break;
                    if (ret > 0)
                        count++;
                }
            }
            cpuset_destroy (set);
            if (count > 0)
                return count;
        }
    }
#elif HAVE_SCHED_GETAFFINITY_LIKE_GLIBC /* glibc >= 2.3.4 */
    {
        cpu_set_t set;

        if (sched_getaffinity (0, sizeof (set), &set) == 0)
        {
            unsigned long count;

# ifdef CPU_COUNT
            /* glibc >= 2.6 has the CPU_COUNT macro.  */
            count = CPU_COUNT (&set);
# else
            size_t i;

            count = 0;
            for (i = 0; i < CPU_SETSIZE; i++)
                if (CPU_ISSET (i, &set))
                    count++;
# endif
            if (count > 0)
                return count;
        }
    }
#elif HAVE_SCHED_GETAFFINITY_NP /* NetBSD >= 5 */
    {
        cpuset_t *set;

        set = cpuset_create ();
        if (set != NULL)
        {
            unsigned long count = 0;

            if (sched_getaffinity_np (getpid (), cpuset_size (set), set) == 0)
            {
                cpuid_t i;

                for (i = 0;; i++)
                {
                    int ret = cpuset_isset (i, set);
                    if (ret < 0)
                        break;
                    if (ret > 0)
                        count++;
                }
            }
            cpuset_destroy (set);
            if (count > 0)
                return count;
        }
    }
#endif

#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
    {   /* This works on native Windows platforms.  */
        DWORD_PTR process_mask;
        DWORD_PTR system_mask;

        if (GetProcessAffinityMask (GetCurrentProcess (),
                                    &process_mask, &system_mask))
        {
            DWORD_PTR mask = process_mask;
            unsigned long count = 0;

            for (; mask != 0; mask = mask >> 1)
                if (mask & 1)
                    count++;
            if (count > 0)
                return count;
        }
    }