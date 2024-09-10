static int submit_write(write_result_t *result, const void *buf, size_t len)
{
  WSABUF wsabuf;
  wsabuf.buf = (char *) buf;
  wsabuf.len = len;
  memset(&result->base.overlapped, 0, sizeof (OVERLAPPED));
  return WSASend(result->base.iocpd->socket, &wsabuf, 1, NULL, 0,
                 (LPOVERLAPPED) result, 0);
}