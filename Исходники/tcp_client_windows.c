/* Tries to issue one async connection, then schedules both an IOCP
   notification request for the connection, and one timeout alert. */
void grpc_tcp_client_connect(grpc_exec_ctx *exec_ctx, grpc_closure *on_done,
                             grpc_endpoint **endpoint,
                             grpc_pollset_set *interested_parties,
                             const struct sockaddr *addr, size_t addr_len,
                             gpr_timespec deadline) {
  SOCKET sock = INVALID_SOCKET;
  BOOL success;
  int status;
  struct sockaddr_in6 addr6_v4mapped;
  struct sockaddr_in6 local_address;
  async_connect *ac;
  grpc_winsocket *socket = NULL;
  LPFN_CONNECTEX ConnectEx;
  GUID guid = WSAID_CONNECTEX;
  DWORD ioctl_num_bytes;
  const char *message = NULL;
  char *utf8_message;
  grpc_winsocket_callback_info *info;

  *endpoint = NULL;

  /* Use dualstack sockets where available. */
  if (grpc_sockaddr_to_v4mapped(addr, &addr6_v4mapped)) {
    addr = (const struct sockaddr *)&addr6_v4mapped;
    addr_len = sizeof(addr6_v4mapped);
  }

  sock = WSASocket(AF_INET6, SOCK_STREAM, IPPROTO_TCP, NULL, 0,
                   WSA_FLAG_OVERLAPPED);
  if (sock == INVALID_SOCKET) {
    message = "Unable to create socket: %s";
    goto failure;
  }

  if (!grpc_tcp_prepare_socket(sock)) {
    message = "Unable to set socket options: %s";
    goto failure;
  }

  /* Grab the function pointer for ConnectEx for that specific socket.
     It may change depending on the interface. */
  status =
      WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guid, sizeof(guid),
               &ConnectEx, sizeof(ConnectEx), &ioctl_num_bytes, NULL, NULL);

  if (status != 0) {
    message = "Unable to retrieve ConnectEx pointer: %s";
    goto failure;
  }

  grpc_sockaddr_make_wildcard6(0, &local_address);

  status = bind(sock, (struct sockaddr *)&local_address, sizeof(local_address));
  if (status != 0) {
    message = "Unable to bind socket: %s";
    goto failure;
  }

  socket = grpc_winsocket_create(sock, "client");
  info = &socket->write_info;
  success =
      ConnectEx(sock, addr, (int)addr_len, NULL, 0, NULL, &info->overlapped);

  /* It wouldn't be unusual to get a success immediately. But we'll still get
     an IOCP notification, so let's ignore it. */
  if (!success) {
    int error = WSAGetLastError();
    if (error != ERROR_IO_PENDING) {
      message = "ConnectEx failed: %s";
      goto failure;
    }
  }

  ac = gpr_malloc(sizeof(async_connect));
  ac->on_done = on_done;
  ac->socket = socket;
  gpr_mu_init(&ac->mu);
  ac->refs = 2;
  ac->addr_name = grpc_sockaddr_to_uri(addr);
  ac->endpoint = endpoint;
  grpc_closure_init(&ac->on_connect, on_connect, ac);

  grpc_timer_init(exec_ctx, &ac->alarm, deadline, on_alarm, ac,
                  gpr_now(GPR_CLOCK_MONOTONIC));
  grpc_socket_notify_on_write(exec_ctx, socket, &ac->on_connect);
  return;

failure:
  utf8_message = gpr_format_message(WSAGetLastError());
  gpr_log(GPR_ERROR, message, utf8_message);
  gpr_free(utf8_message);
  if (socket != NULL) {
    grpc_winsocket_destroy(socket);
  } else if (sock != INVALID_SOCKET) {
    closesocket(sock);
  }
  grpc_exec_ctx_enqueue(exec_ctx, on_done, false, NULL);
}