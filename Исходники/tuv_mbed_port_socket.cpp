ssize_t mbed_socket::dowrite(const void* buf, size_t count) {
  TCPStream* stream = get_stream();
  socket_error_t err;

  if ((sock_flag_ & MBED_SOCKET_FLAG_CONNECTED) == 0) {
    TDLOG(".. dowrite, socket not connected");
    set_errno(ENOTCONN);
    return -1;
  }

  sock_flag_ &= ~MBED_SOCKET_FLAG_WRITABLE;

  err = stream->send(buf, count);
  if (stream->error_check(err)) {
    TDLOG(".. socket send error: %s (%d)", socket_strerror(err), err);
    set_errno(EINVAL);
    // TODO: need to check this... how?
    sock_flag_ |= MBED_SOCKET_FLAG_WRITABLE;
    return -1;
  }

  return count;
}