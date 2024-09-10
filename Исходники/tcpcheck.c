/*
 * We've initiated all connection attempts.
 * Here we sit and wait for them to complete.
 */
static void waitforconnects()
{
  fd_set writefds, exceptfds;
  struct timeval timeleft;
  struct timeval starttime;
  struct timeval curtime;
  struct timeval timeoutval;
  struct timeval timeused;
  struct sockaddr_in dummysock;
  int dummyint = sizeof(dummysock);
  int numfds;
  int res;
  int i;

  gettimeofday(&starttime, NULL);
  
  timeoutval.tv_sec = timeout;
  timeoutval.tv_usec = 0;

  timeleft = timeoutval;
 
  while (1)
  {
    FD_ZERO(&writefds);
    FD_ZERO(&exceptfds);
    setupset(&writefds, &numfds);
    setupset(&exceptfds, &numfds);
    res = select(numfds+1, NULL, &writefds, &exceptfds, &timeleft);

    if (res == -1) {
      perror("select barfed, bailing");
      exit(-1);
    }

    if (res == 0)		/* We timed out */
      break;

    /* Oooh.  We have some successes */
    /* First test the exceptions */

    for (i = 0; i < numcons; i++)
    {
      if (cons[i] == NULL) continue;
      if (FD_ISSET(cons[i]->socket, &exceptfds)) {
				failedconnect(i);
      }
      else if (FD_ISSET(cons[i]->socket, &writefds)) {
				/* Boggle.  It's not always good.  select() is weird. */
				if (getpeername(cons[i]->socket, (struct sockaddr *)&dummysock, &dummyint))
					failedconnect(i);
				else
					goodconnect(i);
			}
		}

		/* now, timeleft = timeoutval - timeused */

		gettimeofday(&curtime, NULL);
		subtime(&curtime, &starttime, &timeused);
		subtime(&timeoutval, &timeused, &timeleft);
	}

  /* Now clean up the remainder... they timed out. */
  for (i = 0; i < numcons; i++) {
    if (cons[i]->status == 0) {
      printf("%s:%d failed:  timed out\n",
	     cons[i]->hostname, cons[i]->port);
    }
  }
}