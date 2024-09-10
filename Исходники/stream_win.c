int w_poll_events(struct watchman_event_poll *p, int n, int timeoutms) {
  HANDLE handles[MAXIMUM_WAIT_OBJECTS];
  int i;
  DWORD res;

  if (n > MAXIMUM_WAIT_OBJECTS - 1) {
    // Programmer error :-/
    w_log(W_LOG_FATAL, "%d > MAXIMUM_WAIT_OBJECTS-1 (%d)\n", n,
        MAXIMUM_WAIT_OBJECTS - 1);
  }

  for (i = 0; i < n; i++) {
    handles[i] = p[i].evt;
    p[i].ready = false;
  }

  res = WaitForMultipleObjectsEx(n, handles, false, timeoutms, true);

  if (res == WAIT_FAILED) {
    errno = map_win32_err(GetLastError());
    return -1;
  }
  // Note: WAIT_OBJECT_0 == 0
  if (/* res >= WAIT_OBJECT_0 && */ res < WAIT_OBJECT_0 + n) {
    p[res - WAIT_OBJECT_0].ready = true;
    return 1;
  }
  if (res >= WAIT_ABANDONED_0 && res < WAIT_ABANDONED_0 + n) {
    p[res - WAIT_ABANDONED_0].ready = true;
    return 1;
  }
  return 0;
}