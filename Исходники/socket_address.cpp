   /*
   struct addrinfo {
      int ai_flags;              // Input flags
      int ai_family;             // Protocol family for socket
      int ai_socktype;           // Socket type
      int ai_protocol;           // Protocol for socket
      socklen_t ai_addrlen;      // Length of socket address
      struct sockaddr* ai_addr;  // Socket address for socket
      char* ai_canonname;        // Canonical name for service location
      struct addrinfo* ai_next;  // Pointer to next in list
   };
   */
   void set(struct addrinfo* result)
      {
      U_TRACE(0, "SocketAddress::set(%p)", result)

      addr.psaGeneric.sa_family = result->ai_family;

#  ifdef ENABLE_IPV6
      if (addr.psaGeneric.sa_family == AF_INET6)
         U_MEMCPY(&(addr.psaIP6Addr.sin6_addr),
                         &((struct sockaddr_in6*)result->ai_addr)->sin6_addr, sizeof(in6_addr));
      else
#  endif
         U_MEMCPY(&(addr.psaIP4Addr.sin_addr),
                         &((struct sockaddr_in*)result->ai_addr)->sin_addr,   sizeof(in_addr));
      }