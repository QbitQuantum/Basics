static int wait_write(mailstream_low * s)
{
  fd_set fds_read;
  fd_set fds_write;
  struct timeval timeout;
  int r;
  int fd;
  struct mailstream_ssl_data * ssl_data;
  int max_fd;
  int cancelled;
  int write_enabled;
#ifdef WIN32
  HANDLE event;
#endif
  
  ssl_data = (struct mailstream_ssl_data *) s->data;
  if (mailstream_cancel_cancelled(ssl_data->cancel))
    return -1;
 
  if (s->timeout == 0) {
    timeout = mailstream_network_delay;
  }
  else {
		timeout.tv_sec = s->timeout;
    timeout.tv_usec = 0;
  }
  
  FD_ZERO(&fds_read);
  fd = mailstream_cancel_get_fd(ssl_data->cancel);
  FD_SET(fd, &fds_read);
  FD_ZERO(&fds_write);
#ifdef WIN32
  event = CreateEvent(NULL, TRUE, FALSE, NULL);
  WSAEventSelect(ssl_data->fd, event, FD_WRITE | FD_CLOSE);
  FD_SET(event, &fds_read);
  r = WaitForMultipleObjects(fds_read.fd_count, fds_read.fd_array, FALSE, timeout.tv_sec * 1000 + timeout.tv_usec / 1000);
  if (r < 0) {
		WSAEventSelect(ssl_data->fd, event, 0);
		CloseHandle(event);
    return -1;
	}
  
  cancelled = (fds_read.fd_array[r - WAIT_OBJECT_0] == fd) /* SEB 20070709 */;
  write_enabled = (fds_read.fd_array[r - WAIT_OBJECT_0] == event);
	WSAEventSelect(ssl_data->fd, event, 0);
	CloseHandle(event);
#else
  FD_SET(ssl_data->fd, &fds_write);
  
  max_fd = ssl_data->fd;
  if (fd > max_fd)
    max_fd = fd;
  
  r = select(max_fd + 1, &fds_read, &fds_write, NULL, &timeout);
  if (r <= 0)
    return -1;
  
  cancelled = FD_ISSET(fd, &fds_read);
  write_enabled = FD_ISSET(ssl_data->fd, &fds_write);
#endif
  
  if (cancelled) {
    /* cancelled */
    mailstream_cancel_ack(ssl_data->cancel);
    return -1;
  }
  
  if (!write_enabled)
    return 0;
  
  return 1;
}