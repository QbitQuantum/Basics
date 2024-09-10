static int select_ws(int nfds, fd_set *readfds, fd_set *writefds,
                     fd_set *exceptfds, struct timeval *timeout)
{
  DWORD milliseconds, wait, idx;
  WSANETWORKEVENTS wsanetevents;
  struct select_ws_data *data;
  HANDLE handle, *handles;
  curl_socket_t sock;
  long networkevents;
  WSAEVENT wsaevent;
  int error, fds;
  HANDLE waitevent = NULL;
  DWORD nfd = 0, thd = 0, wsa = 0;
  int ret = 0;

  /* check if the input value is valid */
  if(nfds < 0) {
    errno = EINVAL;
    return -1;
  }

  /* check if we got descriptors, sleep in case we got none */
  if(!nfds) {
    Sleep((timeout->tv_sec*1000)+(DWORD)(((double)timeout->tv_usec)/1000.0));
    return 0;
  }

  /* create internal event to signal waiting threads */
  waitevent = CreateEvent(NULL, TRUE, FALSE, NULL);
  if(!waitevent) {
    errno = ENOMEM;
    return -1;
  }

  /* allocate internal array for the internal data */
  data = malloc(nfds * sizeof(struct select_ws_data));
  if(data == NULL) {
    errno = ENOMEM;
    return -1;
  }

  /* allocate internal array for the internal event handles */
  handles = malloc(nfds * sizeof(HANDLE));
  if(handles == NULL) {
    free(data);
    errno = ENOMEM;
    return -1;
  }

  /* clear internal arrays */
  memset(data, 0, nfds * sizeof(struct select_ws_data));
  memset(handles, 0, nfds * sizeof(HANDLE));

  /* loop over the handles in the input descriptor sets */
  for(fds = 0; fds < nfds; fds++) {
    networkevents = 0;
    handles[nfd] = 0;

    if(FD_ISSET(fds, readfds))
      networkevents |= FD_READ|FD_ACCEPT|FD_CLOSE;

    if(FD_ISSET(fds, writefds))
      networkevents |= FD_WRITE|FD_CONNECT;

    if(FD_ISSET(fds, exceptfds))
      networkevents |= FD_OOB|FD_CLOSE;

    /* only wait for events for which we actually care */
    if(networkevents) {
      data[nfd].fd = curlx_sitosk(fds);
      if(fds == fileno(stdin)) {
        handle = GetStdHandle(STD_INPUT_HANDLE);
        handle = select_ws_wait(handle, waitevent);
        handles[nfd] = handle;
        data[thd].thread = handle;
        thd++;
      }
      else if(fds == fileno(stdout)) {
        handles[nfd] = GetStdHandle(STD_OUTPUT_HANDLE);
      }
      else if(fds == fileno(stderr)) {
        handles[nfd] = GetStdHandle(STD_ERROR_HANDLE);
      }
      else {
        wsaevent = WSACreateEvent();
        if(wsaevent != WSA_INVALID_EVENT) {
          error = WSAEventSelect(fds, wsaevent, networkevents);
          if(error != SOCKET_ERROR) {
            handle = (HANDLE) wsaevent;
            handles[nfd] = handle;
            data[wsa].wsasock = curlx_sitosk(fds);
            data[wsa].wsaevent = wsaevent;
            wsa++;
          }
          else {
            WSACloseEvent(wsaevent);
            handle = (HANDLE) curlx_sitosk(fds);
            handle = select_ws_wait(handle, waitevent);
            handles[nfd] = handle;
            data[thd].thread = handle;
            thd++;
          }
        }
      }
      nfd++;
    }
  }

  /* convert struct timeval to milliseconds */
  if(timeout) {
    milliseconds = ((timeout->tv_sec * 1000) + (timeout->tv_usec / 1000));
  }
  else {
    milliseconds = INFINITE;
  }

  /* wait for one of the internal handles to trigger */
  wait = WaitForMultipleObjectsEx(nfd, handles, FALSE, milliseconds, FALSE);

  /* signal the event handle for the waiting threads */
  SetEvent(waitevent);

  /* loop over the internal handles returned in the descriptors */
  for(idx = 0; idx < nfd; idx++) {
    handle = handles[idx];
    sock = data[idx].fd;
    fds = curlx_sktosi(sock);

    /* check if the current internal handle was triggered */
    if(wait != WAIT_FAILED && (wait - WAIT_OBJECT_0) <= idx &&
       WaitForSingleObjectEx(handle, 0, FALSE) == WAIT_OBJECT_0) {
      /* first handle stdin, stdout and stderr */
      if(fds == fileno(stdin)) {
        /* stdin is never ready for write or exceptional */
        FD_CLR(sock, writefds);
        FD_CLR(sock, exceptfds);
      }
      else if(fds == fileno(stdout) || fds == fileno(stderr)) {
        /* stdout and stderr are never ready for read or exceptional */
        FD_CLR(sock, readfds);
        FD_CLR(sock, exceptfds);
      }
      else {
        /* try to handle the event with the WINSOCK2 functions */
        wsanetevents.lNetworkEvents = 0;
        error = WSAEnumNetworkEvents(fds, handle, &wsanetevents);
        if(error != SOCKET_ERROR) {
          /* remove from descriptor set if not ready for read/accept/close */
          if(!(wsanetevents.lNetworkEvents & (FD_READ|FD_ACCEPT|FD_CLOSE)))
            FD_CLR(sock, readfds);

          /* remove from descriptor set if not ready for write/connect */
          if(!(wsanetevents.lNetworkEvents & (FD_WRITE|FD_CONNECT)))
            FD_CLR(sock, writefds);

          /* HACK:
           * use exceptfds together with readfds to signal
           * that the connection was closed by the client.
           *
           * Reason: FD_CLOSE is only signaled once, sometimes
           * at the same time as FD_READ with data being available.
           * This means that recv/sread is not reliable to detect
           * that the connection is closed.
           */
          /* remove from descriptor set if not exceptional */
          if(!(wsanetevents.lNetworkEvents & (FD_OOB|FD_CLOSE)))
            FD_CLR(sock, exceptfds);
        }
      }

      /* check if the event has not been filtered using specific tests */
      if(FD_ISSET(sock, readfds) || FD_ISSET(sock, writefds) ||
         FD_ISSET(sock, exceptfds)) {
        ret++;
      }
    }
    else {
      /* remove from all descriptor sets since this handle did not trigger */
      FD_CLR(sock, readfds);
      FD_CLR(sock, writefds);
      FD_CLR(sock, exceptfds);
    }
  }

  for(fds = 0; fds < nfds; fds++) {
    if(FD_ISSET(fds, readfds))
      logmsg("select_ws: %d is readable", fds);

    if(FD_ISSET(fds, writefds))
      logmsg("select_ws: %d is writable", fds);

    if(FD_ISSET(fds, exceptfds))
      logmsg("select_ws: %d is excepted", fds);
  }

  for(idx = 0; idx < wsa; idx++) {
    WSAEventSelect(data[idx].wsasock, NULL, 0);
    WSACloseEvent(data[idx].wsaevent);
  }

  for(idx = 0; idx < thd; idx++) {
    WaitForSingleObject(data[idx].thread, INFINITE);
    CloseHandle(data[idx].thread);
  }

  CloseHandle(waitevent);

  free(handles);
  free(data);

  return ret;
}