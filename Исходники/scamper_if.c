int scamper_if_getmac(const int ifindex, uint8_t *mac)
{
  scamper_fd_t *fd = NULL;
  struct ifreq ifr;

  if(if_indextoname(ifindex, ifr.ifr_name) == NULL)
    {
      printerror(errno, strerror, __func__, "could not if_indextoname");
      goto err;
    }

  if((fd = scamper_fd_ifsock()) == NULL)
    {
      printerror(errno, strerror, __func__, "could not get ifsock");
      goto err;
    }

  if(ioctl(scamper_fd_fd_get(fd), SIOCGIFHWADDR, &ifr) == -1)
    {
      printerror(errno, strerror, __func__, "could not SIOCGIFHWADDR");
      goto err;
    }
  memcpy(mac, ifr.ifr_hwaddr.sa_data, 6);

  scamper_fd_free(fd);
  return 0;

 err:
  if(fd != NULL) scamper_fd_free(fd);
  return -1;
}