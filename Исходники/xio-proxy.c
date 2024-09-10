int _xioopen_proxy_connect(struct single *xfd,
			   struct proxyvars *proxyvars,
			   int level) {
   size_t offset;
   char request[CONNLEN];
   char buff[BUFLEN+1];
#if CONNLEN > BUFLEN
#error not enough buffer space 
#endif
   char textbuff[2*BUFLEN+1];	/* just for sanitizing print data */
   char *eol = buff;
   int state;
   ssize_t sresult;

   /* generate proxy request header - points to final target */
   sprintf(request, "CONNECT %s:%u HTTP/1.0\r\n",
	   proxyvars->targetaddr, proxyvars->targetport);

   /* send proxy CONNECT request (target addr+port) */
   * xiosanitize(request, strlen(request), textbuff) = '\0';
   Info1("sending \"%s\"", textbuff);
   /* write errors are assumed to always be hard errors, no retry */
   do {
      sresult = Write(xfd->wfd, request, strlen(request));
   } while (sresult < 0 && errno == EINTR);
   if (sresult < 0) {
      Msg4(level, "write(%d, %p, "F_Zu"): %s",
	   xfd->wfd, request, strlen(request), strerror(errno));
      if (Close(xfd->wfd) < 0) {
	 Info2("close(%d): %s", xfd->wfd, strerror(errno));
      }
      return STAT_RETRYLATER;
   }

   if (proxyvars->authstring) {
      /* send proxy authentication header */
#     define XIOAUTHHEAD "Proxy-authorization: Basic "
#     define XIOAUTHLEN  27
      static const char *authhead = XIOAUTHHEAD;
#     define HEADLEN 256
      char *header, *next;

      /* ...\r\n\0 */
      if ((header =
	   Malloc(XIOAUTHLEN+((strlen(proxyvars->authstring)+2)/3)*4+3))
	  == NULL) {
	 return -1;
      }
      strcpy(header, authhead);
      next = xiob64encodeline(proxyvars->authstring,
			      strlen(proxyvars->authstring),
			      strchr(header, '\0'));
      *next = '\0';
      Info1("sending \"%s\\r\\n\"", header);
      *next++ = '\r';  *next++ = '\n'; *next++ = '\0';
      do {
	 sresult = Write(xfd->wfd, header, strlen(header));
      } while (sresult < 0 && errno == EINTR);
      if (sresult < 0) {
	 Msg4(level, "write(%d, %p, "F_Zu"): %s",
	      xfd->wfd, header, strlen(header), strerror(errno));
	 if (Close(xfd->wfd/*!*/) < 0) {
	    Info2("close(%d): %s", xfd->wfd, strerror(errno));
	 }
	 return STAT_RETRYLATER;
      }

      free(header);
   }

   Info("sending \"\\r\\n\"");
   do {
      sresult = Write(xfd->wfd, "\r\n", 2);
   } while (sresult < 0 && errno == EINTR);
   /*! */

   /* request is kept for later error messages */
   *strstr(request, " HTTP") = '\0';

   /* receive proxy answer; looks like "HTTP/1.0 200 .*\r\nHeaders..\r\n\r\n" */
   /* socat version 1 depends on a valid fd for data transfer; address
      therefore cannot buffer data. So, to prevent reading beyond the end of
      the answer headers, only single bytes are read. puh. */
   state = XIOSTATE_HTTP1;
   offset = 0;	/* up to where the buffer is filled (relative) */
   /*eol;*/	/* points to the first lineterm of the current line */
   do {
      sresult = xioproxy_recvbytes(xfd, buff+offset, 1, level);
      if (sresult <= 0) {
	 state = XIOSTATE_ERROR;
	 break;	/* leave read cycles */
      }
      
      switch (state) {

      case XIOSTATE_HTTP1:
	 /* 0 or more bytes of first line received, no '\r' yet */
	 if (*(buff+offset) == '\r') {
	    eol = buff+offset;
	    state = XIOSTATE_HTTP2;
	    break;
	 }
	 if (proxyvars->ignorecr && *(buff+offset) == '\n') {
	    eol = buff+offset;
	    state = XIOSTATE_HTTP3;
	    break;
	 }
	 break;

      case XIOSTATE_HTTP2:
	 /* first line received including '\r' */
	 if (*(buff+offset) != '\n') {
	    state = XIOSTATE_HTTP1;
	    break;
	 }
	 state = XIOSTATE_HTTP3;
	 break;

      case XIOSTATE_HTTP3:
	 /* received status (first line) and "\r\n" */
	 if (*(buff+offset) == '\r') {
	    state = XIOSTATE_HTTP7;
	    break;
	 }
	 if (proxyvars->ignorecr && *(buff+offset) == '\n') {
	    state = XIOSTATE_HTTP8;
	    break;
	 }
	 state = XIOSTATE_HTTP4;
	 break;
	 
      case XIOSTATE_HTTP4:
	 /* within header */
	 if (*(buff+offset) == '\r') {
	    eol = buff+offset;
	    state = XIOSTATE_HTTP5;
	    break;
	 }
	 if (proxyvars->ignorecr && *(buff+offset) == '\n') {
	    eol = buff+offset;
	    state = XIOSTATE_HTTP6;
	    break;
	 }
	 break;

      case XIOSTATE_HTTP5:
	 /* within header, '\r' received */
	 if (*(buff+offset) != '\n') {
	    state = XIOSTATE_HTTP4;
	    break;
	 }
	 state = XIOSTATE_HTTP6;
	 break;

      case XIOSTATE_HTTP6:
	 /* received status (first line) and 1 or more headers, "\r\n" */
	 if (*(buff+offset) == '\r') {
	    state = XIOSTATE_HTTP7;
	    break;
	 }
	 if (proxyvars->ignorecr && *(buff+offset) == '\n') {
	    state = XIOSTATE_HTTP8;
	    break;
	 }
	 state = XIOSTATE_HTTP4;
	 break;

      case XIOSTATE_HTTP7:
	 /* received status (first line), 0 or more headers, "\r\n\r" */
	 if (*(buff+offset) == '\n') {
	    state = XIOSTATE_HTTP8;
	    break;
	 }
	 if (*(buff+offset) == '\r') {
	    if (proxyvars->ignorecr) {
	       break;	/* ignore it, keep waiting for '\n' */
	    } else {
	       state = XIOSTATE_HTTP5;
	    }
	    break;
	 }
	 state = XIOSTATE_HTTP4;
	 break;

      }
      ++offset;

      /* end of status line reached */
      if (state == XIOSTATE_HTTP3) {
	 char *ptr;
	 /* set a terminating null - on or after CRLF? */
	 *(buff+offset) = '\0';

	 * xiosanitize(buff, Min(offset, (sizeof(textbuff)-1)>>1), textbuff)
	    = '\0';
	 Info1("proxy_connect: received answer \"%s\"", textbuff);
	 *eol = '\0';
	 * xiosanitize(buff, Min(strlen(buff), (sizeof(textbuff)-1)>>1),
		       textbuff) = '\0';
	 if (strncmp(buff, "HTTP/1.0 ", 9) &&
	     strncmp(buff, "HTTP/1.1 ", 9)) {
	    /* invalid answer */
	    Msg1(level, "proxy: invalid answer \"%s\"", textbuff);
	    return STAT_RETRYLATER;
	 }
	 ptr = buff+9;

	 /* skip multiple spaces */
	 while (*ptr == ' ')  ++ptr;

	 /* HTTP answer */
	 if (strncmp(ptr, "200", 3)) {
	    /* not ok */
	    /* CERN:
	       "HTTP/1.0 200 Connection established"
	       "HTTP/1.0 400 Invalid request "CONNECT 10.244.9.3:8080 HTTP/1.0" (unknown method)"
	       "HTTP/1.0 403 Forbidden - by rule"
	       "HTTP/1.0 407 Proxy Authentication Required"
	       Proxy-Authenticate: Basic realm="Squid proxy-caching web server"
>  50 72 6f 78 79 2d 61 75 74 68 6f 72 69 7a 61 74  Proxy-authorizat
>  69 6f 6e 3a 20 42 61 73 69 63 20 61 57 4e 6f 63  ion: Basic aWNoc
>  32 56 73 59 6e 4e 30 4f 6e 4e 30 63 6d 56 75 5a  2VsYnN0OnN0cmVuZ
>  32 64 6c 61 47 56 70 62 51 3d 3d 0d 0a           2dlaGVpbQ==..
                b64encode("username:password")
	       "HTTP/1.0 500 Can't connect to host"
	    */
	    /* Squid:
	       "HTTP/1.0 400 Bad Request"
	       "HTTP/1.0 403 Forbidden"
	       "HTTP/1.0 503 Service Unavailable"
	       interesting header: "X-Squid-Error: ERR_CONNECT_FAIL 111" */
	    /* Apache:
	       "HTTP/1.0 400 Bad Request"
	       "HTTP/1.1 405 Method Not Allowed"
	    */
	    /* WTE:
	       "HTTP/1.1 200 Connection established"
	       "HTTP/1.1 404 Host not found or not responding, errno:  79"
	       "HTTP/1.1 404 Host not found or not responding, errno:  32"
	       "HTTP/1.1 404 Host not found or not responding, errno:  13"
	    */
	    /* IIS:
	       "HTTP/1.1 404 Object Not Found"
	    */
	    ptr += 3;
	    while (*ptr == ' ')  ++ptr;
	    
	    Msg2(level, "%s: %s", request, ptr);
	    return STAT_RETRYLATER;
	 }

	 /* ok!! */
	 /* "HTTP/1.0 200 Connection established" */
	 /*Info1("proxy: \"%s\"", textbuff+13);*/
	 offset = 0;

      } else if (state == XIOSTATE_HTTP6) {
      /* end of a header line reached */
	 char *endp;

	 /* set a terminating null */
	 *(buff+offset) = '\0';

	 endp =
	    xiosanitize(buff, Min(offset, (sizeof(textbuff)-1)>>1),
			textbuff);
	 *endp = '\0';
	 Info1("proxy_connect: received header \"%s\"", textbuff);
	 offset = 0;
      }