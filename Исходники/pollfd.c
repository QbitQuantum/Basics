int
epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout)
{
  struct epoll_event* ee;
  DWORD ct;
  FD_SET fdset[3];
  WSANETWORKEVENTS wev;
  ee = &_epoll_events[epfd];
  struct timeval tv, *tp;
  if (!ee) return -1;
  if (timeout < 0) tp = NULL;
  else {
    tv.tv_sec = timeout/1000;
    tv.tv_usec = (timeout%1000)*1000000;
    tp = &tv;
  }
  ct = GetTickCount();
  while (GetTickCount() - ct < timeout) {
    int i, e = 0;
    for (i = 0; i < FD_SETSIZE; i++) {
      if (ee->fds[i] < 0) continue;
      if (WSAEnumNetworkEvents((SOCKET) ee->fds[i], NULL, &wev) == 0) {
        FD_ZERO(&fdset[0]);
        FD_ZERO(&fdset[1]);
        FD_ZERO(&fdset[2]);
        if (ee->events & EPOLLIN) FD_SET(ee->fds[i], &fdset[0]);
        if (ee->events & EPOLLOUT) FD_SET(ee->fds[i], &fdset[1]);
        if (ee->events & EPOLLERR) FD_SET(ee->fds[i], &fdset[2]);
        if (select(1, &fdset[0], &fdset[1], &fdset[2], tp) > 0 &&
            (FD_ISSET(ee->fds[i], &fdset[0]) ||
             FD_ISSET(ee->fds[i], &fdset[1]) ||
             FD_ISSET(ee->fds[i], &fdset[2]))) {
          events[e++] = *ee;
          if (ee->events & EPOLLONESHOT)
            ee->fds[i] = -1;
        }
      } else {
        HANDLE h = (HANDLE) _get_osfhandle(ee->fds[i]);
        if (h != INVALID_HANDLE_VALUE && WaitForSingleObject(h, timeout < 0 ? INFINITE : timeout) == WAIT_OBJECT_0) {
          events[e++] = *ee;
          if (ee->events & EPOLLONESHOT)
            ee->fds[i] = -1;
        }
      }
      if (e >= maxevents) break;
    }
    if (e > 0) return e;
    if (timeout == -1) break;
  }
  return 0;
}