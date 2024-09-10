  sockaddr* CopyAddress(int family, const void* data, size_t byteCount, sockaddr_storage* ss) {
      // Netlink gives us the address family in the header, and the
      // sockaddr_in or sockaddr_in6 bytes as the payload. We need to
      // stitch the two bits together into the sockaddr that's part of
      // our portable interface.
      ss->ss_family = family;
      memcpy(SockaddrBytes(family, ss), data, byteCount);

      // For IPv6 we might also have to set the scope id.
      if (family == AF_INET6 && (IN6_IS_ADDR_LINKLOCAL(data) || IN6_IS_ADDR_MC_LINKLOCAL(data))) {
          reinterpret_cast<sockaddr_in6*>(ss)->sin6_scope_id = interface_index;
      }

      return reinterpret_cast<sockaddr*>(ss);
  }