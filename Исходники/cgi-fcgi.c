int main(int argc, char **argv, char **envp)
{
    int count;
    FCGX_Stream *paramsStream;
    fd_set readFdSet, writeFdSet;
    int numFDs, selectStatus;
    unsigned char headerBuff[8];
    int headerLen, valueLen;
    char *equalPtr;
    FCGI_BeginRequestRecord beginRecord;
    int	doBind, doStart, nServers;
    char appPath[MAXPATHLEN], bindPath[MAXPATHLEN];

    if(ParseArgs(argc, argv, &doBind, &doStart,
		   (char *) &bindPath, (char *) &appPath, &nServers)) {
	fprintf(stderr,
"Usage:\n"
"    cgi-fcgi -f <cmdPath> , or\n"
"    cgi-fcgi -connect <connName> <appPath> [<nServers>] , or\n"
"    cgi-fcgi -start -connect <connName> <appPath> [<nServers>] , or\n"
"    cgi-fcgi -bind -connect <connName> ,\n"
"where <connName> is either the pathname of a UNIX domain socket\n"
"or (if -bind is given) a hostName:portNumber specification\n"
"or (if -start is given) a :portNumber specification (uses local host).\n");
	exit(1);
    }
    if(doBind) {
        appServerSock = OS_FcgiConnect(bindPath);
    }
    if(doStart && (!doBind || appServerSock < 0)) {
        FCGI_Start(bindPath, appPath, nServers);
        if(!doBind) {
            exit(0);
        } else {
            appServerSock = OS_FcgiConnect(bindPath);
	}
    }
    if(appServerSock < 0) {
        fprintf(stderr, "Could not connect to %s\n", bindPath);
        exit(errno);
    }
    /*
     * Set an arbitrary non-null FCGI RequestId
     */
    requestId = 1;
    /*
     * XXX: Send FCGI_GET_VALUES
     */

    /*
     * XXX: Receive FCGI_GET_VALUES_RESULT
     */

    /*
     * Send FCGI_BEGIN_REQUEST (XXX: hack, separate write)
     */
    beginRecord.header = MakeHeader(FCGI_BEGIN_REQUEST, requestId,
            sizeof(beginRecord.body), 0);
    beginRecord.body = MakeBeginRequestBody(FCGI_RESPONDER, TRUE);
    count = write(appServerSock, &beginRecord, sizeof(beginRecord));
    if(count != sizeof(beginRecord)) {
        exit(errno);
    }
    /*
     * Send environment to the FCGI application server
     */
    paramsStream = CreateWriter(appServerSock, requestId, 8192, FCGI_PARAMS);
    for( ; *envp != NULL; envp++) {
        equalPtr = strchr(*envp, '=');
        if(equalPtr  == NULL) {
            exit(1000);
        }
        valueLen = strlen(equalPtr + 1);
        FCGIUtil_BuildNameValueHeader(
                equalPtr - *envp,
                valueLen,
                &headerBuff[0],
                &headerLen);
        if(FCGX_PutStr((char *) &headerBuff[0], headerLen, paramsStream) < 0
                || FCGX_PutStr(*envp, equalPtr - *envp, paramsStream) < 0
                || FCGX_PutStr(equalPtr + 1, valueLen, paramsStream) < 0) {
            exit(FCGX_GetError(paramsStream));
        }
    }
    FCGX_FClose(paramsStream);
    FreeStream(&paramsStream);
    /*
     * Perform the event loop until AppServerReadHander sees FCGI_END_REQUEST
     */
    fromWS.stop = fromWS.next = &fromWS.buff[0];
    webServerReadHandlerEOF = FALSE;
    FD_ZERO(&readFdSet);
    FD_ZERO(&writeFdSet);
    numFDs = max(appServerSock, STDIN_FILENO) + 1;
    SetFlags(appServerSock, O_NONBLOCK);
    for(;;) {
        if((fromWS.stop == fromWS.next) && !webServerReadHandlerEOF) {
            FD_SET(STDIN_FILENO, &readFdSet);
        } else {
            FD_CLR(STDIN_FILENO, &readFdSet);
        }
        if(fromWS.stop != fromWS.next) {
            FD_SET(appServerSock, &writeFdSet);
        } else {
            FD_CLR(appServerSock, &writeFdSet);
        }
        FD_SET(appServerSock, &readFdSet);
        selectStatus = select(numFDs, &readFdSet, &writeFdSet, NULL, NULL);
        if(selectStatus < 0) {
            exit(errno);
        }
        if(selectStatus == 0) {
            /*
             * Should not happen, no select timeout.
             */
            continue;
        }
        if(FD_ISSET(STDIN_FILENO, &readFdSet)) {
            WebServerReadHandler();
        }
        if(FD_ISSET(appServerSock, &writeFdSet)) {
            AppServerWriteHandler();
        }
        if(FD_ISSET(appServerSock, &readFdSet)) {
            AppServerReadHandler();
	}
        if(exitStatusSet) {
            exit(exitStatus);
	}
    } 
}