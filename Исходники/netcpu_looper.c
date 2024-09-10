static void
bind_to_processor(int child_num)
{
  /* This routine will bind the calling process to a particular */
  /* processor. We are not choosy as to which processor, so it will be */
  /* the process id mod the number of processors - shifted by one for */
  /* those systems which name processor starting from one instead of */
  /* zero. on those systems where I do not yet know how to bind a */
  /* process to a processor, this routine will be a no-op raj 10/95 */

  /* just as a reminder, this is *only* for the looper processes, not */
  /* the actual measurement processes. those will, should, MUST float */
  /* or not float from CPU to CPU as controlled by the operating */
  /* system defaults. raj 12/95 */

#ifdef __hpux
#include <sys/syscall.h>
#include <sys/mp.h>

  int old_cpu = -2;

  if (debug) {
    fprintf(where,
            "child %d asking for CPU %d as pid %d with %d CPUs\n",
            child_num,
            (child_num % lib_num_loc_cpus),
            getpid(),
            lib_num_loc_cpus);
    fflush(where);
  }

  SETPROCESS((child_num % lib_num_loc_cpus), getpid());
  return;

#else
#if defined(__sun) && defined(__SVR4)
 /* should only be Solaris */
#include <sys/processor.h>
#include <sys/procset.h>

  int old_binding;

  if (debug) {
    fprintf(where,
            "bind_to_processor: child %d asking for CPU %d as pid %d with %d CPUs\n",
            child_num,
            (child_num % lib_num_loc_cpus),
            getpid(),
            lib_num_loc_cpus);
    fflush(where);
  }

  if (processor_bind(P_PID,
                     getpid(),
                     (child_num % lib_num_loc_cpus), 
                      &old_binding) != 0) {
    fprintf(where,"bind_to_processor: unable to perform processor binding\n");
    fprintf(where,"                   errno %d\n",errno);
    fflush(where);
  }
  return;
#else
#ifdef WIN32

  if (!SetThreadAffinityMask(GetCurrentThread(), (ULONG_PTR)1 << (child_num % lib_num_loc_cpus))) {
    perror("SetThreadAffinityMask failed");
    fflush(stderr);
  }

  if (debug) {
    fprintf(where,
            "bind_to_processor: child %d asking for CPU %d of %d CPUs\n",
            child_num,
            (child_num % lib_num_loc_cpus),
            lib_num_loc_cpus);
    fflush(where);
  }

#endif
  return;
#endif /* __sun && _SVR4 */
#endif /* __hpux */
}