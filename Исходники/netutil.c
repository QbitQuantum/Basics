static int add_multicast_group(SOCKET sock, const struct sockaddr *psa) {

#if defined(WIN32)

  LOG(X_ERROR("Multicast not implemented on this system type"));
  return -1;

#else

  if(psa->sa_family == AF_INET6) {
    LOG(X_ERROR("IPv6 multicast group addition not implemented"));
    return -1;
  }

  struct ip_mreq mcip;
  char tmp[128];

  memset(&mcip, 0, sizeof(mcip));

  mcip.imr_multiaddr.s_addr = ((const struct sockaddr_in *) psa)->sin_addr.s_addr;
  mcip.imr_interface.s_addr = INADDR_ANY;

  if(setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &mcip, 
     sizeof(mcip)) < 0) {

    LOG(X_ERROR("Unable to add multicast membership for %s"), INET_NTOP(*psa, tmp, sizeof(tmp)));
    return -1;
  }

  LOG(X_DEBUG("Subscribed to multicast membership for %s"), INET_NTOP(*psa, tmp, sizeof(tmp)));

  return 0;

#endif // WIN32

}