/* event manager callback when reads are ready */
static void on_accept(void *arg, int success) {
  server_port *sp = arg;
  SOCKET sock = sp->new_socket;
  grpc_winsocket_callback_info *info = &sp->socket->read_info;
  grpc_endpoint *ep = NULL;

  if (success) {
    DWORD transfered_bytes = 0;
    DWORD flags;
    BOOL wsa_success = WSAGetOverlappedResult(sock, &info->overlapped,
                                              &transfered_bytes, FALSE,
                                              &flags);
    if (!wsa_success) {
      char *utf8_message = gpr_format_message(WSAGetLastError());
      gpr_log(GPR_ERROR, "on_accept error: %s", utf8_message);
      gpr_free(utf8_message);
      closesocket(sock);
    } else {
      gpr_log(GPR_DEBUG, "on_accept: accepted connection");
      ep = grpc_tcp_create(grpc_winsocket_create(sock));
    }
  } else {
    gpr_log(GPR_DEBUG, "on_accept: shutting down");
    closesocket(sock);
    gpr_mu_lock(&sp->server->mu);
    if (0 == --sp->server->active_ports) {
      gpr_cv_broadcast(&sp->server->cv);
    }
    gpr_mu_unlock(&sp->server->mu);
  }

  if (ep) sp->server->cb(sp->server->cb_arg, ep);
  start_accept(sp);
}