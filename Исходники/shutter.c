void exitFATAL(int sig)
{	FILE *clog,*slog;
	CStr(reason,32);
	const char *clnt;
	CStr(serv,256);
	const char *dp;
	int servport;
	Connection *Conn = curClient.cl_Conn;
	Connection ConnBuf;

	if( exiting != 0 )
		return;
	exiting = 1;

	signal(sig,SIG_DFL);

	sprintf(reason,"SIG%s",sigsym(sig));
	if( streq(reason+3,"???") ){
		sprintf(reason,"SIG#%d",sig);
	}
	if( Conn == NULL ){
		Conn = &ConnBuf;
		bzero(Conn,sizeof(Conn));
	}

	if( sig == SIGSEGV && errno == ENOMEM ){
		syslog_ERROR("#### EXIT on insufficient memory, exceeded data or stack limitation, or exausted swap space. ####\n");
		Finish(-1);
	}

	serv[0] = 0;
	if( 0 < ToS && IsConnected(ToS,NULL) ){
		if( getpeerName(ToS,AVStr(serv),"%A:%P") ){
			dp = strchr(serv,':');
			truncVStr(dp); dp++;
			servport = atoi(dp);
		}
	}

	clnt = curClient.cl_addr;
	clog = setStopService(clnt);
	if( clog )
		logFATAL(clog,reason,clnt,serv);

	if( serv[0] && (slog = setStopService(serv)) ){
		logFATAL(slog,reason,clnt,serv);
		fclose(slog);
	}
	notify_ADMIN(Conn,reason);

	if( curClient.cl_sock < 0 ){
		DELEGATE_sigFATAL(sig);
		Finish(-1);
	}
	ProcTitle(Conn,"INTRUDER !? %s",reason);
	if( Fork("FATAL") == 0 ){
		DELEGATE_sigFATAL(sig);
		Finish(-1);
	}
	wait(0);
	/* send mail to ADMIN ... */
	holder(clog);
	ProcTitle(Conn,"INTRUDER !? disconnected");
	sleep(60);
	Finish(0);
}