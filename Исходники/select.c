/* ==========================================================================
 * select() 
 */
int select(int numfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout)
{
  fd_set real_exceptfds, real_readfds, real_writefds; /* mapped fd_sets */
  fd_set * real_readfds_p, * real_writefds_p, * real_exceptfds_p;
  fd_set read_locks, write_locks, rdwr_locks;
  struct timespec timeout_time, current_time;
  int i, j, ret = 0, got_all_locks = 1;
  struct pthread_select_data data;

  if (numfds > dtablesize) {
    numfds = dtablesize;
  }

  data.nfds = 0;
  FD_ZERO(&data.readfds);
  FD_ZERO(&data.writefds);
  FD_ZERO(&data.exceptfds);

  /* Do this first */
  if (timeout) {
    machdep_gettimeofday(&current_time);
    timeout_time.tv_sec = current_time.tv_sec + timeout->tv_sec;
    if ((timeout_time.tv_nsec = current_time.tv_nsec + 
	 (timeout->tv_usec * 1000)) > 1000000000) {
      timeout_time.tv_nsec -= 1000000000;
      timeout_time.tv_sec++;
    }
  }

  FD_ZERO(&read_locks);
  FD_ZERO(&write_locks);
  FD_ZERO(&rdwr_locks);
  FD_ZERO(&real_readfds);
  FD_ZERO(&real_writefds);
  FD_ZERO(&real_exceptfds);

  /* lock readfds */
  if (readfds || writefds || exceptfds) {
    for (i = 0; i < numfds; i++) {
      if ((readfds && (FD_ISSET(i, readfds))) || 
	  (exceptfds && FD_ISSET(i, exceptfds))) {
	if (writefds && FD_ISSET(i ,writefds)) {
	  if ((ret = fd_lock(i, FD_RDWR, NULL)) != OK) {
	    got_all_locks = 0;
	    break;
	  }
	  FD_SET(i, &rdwr_locks);
	  FD_SET(fd_table[i]->fd.i,&real_writefds);
	} else {
	  if ((ret = fd_lock(i, FD_READ, NULL)) != OK) {
	    got_all_locks = 0;
	    break;
	  }
	  FD_SET(i, &read_locks);
	}
	if (readfds && FD_ISSET(i,readfds)) {
	  FD_SET(fd_table[i]->fd.i, &real_readfds);
	}
	if (exceptfds && FD_ISSET(i,exceptfds)) {
	  FD_SET(fd_table[i]->fd.i, &real_exceptfds);
	}
	if (fd_table[i]->fd.i >= data.nfds) {
	  data.nfds = fd_table[i]->fd.i + 1;
	}
      } else {
	if (writefds && FD_ISSET(i, writefds)) {
	  if ((ret = fd_lock(i, FD_WRITE, NULL)) != OK) {
	    got_all_locks = 0;
	    break;
	  }
	  FD_SET(i, &write_locks);
	  FD_SET(fd_table[i]->fd.i,&real_writefds);
	  if (fd_table[i]->fd.i >= data.nfds) {
	    data.nfds = fd_table[i]->fd.i + 1;
	  }
	}
      }
    }
  }

  if (got_all_locks)
  {
    memcpy(&data.readfds,&real_readfds,sizeof(fd_set));
    memcpy(&data.writefds,&real_writefds,sizeof(fd_set));
    memcpy(&data.exceptfds,&real_exceptfds,sizeof(fd_set));

    real_readfds_p = (readfds == NULL) ? NULL : &real_readfds;
    real_writefds_p = (writefds == NULL) ? NULL : &real_writefds;
    real_exceptfds_p = (exceptfds == NULL) ? NULL : &real_exceptfds;

    pthread_run->sighandled=0;
    if ((ret = machdep_sys_select(data.nfds, real_readfds_p,
				  real_writefds_p, real_exceptfds_p,
				  &zero_timeout)) == OK) {
      pthread_sched_prevent();

      real_exceptfds_p = (exceptfds == NULL) ? NULL : &data.exceptfds;
      real_writefds_p = (writefds == NULL) ? NULL : &data.writefds;
      real_readfds_p = (readfds == NULL) ? NULL : &data.readfds;

      pthread_queue_enq(&fd_wait_select, pthread_run);
      pthread_run->data.select_data = &data;
      SET_PF_WAIT_EVENT(pthread_run);

      if (timeout) {
	machdep_gettimeofday(&current_time);
	sleep_schedule(&current_time, &timeout_time);

	SET_PF_AT_CANCEL_POINT(pthread_run);
	pthread_resched_resume(PS_SELECT_WAIT);
	CLEAR_PF_AT_CANCEL_POINT(pthread_run);

	/* We're awake */
	if (sleep_cancel(pthread_run) == NOTOK) {
	  ret = OK;
	}
	else
	{
	  int count = 0;
	  for (i = 0; i < numfds; i++)
	  {
	    if (real_readfds_p && (FD_ISSET(i, real_readfds_p)))
	      count++;
	  if (real_writefds_p && (FD_ISSET(i, real_writefds_p)))
	    count++;
	  if (real_exceptfds_p && (FD_ISSET(i, real_exceptfds_p)))
	    count++;
	  }
	  ret = count;
	}
      /* Moving this after the sleep_cancel() seemed
       * to fix intermittent crashes during heavy
       * socket use. (mevans)
       */
      CLEAR_PF_DONE_EVENT(pthread_run);
    } else {
      int count = 0;
      SET_PF_AT_CANCEL_POINT(pthread_run);
      pthread_resched_resume(PS_SELECT_WAIT);
      CLEAR_PF_AT_CANCEL_POINT(pthread_run);
      CLEAR_PF_DONE_EVENT(pthread_run);
      for (i = 0; i < numfds; i++)
      {
	if (real_readfds_p && (FD_ISSET(i, real_readfds_p)))
	  count++;
	if (real_writefds_p && (FD_ISSET(i, real_writefds_p)))
	  count++;
	if (real_exceptfds_p && (FD_ISSET(i, real_exceptfds_p)))
	  count++;
      }
      ret = count;
    }
    if (pthread_run->sighandled) /* Added by monty */
    {			/* We where aborted */
      ret= NOTOK;
      SET_ERRNO(EINTR);
    }
  } else if (ret < 0) {
      SET_ERRNO(-ret);
      ret = NOTOK;
    }
  }

  /* clean up the locks */
  for (i = 0; i < numfds; i++)
  {					/* Changed by monty */
    if (FD_ISSET(i,&read_locks)) fd_unlock(i,FD_READ);
    if (FD_ISSET(i,&rdwr_locks)) fd_unlock(i,FD_RDWR);
    if (FD_ISSET(i,&write_locks)) fd_unlock(i,FD_WRITE);
  }
  if (ret > 0) {
    if (readfds != NULL) {
      for (i = 0; i < numfds; i++) {
	if (! (FD_ISSET(i,readfds) &&
	       FD_ISSET(fd_table[i]->fd.i,real_readfds_p)))
	  FD_CLR(i,readfds);
      }
    }
    if (writefds != NULL) {
      for (i = 0; i < numfds; i++)
	if (! (FD_ISSET(i,writefds) &&
	       FD_ISSET(fd_table[i]->fd.i,real_writefds_p)))
	  FD_CLR(i,writefds);
    }
    if (exceptfds != NULL) {
      for (i = 0; i < numfds; i++)
	if (! (FD_ISSET(i,exceptfds) &&
	       FD_ISSET(fd_table[i]->fd.i,real_exceptfds_p)))
	  FD_CLR(i,exceptfds);
    }
  } else {
    if (exceptfds != NULL) FD_ZERO(exceptfds);
    if (writefds != NULL) FD_ZERO(writefds);
    if (readfds != NULL) FD_ZERO(readfds);
  }

  return(ret);
}