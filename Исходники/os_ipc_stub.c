static ssize_t recv_buffer(int fd, int fds[3])
{
  struct iovec iov = { .iov_base = buffer, .iov_len = sizeof(buffer) };
  struct msghdr msg = {
    .msg_iov = &iov, .msg_iovlen = 1,
    .msg_controllen = CMSG_SPACE(3 * sizeof(int)),
  };
  msg.msg_control = alloca(msg.msg_controllen);
  memset(msg.msg_control, 0, msg.msg_controllen);

  ssize_t recvd;
  NO_EINTR(recvd, recvmsg(fd, &msg, 0));
  if (recvd == -1)
  {
    perror("recvmsg");
    return -1;
  }

  if (recvd < 4)
  {
    ssize_t recvd_;
    do {
      NO_EINTR(recvd_, recv(fd, buffer + recvd, sizeof(buffer) - recvd, 0));
      if (recvd_ > 0)
        recvd += recvd_;
    } while (recvd_ > 0 && recvd < 4);
  }

  size_t target = -1;

  if (recvd > 4)
  {
    target =
      unbyte(buffer[0],0) | unbyte(buffer[1],1) |
      unbyte(buffer[2],2) | unbyte(buffer[3],3);

    if (recvd < target)
    {
      ssize_t recvd_;
      do {
        NO_EINTR(recvd_, recv(fd, buffer + recvd, sizeof(buffer) - recvd, 0));
        if (recvd_ > 0)
          recvd += recvd_;
      } while (recvd_ > 0 && recvd < target);
    }
  }

  struct cmsghdr *cm = CMSG_FIRSTHDR(&msg);

  int *fds0 = (int*)CMSG_DATA(cm);
  int nfds = (cm->cmsg_len - CMSG_LEN(0)) / sizeof(int);

  /* Check malformed packet */
  if (nfds != 3 || recvd != target || buffer[recvd-1] != '\0')
  {
    int i;
    for (i = 0; i < nfds; ++i)
      close(fds0[i]);
    return -1;
  }

  fds[0] = fds0[0];
  fds[1] = fds0[1];
  fds[2] = fds0[2];

  return recvd;
}

value ml_merlin_server_setup(value path, value strfd)
{
  CAMLparam2(path, strfd);
  CAMLlocal2(payload, ret);
  char *endptr = NULL;

  int fd = strtol(String_val(strfd), &endptr, 0);
  if (endptr && *endptr == '\0')
  {
    /* (path, fd) */
    payload = caml_alloc(2, 0);
    Store_field(payload, 0, path);
    Store_field(payload, 1, Val_int(fd));

    /* Some payload */
    ret = caml_alloc(1, 0);
    Store_field(ret, 0, payload);
  }
  else
  {
    fprintf(stderr, "ml_merlin_server_setup(\"%s\",\"%s\"): invalid argument\n",
        String_val(path), String_val(strfd));
    unlink(String_val(path));
    /* None */
    ret = Val_unit;
  }

  CAMLreturn(ret);
}

value ml_merlin_server_accept(value server, value val_timeout)
{
  CAMLparam2(server, val_timeout);
  CAMLlocal4(ret, client, args, context);

  // Compute timeout
  double timeout = Double_val(val_timeout);
  struct timeval tv;
  tv.tv_sec = timeout;
  tv.tv_usec = (timeout - tv.tv_sec) * 1000000;

  // Select on server
  int serverfd = Int_val(Field(server, 1));
  int selectres;
  fd_set readset;
  do {
    FD_ZERO(&readset);
    FD_SET(serverfd, &readset);
    selectres = select(serverfd + 1, &readset, NULL, NULL, &tv);
  } while (selectres == -1 && errno == EINTR);

  int fds[3], clientfd;
  ssize_t len = -1;

  if (selectres > 0)
  {
    NO_EINTR(clientfd, accept(serverfd, NULL, NULL));
    len = recv_buffer(clientfd, fds);
  }

  if (len == -1)
    ret = Val_unit; /* None */
  else {
    context = caml_alloc(4, 0); /* (clientfd, stdin, stdout, stderr) */
    Store_field(context, 0, Val_int(clientfd));
    Store_field(context, 1, Val_int(fds[0]));
    Store_field(context, 2, Val_int(fds[1]));
    Store_field(context, 3, Val_int(fds[2]));

    ssize_t i, j;
    int argc = 0;
    for (i = 4; i < len; ++i)
      if (buffer[i] == '\0')
        argc += 1;

    args = caml_alloc(argc, 0);

    argc = 0;
    for (i = 4, j = 4; i < len; ++i)
    {
      if (buffer[i] == '\0')
      {
        Store_field(args, argc, caml_copy_string((const char *)&buffer[j]));
        j = i + 1;
        argc += 1;
      }
    }

    client = caml_alloc(2, 0); /* (context, args) */
    Store_field(client, 0, context);
    Store_field(client, 1, args);

    ret = caml_alloc(1, 0); /* Some client */
    Store_field(ret, 0, client);
  }

  CAMLreturn(ret);
}