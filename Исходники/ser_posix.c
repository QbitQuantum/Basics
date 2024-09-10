static int ser_recv(union filedescriptor *fd, unsigned char * buf, size_t buflen)
{
  struct timeval timeout, to2;
  fd_set rfds;
  int nfds;
  int rc;
  unsigned char * p = buf;
  size_t len = 0;

  timeout.tv_sec  = serial_recv_timeout / 1000L;
  timeout.tv_usec = (serial_recv_timeout % 1000L) * 1000;
  to2 = timeout;

  while (len < buflen) {
  reselect:
    FD_ZERO(&rfds);
    FD_SET(fd->ifd, &rfds);

    nfds = select(fd->ifd + 1, &rfds, NULL, NULL, &to2);
    if (nfds == 0) {
      if (verbose > 1)
	fprintf(stderr,
		"%s: ser_recv(): programmer is not responding\n",
		progname);
      return -1;
    }
    else if (nfds == -1) {
      if (errno == EINTR || errno == EAGAIN) {
	fprintf(stderr,
		"%s: ser_recv(): programmer is not responding,reselecting\n",
		progname);
        goto reselect;
      }
      else {
        fprintf(stderr, "%s: ser_recv(): select(): %s\n",
                progname, strerror(errno));
        exit(1);
      }
    }

    rc = read(fd->ifd, p, (buflen - len > 1024) ? 1024 : buflen - len);
    if (rc < 0) {
      fprintf(stderr, "%s: ser_recv(): read error: %s\n",
              progname, strerror(errno));
      exit(1);
    }
    p += rc;
    len += rc;
  }

  p = buf;

  if (verbose > 3)
  {
      fprintf(stderr, "%s: Recv: ", progname);

      while (len) {
        unsigned char c = *p;
        if (isprint(c)) {
          fprintf(stderr, "%c ", c);
        }
        else {
          fprintf(stderr, ". ");
        }
        fprintf(stderr, "[%02x] ", c);

        p++;
        len--;
      }
      fprintf(stderr, "\n");
  }

  return 0;
}