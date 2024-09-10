int scamper_debug_open(const char *file)
{
  mode_t mode;
  int flags, fd;

#if defined(WITHOUT_PRIVSEP) && !defined(_WIN32)
  uid_t uid = getuid();
#endif

#ifndef _WIN32
  mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
#else
  mode = _S_IREAD | _S_IWRITE;
#endif

  if(scamper_option_debugfileappend() == 0)
    flags = O_WRONLY | O_CREAT | O_TRUNC;
  else
    flags = O_WRONLY | O_CREAT | O_APPEND;

#ifndef WITHOUT_PRIVSEP
  fd = scamper_privsep_open_file(file, flags, mode);
#else
  fd = open(file, flags, mode);
#endif

  if(fd == -1)
    {
      printerror(errno, strerror, __func__,
		 "could not open debugfile %s", file);
      return -1;
    }

  if((debugfile = fdopen(fd, "a")) == NULL)
    {
      printerror(errno, strerror, __func__,
		 "could not fdopen debugfile %s", file);
      return -1;
    }

#if defined(WITHOUT_PRIVSEP) && !defined(_WIN32)
  if(uid != geteuid() && fchown(fd, uid, -1) != 0)
    {
      printerror(errno, strerror, __func__, "could not fchown");
    }
#endif

  return 0;
}