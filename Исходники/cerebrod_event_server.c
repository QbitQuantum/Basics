/*
 * _event_server_service_connection
 *
 * Service a connection from a client to receive event packets.  Use
 * wrapper functions minimally, b/c we want to return errors to the
 * user instead of exitting with errors.
 *
 */
static void
_event_server_service_connection(int fd)
{
  int recv_len;
  struct cerebro_event_server_request req;
  struct cerebrod_event_connection_data *ecd = NULL;
  char buf[CEREBRO_MAX_PACKET_LEN];
  char event_name_buf[CEREBRO_MAX_EVENT_NAME_LEN+1];
  char *event_name_ptr = NULL;
  int32_t version;
  int *fdptr = NULL;
  List connections = NULL;

  assert(fd >= 0);

  memset(&req, '\0', sizeof(struct cerebro_event_server_request));
  if ((recv_len = receive_data(fd,
                               CEREBRO_EVENT_SERVER_REQUEST_PACKET_LEN,
                               buf,
                               CEREBRO_MAX_PACKET_LEN,
                               CEREBRO_EVENT_SERVER_PROTOCOL_CLIENT_TIMEOUT_LEN,
                               NULL)) < 0)
    goto cleanup;

  if (recv_len < sizeof(version))
    goto cleanup;

  if (_event_server_request_check_version(buf, recv_len, &version) < 0)
    {
      _event_server_err_only_response(fd,
                                      version,
                                      CEREBRO_EVENT_SERVER_PROTOCOL_ERR_VERSION_INVALID);
      goto cleanup;
    }

  if (recv_len != CEREBRO_EVENT_SERVER_REQUEST_PACKET_LEN)
    {
      _event_server_err_only_response(fd,
                                      version,
                                      CEREBRO_EVENT_SERVER_PROTOCOL_ERR_PACKET_INVALID);
      goto cleanup;
    }

  if (_event_server_request_unmarshall(&req, buf, recv_len) < 0)
    {
      _event_server_err_only_response(fd,
                                      version,
                                      CEREBRO_EVENT_SERVER_PROTOCOL_ERR_PACKET_INVALID);
      goto cleanup;
    }

  _event_server_request_dump(&req);

  /* Guarantee ending '\0' character */
  memset(event_name_buf, '\0', CEREBRO_MAX_EVENT_NAME_LEN+1);
  memcpy(event_name_buf, req.event_name, CEREBRO_MAX_EVENT_NAME_LEN);

  if (!strlen(event_name_buf))
    {
      _event_server_err_only_response(fd,
                                      req.version,
                                      CEREBRO_EVENT_SERVER_PROTOCOL_ERR_EVENT_INVALID);
      goto cleanup;
    }

  /* Is it the special event-names request */
  if (!strcmp(event_name_buf, CEREBRO_EVENT_NAMES))
    {
      pthread_t thread;
      pthread_attr_t attr;
      int *arg;

      Pthread_attr_init(&attr);
      Pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
      Pthread_attr_setstacksize(&attr, CEREBROD_THREAD_STACKSIZE);
      arg = Malloc(sizeof(int));
      *arg = fd;
      Pthread_create(&thread,
                     &attr,
                     _respond_with_event_names,
                     (void *)arg);
      Pthread_attr_destroy(&attr);
      return;
    }

  if (!event_names)
    {
      _event_server_err_only_response(fd,
                                      req.version,
                                      CEREBRO_EVENT_SERVER_PROTOCOL_ERR_EVENT_INVALID);
      goto cleanup;
    }

  /* Event names is not changeable - so no need for a lock */
  if (!(event_name_ptr = list_find_first(event_names, 
                                         _event_names_compare,
                                         event_name_buf)))
    {
      _event_server_err_only_response(fd,
                                      req.version,
                                      CEREBRO_EVENT_SERVER_PROTOCOL_ERR_EVENT_INVALID);
      goto cleanup;
    }
  
  if (!(ecd = (struct cerebrod_event_connection_data *)malloc(sizeof(struct cerebrod_event_connection_data))))
    {
      CEREBRO_ERR(("malloc: %s", strerror(errno)));
      _event_server_err_only_response(fd,
                                      req.version,
                                      CEREBRO_EVENT_SERVER_PROTOCOL_ERR_INTERNAL_ERROR);
      goto cleanup;
    }
  
  ecd->event_name = event_name_ptr;
  ecd->fd = fd;
  
  if (!(fdptr = (int *)malloc(sizeof(int))))
    {
      CEREBRO_ERR(("malloc: %s", strerror(errno)));
      _event_server_err_only_response(fd,
                                      req.version,
                                      CEREBRO_EVENT_SERVER_PROTOCOL_ERR_INTERNAL_ERROR);
      goto cleanup;
    }
  *fdptr = fd;

  Pthread_mutex_lock(&event_connections_lock);
  if (!list_append(event_connections, ecd))
    {
      CEREBRO_ERR(("list_append: %s", strerror(errno)));
      _event_server_err_only_response(fd,
                                      req.version,
                                      CEREBRO_EVENT_SERVER_PROTOCOL_ERR_INTERNAL_ERROR);
      goto cleanup;
    }

  if (!(connections = Hash_find(event_connections_index, 
                                ecd->event_name)))
    {
      if (!(connections = list_create((ListDelF)free)))
        {
          CEREBRO_ERR(("list_create: %s", strerror(errno)));
          _event_server_err_only_response(fd,
                                          req.version,
                                          CEREBRO_EVENT_SERVER_PROTOCOL_ERR_INTERNAL_ERROR);
          goto cleanup;
        }

      if (!Hash_insert(event_connections_index, ecd->event_name, connections))
        {
          CEREBRO_ERR(("Hash_insert: %s", strerror(errno)));
          _event_server_err_only_response(fd,
                                          req.version,
                                          CEREBRO_EVENT_SERVER_PROTOCOL_ERR_INTERNAL_ERROR);
          list_destroy(connections);
          goto cleanup;
        }
    }

  if (!list_append(connections, fdptr))
    {
      CEREBRO_ERR(("list_append: %s", strerror(errno)));
      _event_server_err_only_response(fd,
                                      req.version,
                                      CEREBRO_EVENT_SERVER_PROTOCOL_ERR_INTERNAL_ERROR);
      goto cleanup;
    }

  Pthread_mutex_unlock(&event_connections_lock);
  /* Clear this pointer so we know it's stored away in a list */
  fdptr = NULL;

  _event_server_err_only_response(fd,
                                  req.version,
                                  CEREBRO_EVENT_SERVER_PROTOCOL_ERR_SUCCESS);

  return;
  
 cleanup:
  if (ecd)
    free(ecd);
  if (fdptr)
    free(fdptr);
  /* ignore potential error, we're in the error path already */
  close(fd);
  return;
}