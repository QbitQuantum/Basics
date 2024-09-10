int main(int argc, char* argv[])
{
   int sock;
   int status;
   struct addrinfo sainfo, *psinfo;
   struct sockaddr_in6 sin6;
   int sin6len;
   char buffer[MAXBUF];
   uint32_t if_index = 0;

   sin6len = sizeof(struct sockaddr_in6);

   sock = socket(PF_INET6, SOCK_DGRAM,0);

   memset(&sin6, 0, sizeof(struct sockaddr_in6));
   sin6.sin6_port = htons(4936);
   sin6.sin6_family = AF_INET6;
   sin6.sin6_addr = in6addr_any;

   status = bind(sock, (struct sockaddr *)&sin6, sin6len);

   if(-1 == status)
     perror("bind"), exit(1);

   memset(&sainfo, 0, sizeof(struct addrinfo));
   memset(&sin6, 0, sin6len);

   sainfo.ai_flags = 0;
   sainfo.ai_family = PF_INET6;
   sainfo.ai_socktype = SOCK_DGRAM;
   sainfo.ai_protocol = IPPROTO_UDP;
   status = getaddrinfo("ff02::150",
                        "4936", &sainfo, &psinfo);

   switch (status) 
     {
      case EAI_FAMILY: printf("family\n");
        break;
      case EAI_SOCKTYPE: printf("stype\n");
        break;
      case EAI_BADFLAGS: printf("flag\n");
        break;
      case EAI_NONAME: printf("noname\n");
        break;
      case EAI_SERVICE: printf("service\n");
        break;
     }
   if_index = if_nametoindex("eth2");
   printf("\nIf_index %d", if_index);
   sprintf(buffer,"Hello World");

   setsockopt(sock, IPPROTO_IPV6, IPV6_MULTICAST_IF, 
              &if_index, sizeof(if_index));

   while (1) {
       status = sendto(sock, buffer, strlen(buffer), 0,
                         (struct sockaddr *)psinfo->ai_addr, sin6len);
       printf("buffer : %s \t%d\n", buffer, status);
       sleep(2);
   }

   // free memory
   freeaddrinfo(psinfo);
   psinfo = NULL;

   shutdown(sock, 2);
   close(sock);
   return 0;
}