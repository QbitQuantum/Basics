static ssize_t mailstream_low_socket_read(mailstream_low * s,
					  void * buf, size_t count)
{
  struct mailstream_socket_data * socket_data;
  
  socket_data = (struct mailstream_socket_data *) s->data;

  if (mailstream_cancel_cancelled(socket_data->cancel))
    return -1;
  
  /* timeout */
  {
    fd_set fds_read;
    struct timeval timeout;
    int r;
    int fd;
    int cancelled;
    int got_data;
#ifdef WIN32
    HANDLE event;
#else
    int max_fd;
#endif
    
    if (s->timeout == 0) {
      timeout = mailstream_network_delay;
    }
    else {
			timeout.tv_sec = s->timeout;
      timeout.tv_usec = 0;
    }
    
    FD_ZERO(&fds_read);
    fd = mailstream_cancel_get_fd(socket_data->cancel);
    FD_SET(fd, &fds_read);
    
#ifdef WIN32
    event = CreateEvent(NULL, TRUE, FALSE, NULL);
    WSAEventSelect(socket_data->fd, event, FD_READ | FD_CLOSE);
    FD_SET(event, &fds_read);
    r = WaitForMultipleObjects(fds_read.fd_count, fds_read.fd_array, FALSE, timeout.tv_sec * 1000 + timeout.tv_usec / 1000);
    if (WAIT_TIMEOUT == r) {
			WSAEventSelect(socket_data->fd, event, 0);
			CloseHandle(event);
      return -1;
		}
    
    cancelled = (fds_read.fd_array[r - WAIT_OBJECT_0] == fd);
    got_data = (fds_read.fd_array[r - WAIT_OBJECT_0] == event);
		WSAEventSelect(socket_data->fd, event, 0);
		CloseHandle(event);
#else
    FD_SET(socket_data->fd, &fds_read);
    max_fd = socket_data->fd;
    if (fd > max_fd)
      max_fd = fd;
    r = select(max_fd + 1, &fds_read, NULL,/* &fds_excp*/ NULL, &timeout);
    if (r <= 0)
      return -1;
    
    cancelled = FD_ISSET(fd, &fds_read);
    got_data = FD_ISSET(socket_data->fd, &fds_read);
#endif
    
    if (cancelled) {
      /* cancelled */
      mailstream_cancel_ack(socket_data->cancel);
      return -1;
    }
    
    if (!got_data)
      return 0;
  }
  
  if (socket_data->use_read) {
    return read(socket_data->fd, buf, count);
  }
  else {
    return recv(socket_data->fd, buf, count, 0);
  }
}