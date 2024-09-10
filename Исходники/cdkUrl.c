gboolean
CdkUrl_Parse(const char *url,      // IN
             char **proto,         // OUT
             char **host,          // OUT
             unsigned short *port, // OUT
             char **path,          // OUT
             gboolean *secure)     // IN/OUT
{
   char *myUrl = NULL;
   const char *start = NULL;
   const char *end = NULL;
   char *myProto = NULL;
   char *myHost = NULL;
   char *myPath = NULL;
   unsigned int myPort;

   g_assert(url);

   /*
    * If there are multibyte characters, we need to convert from IDN
    * to ASCII (punycode).
    */
   if (g_utf8_strlen(url, -1) != strlen(url)) {
      url = myUrl = IDNToASCII(url);
      if (!url) {
         return FALSE;
      }
   }

   start = url;

   end = strstr(start, "://");
   if (end) {
      myProto = g_strndup(start, end - start);
      start = end + 3;
   } else {
      /* Implicit protocol */
      myProto = g_strdup(secure && *secure ? "https" : "http");
   }

   end = strpbrk(start, ":/");
   if (!end) {
      end = start + strlen(start);
   }
   myHost = g_strndup(start, end - start);

   if (*end == ':') {
      /* Explicit port */
      start = end + 1;
      end = strchr(start, '/');
      if (!end) {
         end = start + strlen(start);
      }
      errno = 0;
      myPort = strtoul(start, NULL, 10);
      if (errno != 0 || myPort > 0xffff) {
         goto error;
      }
   } else {
      /* Implicit port */
      if (strcmp(myProto, "http") == 0) {
         myPort = 80;
      } else if (strcmp(myProto, "https") == 0) {
         myPort = 443;
      } else {
         /* Not implemented */
         goto error;
      }
   }

   start = end;
   if (*start == '/') {
      /* Explicit path */
      myPath = g_strdup(start);
   } else {
      /* Implicit path */
      g_assert(*start == '\0');
      myPath = g_strdup("/");
   }

   if (secure) {
      *secure = strcmp(myProto, "https") == 0;
   }
   if (proto) {
      *proto = myProto;
   } else {
      g_free(myProto);
   }
   if (host) {
      *host = myHost;
   } else {
      g_free(myHost);
   }
   if (port) {
      *port = myPort;
   }
   if (path) {
      *path = myPath;
   } else {
      g_free(myPath);
   }
   g_free(myUrl);
   return TRUE;

error:
   g_free(myUrl);
   g_free(myProto);
   g_free(myHost);
   g_free(myPath);
   return FALSE;
}