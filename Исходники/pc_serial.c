/*----------------------------------------------------------------------------*/
int serial_read(int fd, void *buffer, unsigned size, unsigned timeout)
{
  HANDLE h;
  COMMTIMEOUTS ct;
  int received = 0;

  h = get_h(fd);
  if(!h)
    return 0;

  if(!GetCommTimeouts(h,&ct))
  {
    err_trace(__FILE__, __LINE__);
    return 0;
  }

  ct.ReadIntervalTimeout = MAXDWORD;
  ct.ReadTotalTimeoutMultiplier = MAXDWORD;
  ct.ReadTotalTimeoutConstant = timeout;

  if(!SetCommTimeouts(h,&ct))
  {
    err_trace(__FILE__, __LINE__);
    return 0;
  }

  if(!ReadFile(h, buffer, size, (DWORD *)&received, NULL))
  {
    DWORD Err;
    err_trace(__FILE__, __LINE__);
    ClearCommBreak(h);
    ClearCommError(h, &Err, NULL);
    return 0;
  }

#ifdef DEBUG
  if(!received)
  {
//    err_trace(__FILE__, __LINE__);
//    TRACE("%s:%d: Timeout reached. Timeout: %u\n", __FILE__, __LINE__, timeout );
  }
	else
	{
		int i;
		fprintf(stderr, "rx: ");
		for(i = 0; i < received; i++)
			fprintf(stderr, "%02x ", (unsigned)((char *)buffer)[i] & 0xff);
		fprintf(stderr, "\n");
	}
#endif

  return received;
}