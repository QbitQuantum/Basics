int select(int nfds, FAR fd_set *readfds, FAR fd_set *writefds,
           FAR fd_set *exceptfds, FAR struct timeval *timeout)
{
  struct pollfd *pollset;
  int errcode = OK;
  int fd;
  int npfds;
  int msec;
  int ndx;
  int ret;

  /* select() is cancellation point */

  (void)enter_cancellation_point();

  /* How many pollfd structures do we need to allocate? */

  /* Initialize the descriptor list for poll() */

  for (fd = 0, npfds = 0; fd < nfds; fd++)
    {
      /* Check if any monitor operation is requested on this fd */

      if ((readfds   && FD_ISSET(fd, readfds))  ||
          (writefds  && FD_ISSET(fd, writefds)) ||
          (exceptfds && FD_ISSET(fd, exceptfds)))
        {
          /* Yes.. increment the count of pollfds structures needed */

          npfds++;
        }
    }

  /* Allocate the descriptor list for poll() */

  pollset = (struct pollfd *)kmm_zalloc(npfds * sizeof(struct pollfd));
  if (!pollset)
    {
      set_errno(ENOMEM);
      leave_cancellation_point();
      return ERROR;
    }

  /* Initialize the descriptor list for poll() */

  for (fd = 0, ndx = 0; fd < nfds; fd++)
    {
      int incr = 0;

      /* The readfs set holds the set of FDs that the caller can be assured
       * of reading from without blocking.  Note that POLLHUP is included as
       * a read-able condition.  POLLHUP will be reported at the end-of-file
       * or when a connection is lost.  In either case, the read() can then
       * be performed without blocking.
       */

      if (readfds && FD_ISSET(fd, readfds))
        {
          pollset[ndx].fd      = fd;
          pollset[ndx].events |= POLLIN;
          incr                 = 1;
        }

      /* The writefds set holds the set of FDs that the caller can be assured
       * of writing to without blocking.
       */

      if (writefds && FD_ISSET(fd, writefds))
        {
          pollset[ndx].fd      = fd;
          pollset[ndx].events |= POLLOUT;
          incr                 = 1;
        }

      /* The exceptfds set holds the set of FDs that are watched for exceptions */

      if (exceptfds && FD_ISSET(fd, exceptfds))
        {
          pollset[ndx].fd      = fd;
          incr                  = 1;
        }

      ndx += incr;
    }

  DEBUGASSERT(ndx == npfds);

  /* Convert the timeout to milliseconds */

  if (timeout)
    {
      /* Calculate the timeout in milliseconds */

      msec = timeout->tv_sec * 1000 + timeout->tv_usec / 1000;
    }
  else
    {
      /* Any negative value of msec means no timeout */

      msec = -1;
    }

  /* Then let poll do all of the real work. */

  ret = poll(pollset, npfds, msec);
  if (ret < 0)
    {
      /* poll() failed! Save the errno value */

      errcode = get_errno();
    }

  /* Now set up the return values */

  if (readfds)
    {
      memset(readfds, 0, sizeof(fd_set));
    }

  if (writefds)
    {
      memset(writefds, 0, sizeof(fd_set));
    }

  if (exceptfds)
    {
      memset(exceptfds, 0, sizeof(fd_set));
    }

  /* Convert the poll descriptor list back into selects 3 bitsets */

  if (ret > 0)
    {
      ret = 0;
      for (ndx = 0; ndx < npfds; ndx++)
        {
          /* Check for read conditions.  Note that POLLHUP is included as a
           * read condition.  POLLHUP will be reported when no more data will
           * be available (such as when a connection is lost).  In either
           * case, the read() can then be performed without blocking.
           */

          if (readfds)
            {
              if (pollset[ndx].revents & (POLLIN | POLLHUP))
                {
                  FD_SET(pollset[ndx].fd, readfds);
                  ret++;
                }
            }

          /* Check for write conditions */

          if (writefds)
            {
              if (pollset[ndx].revents & POLLOUT)
                {
                  FD_SET(pollset[ndx].fd, writefds);
                  ret++;
                }
            }

          /* Check for exceptions */

          if (exceptfds)
            {
              if (pollset[ndx].revents & POLLERR)
                {
                  FD_SET(pollset[ndx].fd, exceptfds);
                  ret++;
                }
            }
        }
    }

  kmm_free(pollset);

  /* Did poll() fail above? */

  if (ret < 0)
    {
      /* Yes.. restore the errno value */

      set_errno(errcode);
    }

  leave_cancellation_point();
  return ret;
}