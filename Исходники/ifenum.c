static DWORD getInterfaceMtuByName(const char *name, PDWORD mtu)
{
  DWORD ret;
  int fd;

  if (!name)
    return ERROR_INVALID_PARAMETER;
  if (!mtu)
    return ERROR_INVALID_PARAMETER;

  fd = socket(PF_INET, SOCK_DGRAM, 0);
  if (fd != -1) {
    struct ifreq ifr;

    lstrcpynA(ifr.ifr_name, name, IFNAMSIZ);
    if ((ioctl(fd, SIOCGIFMTU, &ifr)))
      ret = ERROR_INVALID_DATA;
    else {
#ifndef __sun
      *mtu = ifr.ifr_mtu;
#else
      *mtu = ifr.ifr_metric;
#endif
      ret = NO_ERROR;
    }
    close(fd);
  }
  else
    ret = ERROR_NO_MORE_FILES;
  return ret;
}