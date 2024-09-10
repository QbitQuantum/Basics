 const char *inet_ntop(int af, const void *src, char *dst, socklen_t size) {
   union { struct sockaddr sa; struct sockaddr_in sai;
           struct sockaddr_in6 sai6; } addr;
   int res;
   memset(&addr, 0, sizeof(addr));
   addr.sa.sa_family = af;
   if (af == AF_INET6) {
     memcpy(&addr.sai6.sin6_addr, src, sizeof(addr.sai6.sin6_addr));
   } else {
     memcpy(&addr.sai.sin_addr, src, sizeof(addr.sai.sin_addr));
   }
   res = WSAAddressToStringA(&addr.sa, sizeof(addr), 0, dst, (LPDWORD) &size);
   if (res != 0) return NULL;
   return dst;
 }