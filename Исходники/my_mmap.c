int my_msync(int fd, void *addr, size_t len, int flags)
{
  return FlushViewOfFile(addr, len) ? 0 : -1;
}