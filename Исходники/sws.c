static int ProcessRequest(struct httprequest *req)
{
  char *line=&req->reqbuf[req->checkindex];
  bool chunked = FALSE;
  static char request[REQUEST_KEYWORD_SIZE];
  static char doc[MAXDOCNAMELEN];
  char logbuf[256];
  int prot_major, prot_minor;
  char *end;
  int error;
  end = strstr(line, end_of_headers);

  logmsg("ProcessRequest() called");

  /* try to figure out the request characteristics as soon as possible, but
     only once! */

  if(use_gopher &&
     (req->testno == DOCNUMBER_NOTHING) &&
     !strncmp("/verifiedserver", line, 15)) {
    logmsg("Are-we-friendly question received");
    req->testno = DOCNUMBER_WERULEZ;
    return 1; /* done */
  }

  else if((req->testno == DOCNUMBER_NOTHING) &&
     sscanf(line,
            "%" REQUEST_KEYWORD_SIZE_TXT"s %" MAXDOCNAMELEN_TXT "s HTTP/%d.%d",
            request,
            doc,
            &prot_major,
            &prot_minor) == 4) {
    char *ptr;

    req->prot_version = prot_major*10 + prot_minor;

    /* find the last slash */
    ptr = strrchr(doc, '/');

    /* get the number after it */
    if(ptr) {
      FILE *stream;
      char *filename;

      if((strlen(doc) + strlen(request)) < 200)
        sprintf(logbuf, "Got request: %s %s HTTP/%d.%d",
                request, doc, prot_major, prot_minor);
      else
        sprintf(logbuf, "Got a *HUGE* request HTTP/%d.%d",
                prot_major, prot_minor);
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
        char *orgcmd = NULL;
        char *cmd = NULL;
        size_t cmdsize = 0;
        int num=0;

        /* get the custom server control "commands" */
        error = getpart(&orgcmd, &cmdsize, "reply", "servercmd", stream);
        fclose(stream);
        if(error) {
          logmsg("getpart() failed with error: %d", error);
          req->open = FALSE; /* closes connection */
          return 1; /* done */
        }

        cmd = orgcmd;
        while(cmd && cmdsize) {
          char *check;

          if(!strncmp(CMD_AUTH_REQUIRED, cmd, strlen(CMD_AUTH_REQUIRED))) {
            logmsg("instructed to require authorization header");
            req->auth_req = TRUE;
          }
          else if(!strncmp(CMD_IDLE, cmd, strlen(CMD_IDLE))) {
            logmsg("instructed to idle");
            req->rcmd = RCMD_IDLE;
            req->open = TRUE;
          }
          else if(!strncmp(CMD_STREAM, cmd, strlen(CMD_STREAM))) {
            logmsg("instructed to stream");
            req->rcmd = RCMD_STREAM;
          }
          else if(1 == sscanf(cmd, "pipe: %d", &num)) {
            logmsg("instructed to allow a pipe size of %d", num);
            if(num < 0)
              logmsg("negative pipe size ignored");
            else if(num > 0)
              req->pipe = num-1; /* decrease by one since we don't count the
                                    first request in this number */
          }
          else if(1 == sscanf(cmd, "skip: %d", &num)) {
            logmsg("instructed to skip this number of bytes %d", num);
            req->skip = num;
          }
          else if(1 == sscanf(cmd, "writedelay: %d", &num)) {
            logmsg("instructed to delay %d secs between packets", num);
            req->writedelay = num;
          }
          else {
            logmsg("funny instruction found: %s", cmd);
          }
          /* try to deal with CRLF or just LF */
          check = strchr(cmd, '\r');
          if(!check)
            check = strchr(cmd, '\n');

          if(check) {
            /* get to the letter following the newline */
            while((*check == '\r') || (*check == '\n'))
              check++;

            if(!*check)
              /* if we reached a zero, get out */
              break;
            cmd = check;
          }
          else
            break;
        }
        if(orgcmd)
          free(orgcmd);
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
          if(portp && (*(portp+1) != '\0') && ISDIGIT(*(portp+1)))
            req->testno = strtol(portp+1, NULL, 10);
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

  if(use_gopher) {
    /* when using gopher we cannot check the request until the entire
       thing has been received */
    char *ptr;

    /* find the last slash in the line */
    ptr = strrchr(line, '/');

    if(ptr) {
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

      sprintf(logbuf, "Requested GOPHER test number %ld part %ld",
              req->testno, req->partno);
      logmsg("%s", logbuf);
    }
  }

  if(req->pipe)
    /* we do have a full set, advance the checkindex to after the end of the
       headers, for the pipelining case mostly */
    req->checkindex += (end - line) + strlen(end_of_headers);

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
      char *endptr;
      char *ptr = line + 15;
      unsigned long clen = 0;
      while(*ptr && ISSPACE(*ptr))
        ptr++;
      endptr = ptr;
      SET_ERRNO(0);
      clen = strtoul(ptr, &endptr, 10);
      if((ptr == endptr) || !ISSPACE(*endptr) || (ERANGE == ERRNO)) {
        /* this assumes that a zero Content-Length is valid */
        logmsg("Found invalid Content-Length: (%s) in the request", ptr);
        req->open = FALSE; /* closes connection */
        return 1; /* done */
      }
      req->cl = clen - req->skip;

      logmsg("Found Content-Length: %lu in the request", clen);
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
     req->reqbuf + req->offset > end + strlen(end_of_headers) &&
     (!strncmp(req->reqbuf, "GET", strlen("GET")) ||
      !strncmp(req->reqbuf, "HEAD", strlen("HEAD")))) {
    /* If we have a persistent connection, HTTP version >= 1.1
       and GET/HEAD request, enable pipelining. */
    req->checkindex = (end - req->reqbuf) + strlen(end_of_headers);
    req->pipelining = TRUE;
  }

  while(req->pipe) {
    if(got_exit_signal)
      return 1; /* done */
    /* scan for more header ends within this chunk */
    line = &req->reqbuf[req->checkindex];
    end = strstr(line, end_of_headers);
    if(!end)
      break;
    req->checkindex += (end - line) + strlen(end_of_headers);
    req->pipe--;
  }

  /* If authentication is required and no auth was provided, end now. This
     makes the server NOT wait for PUT/POST data and you can then make the
     test case send a rejection before any such data has been sent. Test case
     154 uses this.*/
  if(req->auth_req && !req->auth)
    return 1; /* done */

  if(req->cl > 0) {
    if(req->cl <= req->offset - (end - req->reqbuf) - strlen(end_of_headers))
      return 1; /* done */
    else
      return 0; /* not complete yet */
  }

  return 1; /* done */
}