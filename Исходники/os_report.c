static FILE * open_socket (char *host, unsigned short port)
{
   FILE * file = NULL;
   struct sockaddr_in sa;
   os_socket sock;
   char* errorMessage;

   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   {
      errorMessage = os_reportErrnoToString(socketErrorNo());
      fprintf(stderr, "socket: %s\n", errorMessage);
      os_free(errorMessage);
      return NULL;
   }

   memset((char *)&sa, 0, sizeof(sa));
   sa.sin_family = AF_INET;
   sa.sin_port = htons(port);
   sa.sin_addr.s_addr = inet_addr (host);

   if (connect (sock, (struct sockaddr *)&sa, sizeof(sa)) < 0)
   {
      errorMessage = os_reportErrnoToString(socketErrorNo());
      fprintf(stderr, "connect: %s\n", errorMessage);
      os_free(errorMessage);
      return NULL;
   }
#ifdef WINCE
   file = _wfdopen ((int)sock, L"w");
#else
   file = fdopen ((int)sock, "w");
#endif

   return file;
}