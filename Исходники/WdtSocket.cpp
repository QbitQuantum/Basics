int WdtSocket::getSendBufferSize() const {
  int size;
  socklen_t sizeSize = sizeof(size);
  getsockopt(fd_, SOL_SOCKET, SO_SNDBUF, (void *)&size, &sizeSize);
  return size;
}