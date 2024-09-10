int main(int argc, char * argv[])
{
   int err;
   DHCPContext ctx;
   unsigned char * alp, * ale;
   unsigned char dhcpOpts[] = {TAG_SLP_SCOPE, TAG_SLP_DA};

#ifdef _WIN32
   {
      WSADATA wsaData;
      if ((err = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0)
         return FAIL;
   }
#endif

   *ctx.scopelist = 0;
   ctx.scopelistlen = 0;
   ctx.addrlistlen = 0;

   if ((err = DHCPGetOptionInfo(dhcpOpts, sizeof(dhcpOpts), 
         DHCPParseSLPTags, &ctx)) != 0)
      return FAIL;

   printf("ScopeList: [%.*s]\n", ctx.scopelistlen, ctx.scopelist);
   printf("AddrList: [");

   alp = ctx.addrlist;
   ale = ctx.addrlist + ctx.addrlistlen;
   while(alp + 3 <= ale)
   {
      printf("%u.%u.%u.%u", alp[0], alp[1], alp[2], alp[3]);
      alp += 4;
      if (alp + 3 <= ale)
         printf(", ");
   }
   printf("]\n");

#ifdef _WIN32
   WSACleanup();
#endif

   return PASS;
}