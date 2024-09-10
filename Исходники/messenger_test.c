int
mock_bind( int sockfd, const struct sockaddr *addr, socklen_t addrlen ) {
  return fail_mock_bind ? -1 : bind( sockfd, addr, addrlen );
}