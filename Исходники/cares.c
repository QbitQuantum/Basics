/* callback from ares when socket operation is started */
static void uv_ares_sockstate_cb(void *data, ares_socket_t sock, int read,
    int write) {
  /* look to see if we have a handle for this socket in our list */
  uv_loop_t* loop = (uv_loop_t*) data;
  uv_ares_task_t* uv_handle_ares = uv_find_ares_handle(loop, sock);

  int timeoutms = 0;

  if (read == 0 && write == 0) {
    /* if read and write are 0, cleanup existing data */
    /* The code assumes that c-ares does a callback with read = 0 and */
    /* write = 0 when the socket is closed. After we recieve this we stop */
    /* monitoring the socket. */
    if (uv_handle_ares != NULL) {
      uv_req_t* uv_ares_req;

      uv_handle_ares->h_close_event = CreateEvent(NULL, FALSE, FALSE, NULL);
      /* remove Wait */
      if (uv_handle_ares->h_wait) {
        UnregisterWaitEx(uv_handle_ares->h_wait,
                         uv_handle_ares->h_close_event);
        uv_handle_ares->h_wait = NULL;
      }

      /* detach socket from the event */
      WSAEventSelect(sock, NULL, 0);
      if (uv_handle_ares->h_event != WSA_INVALID_EVENT) {
        WSACloseEvent(uv_handle_ares->h_event);
        uv_handle_ares->h_event = WSA_INVALID_EVENT;
      }
      /* remove handle from list */
      uv_remove_ares_handle(uv_handle_ares);

      /* Post request to cleanup the Task */
      uv_ares_req = &uv_handle_ares->ares_req;
      uv_req_init(loop, uv_ares_req);
      uv_ares_req->type = UV_ARES_CLEANUP_REQ;
      uv_ares_req->data = uv_handle_ares;

      /* post ares done with socket - finish cleanup when all threads done. */
      POST_COMPLETION_FOR_REQ(loop, uv_ares_req);
    } else {
      assert(0);
      uv_fatal_error(ERROR_INVALID_DATA, "ares_SockStateCB");
    }
  } else {
    if (uv_handle_ares == NULL) {
      /* setup new handle */
      /* The code assumes that c-ares will call us when it has an open socket.
        We need to call into c-ares when there is something to read,
        or when it becomes writable. */
      uv_handle_ares = (uv_ares_task_t*)malloc(sizeof(uv_ares_task_t));
      if (uv_handle_ares == NULL) {
        uv_fatal_error(ERROR_OUTOFMEMORY, "malloc");
      }
      uv_handle_ares->type = UV_ARES_TASK;
      uv_handle_ares->close_cb = NULL;
      uv_handle_ares->data = loop;
      uv_handle_ares->sock = sock;
      uv_handle_ares->h_wait = NULL;
      uv_handle_ares->flags = 0;

      /* create an event to wait on socket signal */
      uv_handle_ares->h_event = WSACreateEvent();
      if (uv_handle_ares->h_event == WSA_INVALID_EVENT) {
        uv_fatal_error(WSAGetLastError(), "WSACreateEvent");
      }

      /* tie event to socket */
      if (SOCKET_ERROR == WSAEventSelect(sock,
                                         uv_handle_ares->h_event,
                                         FD_READ | FD_WRITE | FD_CONNECT)) {
        uv_fatal_error(WSAGetLastError(), "WSAEventSelect");
      }

      /* add handle to list */
      uv_add_ares_handle(loop, uv_handle_ares);
      uv_ref(loop);

      /*
       * we have a single polling timer for all ares sockets.
       * This is preferred to using ares_timeout. See ares_timeout.c warning.
       * if timer is not running start it, and keep socket count
       */
      if (loop->ares_active_sockets == 0) {
        uv_timer_init(loop, &loop->ares_polling_timer);
        uv_timer_start(&loop->ares_polling_timer, uv_ares_poll, 1000L, 1000L);
      }
      loop->ares_active_sockets++;

      /* specify thread pool function to call when event is signaled */
      if (RegisterWaitForSingleObject(&uv_handle_ares->h_wait,
                                  uv_handle_ares->h_event,
                                  uv_ares_socksignal_tp,
                                  (void*)uv_handle_ares,
                                  INFINITE,
                                  WT_EXECUTEINWAITTHREAD) == 0) {
        uv_fatal_error(GetLastError(), "RegisterWaitForSingleObject");
      }
    } else {
      /* found existing handle.  */
      assert(uv_handle_ares->type == UV_ARES_TASK);
      assert(uv_handle_ares->data != NULL);
      assert(uv_handle_ares->h_event != WSA_INVALID_EVENT);
    }
  }
}