int
ls_connect(char *host)
{
    struct  hostent *hp;
    int     s, descriptor[2], size;
    char    official[MAXHOSTNAMELEN];
    struct resConnect connReq;
    char *reqBuf;
    struct lsfAuth auth;
    int resTimeout;



    if (genParams_[LSF_RES_TIMEOUT].paramValue)
	resTimeout = atoi(genParams_[LSF_RES_TIMEOUT].paramValue);
    else
	resTimeout = RES_TIMEOUT;

    if (_isconnected_(host, descriptor))
        return(descriptor[0]);

    if ((hp = Gethostbyname_(host)) == NULL) {
        lserrno = LSE_BAD_HOST;
        return -1;
    }

    strcpy(official, hp->h_name);
    memcpy((char *)&res_addr_.sin_addr,(char *)hp->h_addr,(int)hp->h_length);
    if ((rootuid_) && (genParams_[LSF_AUTH].paramValue == NULL)) {
        if (currentsocket_ > (FIRST_RES_SOCK + totsockets_ - 1)) {
            lserrno = LSE_NOMORE_SOCK;
            return -1;
        }
        s = currentsocket_;
        currentsocket_++;
    } else {
        if ((s = CreateSockEauth_(SOCK_STREAM)) < 0)
            return -1;
    }

    putEauthClientEnvVar("user");
    putEauthServerEnvVar("res");

#ifdef INTER_DAEMON_AUTH

    putEnv("LSF_EAUTH_AUX_PASS", "yes");
#endif


    if (getAuth_(&auth, official) == -1) {
	closesocket(s);
	return -1;
    }

    runEsub_(&connReq.eexec, NULL);

    size = sizeof(struct LSFHeader) + sizeof(connReq) +
	   sizeof(struct lsfAuth) +
	   ALIGNWORD_(connReq.eexec.len) +
	   sizeof(int) * 5 ;

    if ((reqBuf = malloc(size)) == NULL) {
	lserrno = LSE_MALLOC;
	goto Fail;
    }

    if (b_connect_(s, (struct sockaddr *)&res_addr_,
				 sizeof(res_addr_), resTimeout) < 0) {
	lserrno = LSE_CONN_SYS;
	goto Fail;
    }

    if (callRes_(s, RES_CONNECT, (char *) &connReq, reqBuf,
		 size, xdr_resConnect, 0, 0, &auth) == -1) {
	goto Fail;
    }

    if (connReq.eexec.len > 0)
	free(connReq.eexec.data);

    free(reqBuf);

    (void)connected_(official, s, -1, currentSN);

    return(s);

  Fail:
    CLOSESOCKET(s);

    if (connReq.eexec.len > 0)
	free(connReq.eexec.data);

    free(reqBuf);
    return -1;
}