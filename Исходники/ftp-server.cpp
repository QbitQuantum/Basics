void *
read_file (void *fd)
{
  ACE_TLI_Stream stream;
  char buf[BUFSIZ];
  int flags = 0;
  ssize_t n;

  // Cast the arg to a long, first, because a pointer is the same size
  // as a long on all current ACE platforms.
  stream.set_handle ((int) (long) fd);

  ACE_DEBUG((LM_DEBUG, "start (tid = %t, fd = %d)\n",
             stream.get_handle ()));

  while ((n = stream.recv (buf, sizeof buf, &flags)) > 0)
    continue;

  ACE_UNUSED_ARG (n);

  ACE_DEBUG ((LM_DEBUG,"finish (tid = %t, fd = %d)\n",
              stream.get_handle ()));

  if (stream.close () == -1)
    ACE_OS::t_error ("stream.close error");

  return 0;
}