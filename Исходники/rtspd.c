static int ProcessRequest(struct httprequest *req)
{
  char *line=&req->reqbuf[req->checkindex];
  bool chunked = FALSE;
  static char request[REQUEST_KEYWORD_SIZE];
  static char doc[MAXDOCNAMELEN];
  static char prot_str[5];
  char logbuf[256];
  int prot_major, prot_minor;
  char *end;
  int error;
  end = strstr(line, END_OF_HEADERS);

  logmsg("ProcessRequest() called with testno %ld and line [%s]",
         req->testno, line);

  /* try to figure out the request characteristics as soon as possible, but
     only once! */
  if((req->testno == DOCNUMBER_NOTHING) &&
     sscanf(line,
            "%" REQUEST_KEYWORD_SIZE_TXT"s %" MAXDOCNAMELEN_TXT "s %4s/%d.%d",
            request,
            doc,
            prot_str,
            &prot_major,
            &prot_minor) == 5) {
    char *ptr;

    if(!strcmp(prot_str, "HTTP")) {
        req->protocol = RPROT_HTTP;
    }
    else if(!strcmp(prot_str, "RTSP")) {
        req->protocol = RPROT_RTSP;
    }
    else {
        req->protocol = RPROT_NONE;
        logmsg("got unknown protocol %s", prot_str);
        return 1;
    }

    req->prot_version = prot_major*10 + prot_minor;

    /* find the last slash */
    ptr = strrchr(doc, '/');

    /* get the number after it */
    if(ptr) {
      FILE *stream;
      char *filename;

      if((strlen(doc) + strlen(request)) < 200)
        sprintf(logbuf, "Got request: %s %s %s/%d.%d",
                request, doc, prot_str, prot_major, prot_minor);
      else
        sprintf(logbuf, "Got a *HUGE* request %s/%d.%d",
                prot_str, prot_major, prot_minor);
      logmsg("%s", logbuf);

      if(!strncmp("/verifiedserver", ptr, 15)) {
        logmsg("Are-we-friendly question received");
        req->testno = DOCNUMBER_WERULEZ;
        return 1; /* done */
      }

      if(!strncmp("/quit", ptr, 5)) {
        logmsg("Request-to-quit received");
        req->testno = DOCNUMBER_QUIT;
        return 1; /* done */
      }

      ptr++; /* skip the slash */

      /* skip all non-numericals following the slash */
      while(*ptr && !ISDIGIT(*ptr))
        ptr++;

      req->testno = strtol(ptr, &ptr, 10);

      if(req->testno > 10000) {
        req->partno = req->testno % 10000;
        req->testno /= 10000;
      }
      else
        req->partno = 0;

      sprintf(logbuf, "Requested test number %ld part %ld",
              req->testno, req->partno);
      logmsg("%s", logbuf);

      filename = test2file(req->testno);

      stream=fopen(filename, "rb");
      if(!stream) {
        error = ERRNO;
        logmsg("fopen() failed with error: %d %s", error, strerror(error));
        logmsg("Error opening file: %s", filename);
        logmsg("Couldn't open test file %ld", req->testno);
        req->open = FALSE; /* closes connection */
        return 1; /* done */
      }
      else {
        char *cmd = NULL;
        size_t cmdsize = 0;
        int num=0;

        int rtp_channel = 0;
        int rtp_size = 0;
        int rtp_partno = -1;
        int i = 0;
        char *rtp_scratch = NULL;

        /* get the custom server control "commands" */
        cmd = (char *)spitout(stream, "reply", "servercmd", &cmdsize);
        ptr = cmd;
        fclose(stream);

        if(cmdsize) {
          logmsg("Found a reply-servercmd section!");
          do {
            if(!strncmp(CMD_AUTH_REQUIRED, ptr, strlen(CMD_AUTH_REQUIRED))) {
              logmsg("instructed to require authorization header");
              req->auth_req = TRUE;
            }
            else if(!strncmp(CMD_IDLE, ptr, strlen(CMD_IDLE))) {
              logmsg("instructed to idle");
              req->rcmd = RCMD_IDLE;
              req->open = TRUE;
            }
            else if(!strncmp(CMD_STREAM, ptr, strlen(CMD_STREAM))) {
              logmsg("instructed to stream");
              req->rcmd = RCMD_STREAM;
            }
            else if(1 == sscanf(ptr, "pipe: %d", &num)) {
              logmsg("instructed to allow a pipe size of %d", num);
              if(num < 0)
                logmsg("negative pipe size ignored");
              else if(num > 0)
                req->pipe = num-1; /* decrease by one since we don't count the
                                      first request in this number */
            }
            else if(1 == sscanf(ptr, "skip: %d", &num)) {
              logmsg("instructed to skip this number of bytes %d", num);
              req->skip = num;
            }
            else if(3 == sscanf(ptr, "rtp: part %d channel %d size %d",
                                &rtp_partno, &rtp_channel, &rtp_size)) {

              if(rtp_partno == req->partno) {
                logmsg("RTP: part %d channel %d size %d",
                       rtp_partno, rtp_channel, rtp_size);

                /* Make our scratch buffer enough to fit all the
                 * desired data and one for padding */
                rtp_scratch = malloc(rtp_size + 4 + RTP_DATA_SIZE);

                /* RTP is signalled with a $ */
                rtp_scratch[0] = '$';

                /* The channel follows and is one byte */
                rtp_scratch[1] = (char)(rtp_channel & 0xFF);

                /* Length follows and is a two byte short in network order */
                *((unsigned short *)(&rtp_scratch[2])) =
                  htons((unsigned short)rtp_size);

                /* Fill it with junk data */
                for(i = 0; i < rtp_size; i+= RTP_DATA_SIZE) {
                  memcpy(rtp_scratch + 4 + i, RTP_DATA, RTP_DATA_SIZE);
                }

                if(req->rtp_buffer == NULL) {
                  req->rtp_buffer = rtp_scratch;
                  req->rtp_buffersize = rtp_size + 4;
                } else {
                  req->rtp_buffer = realloc(req->rtp_buffer, req->rtp_buffersize + rtp_size + 4);
                  memcpy(req->rtp_buffer + req->rtp_buffersize, rtp_scratch, rtp_size + 4);
                  req->rtp_buffersize += rtp_size + 4;
                  free(rtp_scratch);
                }
                logmsg("rtp_buffersize is %zu, rtp_size is %d.", req->rtp_buffersize, rtp_size);

              }
            }
            else {
              logmsg("funny instruction found: %s", ptr);
            }

            ptr = strchr(ptr, '\n');
            if(ptr)
              ptr++;
            else
              ptr = NULL;
          } while(ptr && *ptr);
          logmsg("Done parsing server commands");
        }
      }
    }
    else {
      if(sscanf(req->reqbuf, "CONNECT %" MAXDOCNAMELEN_TXT "s HTTP/%d.%d",
                doc, &prot_major, &prot_minor) == 3) {
        sprintf(logbuf, "Received a CONNECT %s HTTP/%d.%d request",
                doc, prot_major, prot_minor);
        logmsg("%s", logbuf);

        if(req->prot_version == 10)
          req->open = FALSE; /* HTTP 1.0 closes connection by default */

        if(!strncmp(doc, "bad", 3))
          /* if the host name starts with bad, we fake an error here */
          req->testno = DOCNUMBER_BADCONNECT;
        else if(!strncmp(doc, "test", 4)) {
          /* if the host name starts with test, the port number used in the
             CONNECT line will be used as test number! */
          char *portp = strchr(doc, ':');
          if(portp)
            req->testno = atoi(portp+1);
          else
            req->testno = DOCNUMBER_CONNECT;
        }
        else
          req->testno = DOCNUMBER_CONNECT;
      }
      else {
        logmsg("Did not find test number in PATH");
        req->testno = DOCNUMBER_404;
      }
    }
  }

  if(!end) {
    /* we don't have a complete request yet! */
    logmsg("ProcessRequest returned without a complete request");
    return 0; /* not complete yet */
  }
  logmsg("ProcessRequest found a complete request");

  if(req->pipe)
    /* we do have a full set, advance the checkindex to after the end of the
       headers, for the pipelining case mostly */
    req->checkindex += (end - line) + strlen(END_OF_HEADERS);

  /* **** Persistence ****
   *
   * If the request is a HTTP/1.0 one, we close the connection unconditionally
   * when we're done.
   *
   * If the request is a HTTP/1.1 one, we MUST check for a "Connection:"
   * header that might say "close". If it does, we close a connection when
   * this request is processed. Otherwise, we keep the connection alive for X
   * seconds.
   */

  do {
    if(got_exit_signal)
      return 1; /* done */

    if((req->cl==0) && curlx_strnequal("Content-Length:", line, 15)) {
      /* If we don't ignore content-length, we read it and we read the whole
         request including the body before we return. If we've been told to
         ignore the content-length, we will return as soon as all headers
         have been received */
      size_t cl = strtol(line+15, &line, 10);
      req->cl = cl - req->skip;

      logmsg("Found Content-Length: %zu in the request", cl);
      if(req->skip)
        logmsg("... but will abort after %zu bytes", req->cl);
      break;
    }
    else if(curlx_strnequal("Transfer-Encoding: chunked", line,
                            strlen("Transfer-Encoding: chunked"))) {
      /* chunked data coming in */
      chunked = TRUE;
    }

    if(chunked) {
      if(strstr(req->reqbuf, "\r\n0\r\n\r\n"))
        /* end of chunks reached */
        return 1; /* done */
      else
        return 0; /* not done */
    }

    line = strchr(line, '\n');
    if(line)
      line++;

  } while(line);

  if(!req->auth && strstr(req->reqbuf, "Authorization:")) {
    req->auth = TRUE; /* Authorization: header present! */
    if(req->auth_req)
      logmsg("Authorization header found, as required");
  }

  if(!req->digest && strstr(req->reqbuf, "Authorization: Digest")) {
    /* If the client is passing this Digest-header, we set the part number
       to 1000. Not only to spice up the complexity of this, but to make
       Digest stuff to work in the test suite. */
    req->partno += 1000;
    req->digest = TRUE; /* header found */
    logmsg("Received Digest request, sending back data %ld", req->partno);
  }
  else if(!req->ntlm &&
          strstr(req->reqbuf, "Authorization: NTLM TlRMTVNTUAAD")) {
    /* If the client is passing this type-3 NTLM header */
    req->partno += 1002;
    req->ntlm = TRUE; /* NTLM found */
    logmsg("Received NTLM type-3, sending back data %ld", req->partno);
    if(req->cl) {
      logmsg("  Expecting %zu POSTed bytes", req->cl);
    }
  }
  else if(!req->ntlm &&
          strstr(req->reqbuf, "Authorization: NTLM TlRMTVNTUAAB")) {
    /* If the client is passing this type-1 NTLM header */
    req->partno += 1001;
    req->ntlm = TRUE; /* NTLM found */
    logmsg("Received NTLM type-1, sending back data %ld", req->partno);
  }
  else if((req->partno >= 1000) && strstr(req->reqbuf, "Authorization: Basic")) {
    /* If the client is passing this Basic-header and the part number is already
       >=1000, we add 1 to the part number.  This allows simple Basic authentication
       negotiation to work in the test suite. */
    req->partno += 1;
    logmsg("Received Basic request, sending back data %ld", req->partno);
  }
  if(strstr(req->reqbuf, "Connection: close"))
    req->open = FALSE; /* close connection after this request */

  if(!req->pipe &&
     req->open &&
     req->prot_version >= 11 &&
     end &&
     req->reqbuf + req->offset > end + strlen(END_OF_HEADERS) &&
     (!strncmp(req->reqbuf, "GET", strlen("GET")) ||
      !strncmp(req->reqbuf, "HEAD", strlen("HEAD")))) {
    /* If we have a persistent connection, HTTP version >= 1.1
       and GET/HEAD request, enable pipelining. */
    req->checkindex = (end - req->reqbuf) + strlen(END_OF_HEADERS);
    req->pipelining = TRUE;
  }

  while(req->pipe) {
    if(got_exit_signal)
      return 1; /* done */
    /* scan for more header ends within this chunk */
    line = &req->reqbuf[req->checkindex];
    end = strstr(line, END_OF_HEADERS);
    if(!end)
      break;
    req->checkindex += (end - line) + strlen(END_OF_HEADERS);
    req->pipe--;
  }

  /* If authentication is required and no auth was provided, end now. This
     makes the server NOT wait for PUT/POST data and you can then make the
     test case send a rejection before any such data has been sent. Test case
     154 uses this.*/
  if(req->auth_req && !req->auth)
    return 1; /* done */

  if(req->cl > 0) {
    if(req->cl <= req->offset - (end - req->reqbuf) - strlen(END_OF_HEADERS))
      return 1; /* done */
    else
      return 0; /* not complete yet */
  }

  return 1; /* done */
}