u32 mip_sdk_port_read_count(void *port_handle)
{
  fd_set rdfs;
  struct timeval timeout;

  if(port_handle == NULL)
  {
    printf("mip_sdk_read_count error: handle is null\n");
    return MIP_USER_FUNCTION_ERROR;
  }

  struct serial_fd* fd = (struct serial_fd*)port_handle;

  if (fd->state == STATE_WAITING_ON_FD)
  {
    openPort(fd);
  }
  else if (fd->size < MAX_BUFFER_SIZE)
  {
    FD_ZERO(&rdfs);
    FD_SET(fd->fd, &rdfs);

    timeout.tv_sec = 0;
    timeout.tv_usec = 10000;

    if (select(fd->fd+1, &rdfs, NULL, NULL, &timeout) > 0)
    {
      u32 i;

      //move the bytes down
      for (i = 0; i < fd->size && fd->position > 0; i++)
      {
        fd->pBuffer[i] = fd->pBuffer[fd->position + i];
      }
      fd->position = 0;

      size_t bytesRead = read(fd->fd, &fd->pBuffer[fd->size], MAX_BUFFER_SIZE - fd->size);

      if (bytesRead > 0)
      {
        fd->size += bytesRead;
        //printf("read_count: buffer size is %u\n", fd->size);
      }
      else
      {
        tempClosePort(fd);
      }
    }
  }

  return fd->size;
}