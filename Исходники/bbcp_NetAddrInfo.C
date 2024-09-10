bool bbcp_NetAddrInfo::isPrivate()
{
   unsigned char *ipV4 = 0;

// For IPV6 addresses we will use the macro unless it is mapped
//
   if (IP.Addr.sa_family == AF_INET6)
      {if ((IN6_IS_ADDR_V4MAPPED(&IP.v6.sin6_addr)))
          ipV4 = (unsigned char *)&IP.v6.sin6_addr.s6_addr32[3];
          else  {if ((IN6_IS_ADDR_LINKLOCAL(&IP.v6.sin6_addr))
                 ||  (IN6_IS_ADDR_SITELOCAL(&IP.v6.sin6_addr))
                 ||  (IN6_IS_ADDR_LOOPBACK (&IP.v6.sin6_addr))) return true;
                 return false;
                }
      }

// If this is not an IPV4 address then we will consider it private
//
   if (!ipV4)
      {if (IP.Addr.sa_family != AF_INET) return true;
       ipV4 = (unsigned char *)&IP.v4.sin_addr.s_addr;
      }

// For IPV4 we use the RFC definition of private. Note that this includes
// mapped addresses which, as odd as it is, we could get.
//
   if (ipV4[0] ==  10
   || (ipV4[0] == 172 && ipV4[1] >=  16 && ipV4[1] <= 31)
   || (ipV4[0] == 192 && ipV4[1] == 168)
   || (ipV4[0] == 169 && ipV4[1] == 254)
   ||  ipV4[0] == 127) return true;

// Not a local address
//
   return false;
}