int getsockname(int sockfd, FAR struct sockaddr *addr, FAR socklen_t *addrlen)
{
  FAR struct socket *psock = sockfd_socket(sockfd);
  int ret;
  int errcode;

  /* Verify that the sockfd corresponds to valid, allocated socket */

  if (!psock || psock->s_crefs <= 0)
    {
      errcode = EBADF;
      goto errout;
    }

  /* Some sanity checking... Shouldn't need this on a buckled up embedded
   * system (?)
   */

#ifdef CONFIG_DEBUG_FEATURES
  if (!addr || !addrlen)
    {
      errcode = EINVAL;
      goto errout;
    }
#endif

  /* Handle by address domain */

  switch (psock->s_domain)
    {
#ifdef CONFIG_NET_IPv4
    case PF_INET:
      ret = ipv4_getsockname(psock, addr, addrlen);
      break;
#endif

#ifdef CONFIG_NET_IPv6
    case PF_INET6:
      ret = ipv6_getsockname(psock, addr, addrlen);
      break;
#endif

    case PF_PACKET:
    default:
      errcode = EAFNOSUPPORT;
      goto errout;
    }

  /* Check for failure */

  if (ret < 0)
    {
      errcode = -ret;
      goto errout;
    }

  return OK;

errout:
  set_errno(errcode);
  return ERROR;
}