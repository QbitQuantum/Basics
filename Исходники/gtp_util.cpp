IpAddr convIpStrToIpAddr(const S8* pIp, U32 len)
{
   LOG_ENTERFN();

   IpAddr ipAddr;
   S8     ip[GSIM_SIZE_32] = {'\0'};
   MEMCPY(ip, pIp, len);

   ipAddr.ipAddrType = IP_ADDR_TYPE_INV;
   if (STRFIND(ip, ":") != NULL)
   {
      RETVAL ret = inet_pton(AF_INET6, ip, (VOID *)(ipAddr.u.ipv6Addr.addr));
      if (0 == ret)
      {
         LOG_FATAL("Invalid IPv6 Address");
      }
      else
      {
         ipAddr.u.ipv6Addr.len = STRLEN(ip);
         ipAddr.ipAddrType = IP_ADDR_TYPE_V6;
      }
   }
   else
   {
      RETVAL ret = inet_pton(AF_INET, ip, (VOID *)&(ipAddr.u.ipv4Addr.addr));
      if (0 == ret)
      {
         LOG_FATAL("Invalid IPv4 Address");
      }
      else
      {
         ipAddr.u.ipv4Addr.addr = ntohl(ipAddr.u.ipv4Addr.addr);
         ipAddr.ipAddrType = IP_ADDR_TYPE_V4;
      }
   }

   LOG_EXITFN(ipAddr);
}