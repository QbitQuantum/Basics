/**
 * Return the amount of USER time used by a thread.
 * 
 * @param[in] thread
 * @return actual time on USER used by thread (nanoseconds) or
 * negative value if not supported.
 */
I_64 VMCALL
hythread_get_user_time (hythread_t thread)
{

#if defined(WIN32)
  FILETIME creationTime, exitTime, kernelTime, userTime;
  I_64 totalTime;
  /* WARNING! Not supported on Win95!  Need to test to ensure this fails gracefully */
  if (GetThreadTimes
      (thread->handle, &creationTime, &exitTime, &kernelTime, &userTime))
    {
      totalTime =
	((I_64) userTime.
	 dwLowDateTime | ((I_64) userTime.dwHighDateTime << 32));
      /* totalTime is in 100's of nanos.  Convert to nanos */
      return totalTime * 100;
    }
#endif /* WIN32 */

  return -1;
}