CAMLprim value win_check_connection (value socket, value kind, value idx) {
  CAMLparam3 (socket, kind, idx);
  WSANETWORKEVENTS evs;
  int res, err, i = Long_val(idx);

  D(printf("Check connection... %d\n", i));
  if (WSAEnumNetworkEvents(Socket_val(socket), NULL, &evs)) {
    win32_maperr(WSAGetLastError ());
    uerror("WSAEnumNetworkEvents", Nothing);
  }
  if (WSAEventSelect(Socket_val(socket), NULL, 0) == SOCKET_ERROR) {
    win32_maperr(WSAGetLastError ());
    uerror("WSAEventSelect", Nothing);
  }
  if (!CloseHandle(events[i])) {
    win32_maperr(GetLastError ());
    uerror("CloseHandle", Nothing);
  }
  err =
    evs.iErrorCode[(Long_val(kind) == 0) ? FD_CONNECT_BIT : FD_ACCEPT_BIT];
  D(printf("Check connection: %ld, err %d\n", evs.lNetworkEvents, err));
  if (err != 0) {
    win32_maperr(err);
    uerror("check_connection", Nothing);
  }
  CAMLreturn (Val_unit);
}