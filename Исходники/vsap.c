int service_vsap(Connection *Conn)
{	CStr(request,1024);
	CStr(reqver,128);
	const char *req;
	int svsock,shared,clsock,rcode;
	CStr(myport,256);
	CStr(sockname,MaxHostNameLen);
	CStr(peername,MaxHostNameLen);
	int wcc,rcc;
	CStr(com,1024);
	CStr(arg,1024);
	const char *argp;
	CStr(opt,32);
	const char *op;
	int timeout;
	int AuthOk;
	FILE *authout;

	minit_vsapsv();
	if( ToS <= 0 || FromS <= 0 ){
		/*
		If the DST_HOST is not local
		connect to the master and simple_relay...
		 */
	}
	if( !isMYSELF(DFLT_HOST) ){
		daemonlog("E","VSAP relaying to %s:%d\n",DFLT_HOST,DFLT_PORT);
		if( ToS < 0 )
			connect_to_serv(Conn,FromC,ToC,0);
		relay_svcl(Conn,FromC,ToC,FromS,ToS);
		close(ToS);
		return 0;
	}

	/*
	timeout = 300;
	*/
	timeout = IO_TIMEOUT;

	shared = 0;
	myport[0] = 0;
	SvSockN = 0;
	ClSockN = 0;
	clsock = -1;
	svsock = -1;
	reqver[0] = 0;

	authout = TMPFILE("VSAP-AUTH");
	if( doAUTH(Conn,NULL,authout,"vsap","-",0,CVStr("user-xxxx:pass-xxxx"),CVStr("host-xxxx"),NULL,NULL) == EOF ){
		AuthOk = 0;
	}else	AuthOk = -1;

	if( ImMaster ){
		sprintf(myport,"%s:%d",DST_HOST,DST_PORT);
	}else
	for(;;){
		if( DDI_fgetsFromCbuf(Conn,AVStr(request),sizeof(request),NULL) == 0 )
		{	int closed = 0;
			for(;;){
				if( PollIn(FromC,1*1000) != 0 )
					break;
				closed |= checkCloseOnTimeout(1);
				if( 0 <= clsock && !IsAlive(clsock) ){
daemonlog("E","## disconnected by peer\n");
SockPrintf(ToC,"%s %d %s.\r\n",VER,NO_GENERIC_BYE,"disconnected by peer");
					close(clsock);del_clsock(clsock);
					goto EXIT;
				}
			}
		if( (rcc = RecvLine(FromC,request,sizeof(request))) <= 0 )
			break;
		}

		daemonlog("D","CLIENT-SAYS: %s",request);
daemonlog("E","CLIENT-SAYS: %s",request);
		req = request;
		if( strncmp(req,"VSAP/",5) == 0 )
			req = wordScan(req,reqver);

		argp = wordScan(req,com);
		arg[0] = 0;
		lineScan(argp,arg);

		if( strcasecmp(com,"AUTH") == 0 ){
			CStr(ahost,MaxHostNameLen);
			ahost[0] = 0;
			if( doAUTH(Conn,NULL,authout,"vsap","-",0,AVStr(arg),AVStr(ahost),NULL,NULL) == EOF ){
			}else{
				AuthOk = 1;
				SockPrintf(ToC,"%s %d OK\r\n",VER,OK_GENERIC);
				continue;
			}
		}
		if( AuthOk == 0 ){
			SockPrintf(ToC,"%s %d forbidden\r\n",VER,NO_PERMISSION);
			sv1log("WITH AUTHORIZER, but NO AUTH from client\n");
			break;
		}

		if( strcasecmp(com,"ECHO") == 0 ){
			CStr(stime,64);
			StrftimeLocal(AVStr(stime),sizeof(stime),TIMEFORM_HTTPD,time(0),0);
			SockPrintf(ToC,"%s %d [%s] %s\r\n",VER,OK_GENERIC,
				stime,arg);
		}else
		if( strcasecmp(com,"CONNECT") == 0 ){
			strcpy(myport,arg);
			if( !vsap_permit(Conn,myport) )
				break;
			clsock = do_connect(svsock,myport,ToC);
			if( clsock < 0 )
				break;
		}else
		if( strcasecmp(com,"BIND") == 0 ){
			CStr(opts,1024);
			opts[0] = 0;
			Xsscanf(arg,"%s %[^\r\n]",AVStr(myport),AVStr(opts));
			if( !vsap_permit(Conn,myport) )
				break;
			svsock = do_bind(-1,AVStr(myport),opts,&shared,AVStr(sockname),ToC);
			if( svsock < 0 )
				break;
		}else
		if( strcasecmp(com,"LISTEN") == 0 ){
			int nlisten = atoi(arg);
			Socket1("VSAP",svsock,NULL,NULL,NULL,VStrANYPORT,ANYPORT,nlisten,NULL,0);
			SockPrintf(ToC,"%s %d listen ok.\r\n",VER,OK_LISTEN);
		}else
		if( strcasecmp(com,"ACCEPT") == 0 ){
			int priority;
			if( Conn->cl_count <= 1 )
				priority = 0;
			else	priority = 1;

			clsock = do_accept(myport,arg,shared,priority,FromC,ToC);
			if( !shared )
				svsock = -1;

			if( clsock < 0 ){
				wcc = SockPrintf(ToC,"%s %d accept fail\r\n",
					VER,NO_ACCEPT);
				break;
			}
			add_clsock(clsock);
			if( myport[0] == '/' ){
				strcpy(sockname,myport);
				strcpy(peername,myport);
			}else	getpairName(clsock,AVStr(sockname),AVStr(peername));
			wcc = SockPrintf(ToC,"%s %d %d %s %s accepted.\r\n",
				VER,OK_ACCEPT,ClSockN,sockname,peername);
		}else
		if( strcasecmp(com,"QUIT") == 0 ){
			SockPrintf(ToC,"%s %d bye.\r\n",VER,OK_BYE);
			break;
		}else
		if( strcasecmp(com,"FORWARD") == 0 ){
			do_forward(Conn,myport,arg,shared,svsock,0,FromC,ToC);
		}else
		if( strcasecmp(com,"RELAY") == 0 ){
/*
-t timeout
 */
			for( op = arg; *op == '-'; ){
				if( strneq(op,"-t=",3) ){
					int to;
					op = numscanX(op+3,AVStr(opt),sizeof(opt));
					to = atoi(opt);
					if( to < timeout )
						timeout = to;
				}else{
					break;
				}
			}

			tcp_relay2(timeout*1000,FromC,clsock,clsock,ToC);
			/*
			set_linger(clsock,10);
			*/
			set_linger(clsock,LIN_TIMEOUT);
			close(clsock);del_clsock(clsock);
			break;
		}else
		if( strcasecmp(com,"PROXY") == 0 ){
			ToS = FromS = ToC;
			ToC = FromC = clsock;
daemonlog("E","##### VSAP switch protocol to '%s'\n",arg);
			if( strcmp(arg,"http")==0 )
				service_http(Conn);
			else
			if( strcmp(arg,"ftp")==0 )
				service_ftp(Conn);
			set_linger(clsock,10);
			close(clsock);del_clsock(clsock);
			break;
		}else
		{
/*
			wcc = write(clsock,req,rcc);
			tcp_relay2(timeout*1000,FromC,clsock,clsock,ToC);
*/
			SockPrintf(ToC,"%s %d %s",VER,NO_GENERIC,request);
		}
	}
EXIT:
	fclose(authout);
	return 0;
}