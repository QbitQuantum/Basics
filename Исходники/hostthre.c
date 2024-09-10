/*
 * init_resolve_thread() starts a new thread that performs the actual
 * resolve. This function returns before the resolve is done.
 *
 * Returns FALSE in case of failure, otherwise TRUE.
 */
static bool init_resolve_thread (struct connectdata *conn,
                                 const char *hostname, int port,
                                 const Curl_addrinfo *hints)
{
  struct thread_data *td = calloc(sizeof(*td), 1);
  HANDLE thread_and_event[2] = {0};

  if (!td) {
    SetLastError(ENOMEM);
    return FALSE;
  }

  Curl_safefree(conn->async.hostname);
  conn->async.hostname = strdup(hostname);
  if (!conn->async.hostname) {
    free(td);
    SetLastError(ENOMEM);
    return FALSE;
  }

  conn->async.port = port;
  conn->async.done = FALSE;
  conn->async.status = 0;
  conn->async.dns = NULL;
  conn->async.os_specific = (void*) td;
  td->dummy_sock = CURL_SOCKET_BAD;

  /* Create the mutex used to inform the resolver thread that we're
   * still waiting, and take initial ownership.
   */
  td->mutex_waiting = CreateMutex(NULL, TRUE, NULL);
  if (td->mutex_waiting == NULL) {
    Curl_destroy_thread_data(&conn->async);
    SetLastError(EAGAIN);
    return FALSE;
  }

  /* Create the event that the thread uses to inform us that it's
   * done resolving. Do not signal it.
   */
  td->event_resolved = CreateEvent(NULL, TRUE, FALSE, NULL);
  if (td->event_resolved == NULL) {
    Curl_destroy_thread_data(&conn->async);
    SetLastError(EAGAIN);
    return FALSE;
  }
  /* Create the mutex used to serialize access to event_terminated
   * between us and resolver thread.
   */
  td->mutex_terminate = CreateMutex(NULL, FALSE, NULL);
  if (td->mutex_terminate == NULL) {
    Curl_destroy_thread_data(&conn->async);
    SetLastError(EAGAIN);
    return FALSE;
  }
  /* Create the event used to signal thread that it should terminate.
   */
  td->event_terminate = CreateEvent(NULL, TRUE, FALSE, NULL);
  if (td->event_terminate == NULL) {
    Curl_destroy_thread_data(&conn->async);
    SetLastError(EAGAIN);
    return FALSE;
  }
  /* Create the event used by thread to inform it has initialized its own data.
   */
  td->event_thread_started = CreateEvent(NULL, TRUE, FALSE, NULL);
  if (td->event_thread_started == NULL) {
    Curl_destroy_thread_data(&conn->async);
    SetLastError(EAGAIN);
    return FALSE;
  }

  td->stderr_file = stderr;

#ifdef _WIN32_WCE
  td->thread_hnd = (HANDLE) CreateThread(NULL, 0,
                                         (LPTHREAD_START_ROUTINE) THREAD_FUNC,
                                         conn, 0, &td->thread_id);
#else
  td->thread_hnd = (HANDLE) _beginthreadex(NULL, 0, THREAD_FUNC,
                                           conn, 0, &td->thread_id);
#endif

#ifdef CURLRES_IPV6
  curlassert(hints);
  td->hints = *hints;
#else
  (void) hints;
#endif

  if (!td->thread_hnd) {
     SetLastError(errno);
     TRACE(("_beginthreadex() failed; %s\n", Curl_strerror(conn,errno)));
     Curl_destroy_thread_data(&conn->async);
     return FALSE;
  }
  /* Waiting until the thread will initialize its data or it will exit due errors.
   */
  thread_and_event[0] = td->thread_hnd;
  thread_and_event[1] = td->event_thread_started;
  if (WaitForMultipleObjects(sizeof(thread_and_event) /
                             sizeof(thread_and_event[0]),
                             thread_and_event, FALSE,
                             INFINITE) == WAIT_FAILED) {
    /* The resolver thread has been created,
     * most probably it works now - ignoring this "minor" error
     */
  }
  /* This socket is only to keep Curl_resolv_fdset() and select() happy;
   * should never become signalled for read/write since it's unbound but
   * Windows needs atleast 1 socket in select().
   */
  td->dummy_sock = socket(AF_INET, SOCK_DGRAM, 0);
  return TRUE;
}