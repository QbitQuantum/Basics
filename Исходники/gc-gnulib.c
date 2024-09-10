static Gc_rc
randomize (int level, char *data, size_t datalen)
{
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
  if (!g_hProv)
    return GC_RANDOM_ERROR;
  CryptGenRandom (g_hProv, (DWORD) datalen, data);
#else
  int fd;
  const char *device;
  size_t len = 0;
  int rc;

  switch (level)
    {
    case 0:
      device = NAME_OF_NONCE_DEVICE;
      break;

    case 1:
      device = NAME_OF_PSEUDO_RANDOM_DEVICE;
      break;

    default:
      device = NAME_OF_RANDOM_DEVICE;
      break;
    }

  if (strcmp (device, "no") == 0)
    return GC_RANDOM_ERROR;

  fd = open (device, O_RDONLY);
  if (fd < 0)
    return GC_RANDOM_ERROR;

  do
    {
      ssize_t tmp;

      tmp = read (fd, data, datalen);

      if (tmp < 0)
        {
          int save_errno = errno;
          close (fd);
          errno = save_errno;
          return GC_RANDOM_ERROR;
        }

      len += tmp;
    }
  while (len < datalen);

  rc = close (fd);
  if (rc < 0)
    return GC_RANDOM_ERROR;
#endif

  return GC_OK;
}