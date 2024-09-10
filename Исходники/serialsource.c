static int source_wait(serial_source src, struct timeval *deadline)
/* Effects: waits until deadline for some data on source. deadline
     can be NULL for indefinite waiting.
   Returns: 0 if data is available, -1 if the deadline expires
*/
{
#ifndef LOSE32
  struct timeval tv;
  fd_set fds;
  int cnt;

  if (src->recv.bufpos < src->recv.bufused)
    return 0;

  for (;;)
    {
      if (deadline)
	{
	  gettimeofday(&tv, NULL);
	  tv.tv_sec = deadline->tv_sec - tv.tv_sec;
	  tv.tv_usec = deadline->tv_usec - tv.tv_usec;
	  if (tv.tv_usec < 0)
	    {
	      tv.tv_usec += 1000000;
	      tv.tv_sec--;
	    }
	  if (tv.tv_sec < 0)
	    return -1;
	}

      FD_ZERO(&fds);
      FD_SET(src->fd, &fds);
      cnt = select(src->fd + 1, &fds, NULL, NULL, deadline ? &tv : NULL);
      if (cnt < 0)
	{
	  if (errno == EINTR)
	    continue;
	  message(src, msg_unix_error);
	  return -1;
	}
      if (cnt == 0)
	return -1;
      return 0;
    }
#else // LOSE32
    // FIXME: the deadline is ignored here

    DWORD eventMask;
    SetCommMask(src->hComm, EV_RXCHAR);
    if (!WaitCommEvent(src->hComm, &eventMask, NULL)) {
        return -1;
    }

    return 0;

#endif
}