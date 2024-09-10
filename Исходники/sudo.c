int service_sudo(Connection *Conn,int svsock,int svport){
	int fc;
	int fv[2];
	int rv[2];
	CStr(req,1024);
	CStr(com,1024);
	CStr(arg,1024);
	CStr(a1,1024);
	CStr(a2,1024);
	CStr(a3,1024);
	const char *dp;
	CStr(resp,1024);
	int tsock = -1;
	int clsock;
	int isUDP;
	int rcc;
	int fd;
	CStr(local,MaxHostNameLen);
	CStr(remote,MaxHostNameLen);
	CStr(opts,MaxHostNameLen);
	CStr(clhost,128);
	int clport;

	gethostName(svsock,AVStr(local),"%A");
	sv1log("==SU START uid=%d/%d sock=%d port=%d udp=%d [%s]\n",
		getuid(),geteuid(),svsock,svport,isUDPsock(svsock),local);

	if( svport == 0 ){
		sprintf(local,"%s/sudo/port/P%s",DELEGATE_DGROOT,portSUDO);
		unlink(local);
		svsock = server_open_un("SUDO",AVStr(local),32);
		sv1log("==SU sock[%d] %s\n",svsock,local);
		if( svsock < 0 ){
			return -1;
		}
		if( geteuid() == 0 ){
			int omode = File_mod(local);
			/* set the owner of the socket to the one in OWNER */
			chmodShared(local);
			chmod(local,omode|0660);
		}
	}


	if( isUDP = isUDPsock(svsock) ){
	}else{
	}

	if( isUDP ){
		tsock = server_open_un("SUDO",AVStr(local),32);
		sv1log("---> tsock:%d [%s]\n",tsock,local);
	}else{
		tsock = svsock;
	}

	fc = 1;
	fv[0] = tsock;
	if( 0 <= isPrivateSUDO ){
		fc = 2;
		fv[1] = isPrivateSUDO;
	}

	for(;;){
		/*
		if( PollIn(tsock,0) <= 0 ){
			break;
		}
		*/
		if( PollIns(0,fc,fv,rv) <= 0 ){
			sv1log("==SU EXIT: poll error\n");
			break;
		}
		if( fc == 2 ){
			if( rv[1] ){
				sv1log("==SU EXIT: parent died\n");
				break;
			}
			if( rv[0] == 0 )
				continue;
		}

		clsock = tsock;
		if( !isUDP && !IsConnected(tsock,NULL) ){
			clsock = ACCEPT1(tsock,1,-1,10,AVStr(clhost));
			if( clsock < 0 ){
				msleep(100);
				continue;
			}
		}
		rcc = RecvFrom(clsock,req,sizeof(req)-1,AVStr(clhost),&clport);
		if( rcc <= 0 ){
			sv1log("==SU %d %d rcc=%d\n",tsock,clsock,rcc);
			if( clsock != tsock ){
				close(clsock);
				continue;
			}else{
				sv1log("==SU EXIT: read error\n");
				break;
			}
		}
		setVStrEnd(req,rcc);
		dp = wordScan(req,com);
		if( *dp == ' ' )
			textScan(dp+1,arg);
		else	lineScan(dp,arg);
		dp = wordScan(arg,a1);
		dp = wordScan(dp,a2);
		lineScan(dp,a3);
		sv1log("==SU Q[%s][%s]\n",com,arg);
		putLoadStat(ST_ACC,1);
		putLoadStat(ST_DONE,1);
		put_svstat();
		incRequestSerno(Conn);

		if( strcaseeq(com,"QUIT") ){
			if( isUDP ){
				continue;
			}else{
				sv1log("==SU EXIT: by QUIT command\n");
				break;
			}
		}
		if( strcaseeq(com,"PAM") ){
			doPAM(clsock,clhost,clport,tsock,arg);
			continue;
		}
		if( strcaseeq(com,"BIND") ){
			doBind(clsock,clhost,clport,tsock,arg);
			continue;
		}
/*
		if( strcaseeq(com,"STDERR") ){
			sv1log("==SU receiving @fd[%d]\n",usock);
			fd = recvFd(usock);
 fprintf(stderr,"---- STDERR %d -> %d\n",usock,fd);
			if( 0 <= fd ){
				dup2(fd,fileno(stderr));
 fprintf(stderr,"---- STDERR %d dup2\n",fd);
			}
		}
*/
	}
	return 0;
}