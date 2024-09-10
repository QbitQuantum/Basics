void udp_relayX(Connection *Conn,int csc,int csv[])
{	int svsock;
	int sockv[1024],readyv[1024],sx; /* must be lt/eq FD_SESIZE */
	int nsock; /* number of clients */
	CStr(buff,0x8000);
	int rcc,wcc;
	int nready;
	CStr(ihost,64);
	int iport;
	CStr(svhost,64);
	int svport;
	const char *clhost;
	int clport;
	UDP_Assoc *ua;
	UDP_Assoc *udpav[MAXASSOC*4]; /**/
	int udpxv[MAXASSOC*4];
	int lastrelay,idle;
	const char *aaddr;
	int svportmap;
	int portnumv[64];
	int csi;
	int istcp[MAXASSOC];
	int ccc = 0; /* tcp clients */
	int usocks = 0; /* UDP SOCKS */
	int update = 0;
	int ai;

	/* is this necessary or effective ? */
	socks_addservers();

	if( MAXASSOC < UDPRELAY_MAXASSOC ){
		UDPRELAY_MAXASSOC = MAXASSOC;
	}
	sv1log("MAXIMA=udprelay:%d (max. udp assoc.)\n",UDPRELAY_MAXASSOC);

	if( (aaddr = gethostaddr(DST_HOST)) == NULL ){
		sv1log("#### ERROR: bad destination host [%s]\n",DST_HOST);
		return;
	}
	strcpy(svhost,aaddr);
	svport = DST_PORT;
	svportmap = DFLT_PORTMAP;
	if( svportmap ){
		/* get port numbers of incoming ports ... */
		for( csi = 0; csi < csc; csi++ ){
			portnumv[csi] = sockPort(csv[csi]) + svportmap;
			portnumv[csi] &= ~0x40000000; /* clear IS_PORTMAP */
		}
	}

	expand_fdset(MAXASSOC);
	uassocv = (UDP_Assoc**)calloc(MAXASSOC+1,sizeof(UDP_Assoc*));
	for( csi = 0; csi < csc; csi++ )
		sockv[csi] = csv[csi];
	for( csi = 0; csi < csc; csi++ )
		istcp[csi] = !isUDPsock(sockv[csi]);
	nsock = 0;
	lastrelay = 0;

	for(;;){
UPDATE:
		if( update ){
			int ai;
			update = 0;
			ccc = 0;
			for( ai = 0; ua = uassocv[ai]; ai++ ){
				if( ua->ua_clpriv ){
				udpxv[csc + ccc] = ai;
				udpav[csc + ccc] = ua;
				sockv[csc + ccc++] = ua->ua_clsock;
				}
			}
			nsock = 0;
			for( ai = 0; ua = uassocv[ai]; ai++ ){
				udpxv[csc+ccc + nsock] = ai;
				udpav[csc+ccc + nsock] = ua;
				sockv[csc+ccc + nsock++] = ua->ua_svsock;
			}
			usocks = 0;
			for( ai = 0; ua = uassocv[ai]; ai++ ){
				int ns = csc+ccc+nsock;
				if( 0 <= ua->ua_svSOCKS ){
					udpxv[ns+usocks] = ai;
					udpav[ns+usocks] = ua;
					sockv[ns+usocks] = ua->ua_svSOCKS;
					usocks++;
				}
			}
		}
		/*
		nready = PollIns(10*1000,csc+nsock+ccc,sockv,readyv);
		*/
		nready = PollIns(10*1000,csc+ccc+nsock+usocks,sockv,readyv);
		if( nready < 0 ){
			/*
			sv1log("UDPRELAY: ABORT PollIns(%d) = %d\n",nready);
			*/
			sv1log("UDPRELAY: ABORT PollIns(%d+%d+%d+%d)=%d\n",
				csc,ccc,nsock,usocks,nready);
			for( ai = 0; ai < csc+ccc+nsock+usocks; ai++ ){
				sv1log("[%2d] %d\n",ai,sockv[ai]);
			}
			break;
		}
		if( nready == 0 ){
			idle = time(0) - lastrelay;
			if( SERVER_TIMEOUT && lastrelay )
			if( SERVER_TIMEOUT < idle){
				sv1log("UDPRELAY: SERVER TIMEOUT (idle %ds)\n",
					idle);
				break;
			}
			killTimeouts(uassocv);
			/*
			nsock = getsocks(uassocv,&sockv[csc]);
			*/
			update = 1;
			continue;
		}
		lastrelay = time(0);

		for( sx = 0; sx < csc; sx++ )
		if( 0 < readyv[sx] && istcp[sx] ){
			CStr(local,256);
			CStr(remote,256);
			int clsk;
			strcpy(remote,"*:*");
			strcpy(local,"*:*");
			clsk = VSocket(Conn,"ACPT/",sockv[sx],AVStr(local),AVStr(remote),"");
/*
			setNonblockingIO("UDPRELAY-CL",clsk,1);
*/
			SetNonblockingIO("UDPRELAY-CL",clsk,1);
			iport = getpeerAddr(clsk,AVStr(ihost));
			if( clsk <= 0 || iport <= 0 ){
				sv1log("UDPRELAY: accept() errno=%d\n",errno);
				continue;
			}
			if( svportmap ){
				svport = portnumv[sx];
			}
			ua = newUA(Conn,uassocv,ihost,iport,svhost,svport);
			ua->ua_clsock = clsk;
			ua->ua_clpriv = 1;
			update = 1;
		}else
		if( 0 < readyv[sx] ){
			rcc = recvFromA(sockv[sx],AVStr(buff),sizeof(buff),0,AVStr(ihost),&iport);
			if( rcc <= 0 ){
				sv1log("UDPRELAY: recv() == 0, errno=%d\n",errno);
				break;
			}
			if( svportmap ){
				svport = portnumv[sx];
			}
			ua = findUAbysrc(uassocv,ihost,iport,svhost,svport);
			if( ua == NULL ){
				ua = newUA(Conn,uassocv,ihost,iport,svhost,svport);
				if( ua == NULL ){
					continue;
				}
				ua->ua_clsock = sockv[sx];
				if( ua->ua_svsock < 0 )
					continue;
				/*
				nsock = getsocks(uassocv,&sockv[csc]);
				*/
				update = 1;
			}
			toServ(ua,buff,rcc,svhost,svport,ihost,iport);
			/*
			ua->ua_mtime = time(0);
			ua->ua_upcnt++;
			ua->ua_upbytes += rcc;
			if( UDPRELAY_RPORT_FIX )
				wcc = Send(ua->ua_svsock,buff,rcc);
			else	wcc = SendTo(ua->ua_svsock,buff,rcc,svhost,svport);
			Verbose("TO SERV#%d: %s:%d %3d> %s:%d\n",
				ua->ua_id,ihost,iport,rcc,svhost,svport);
			*/
			if( nready == 1 )
				continue;
		}

		for( sx = csc; sx < csc+ccc; sx++ )
		if( 0 < readyv[sx] ){
			rcc = recv(sockv[sx],buff,sizeof(buff),0);
			if( rcc <= 0 ){
				int ux = getUAx(uassocv,udpav[sx]);
				if( ux < 0 ){
					sv1log("## delUA-CL(%d)?\n",ux);
					continue;
				}
				delUA(uassocv,ux,"TCPreset-CL",1);
				/* here udpxv[] becomes inconsistent */
				update = 1;
			}else{
				ua = udpav[sx];
				toServ(ua,buff,rcc,svhost,svport,NULL,0);
			}
		}

		/*
		for( sx = csc; sx < csc+nsock; sx++ ){
		*/
		for( sx = csc+ccc; sx < csc+ccc+nsock; sx++ ){
			if( readyv[sx] <= 0 )
				continue;
			ua = udpav[sx];
			svsock = sockv[sx];

			if( 0 <= ua->ua_svSOCKS )
			rcc = RecvFrom(svsock,buff,sizeof(buff),AVStr(ihost),&iport);
			else
			rcc = recvFromA(svsock,AVStr(buff),sizeof(buff),0,AVStr(ihost),&iport);

			if( rcc <= 0 ){
				if( ua->ua_svtcp ){
					int ux = getUAx(uassocv,udpav[sx]);
					if( ux < 0 ){
						sv1log("## delUA-SV(%d)?\n",ux);
						continue;
					}
					delUA(uassocv,ux,"TCPreset-SV",1);
					update = 1;
				}
				readyv[sx] = -1;
				continue;
			}

			/*
			ua = findUAbysock(uassocv,svsock);
			*/
			ua->ua_mtime = time(0);
			ua->ua_downcnt++;
			ua->ua_downbytes += rcc;
			clhost = ua->ua_clhost;
			clport = ua->ua_clport;
			/*
			wcc = SendTo(ua->ua_clsock,buff,rcc,clhost,clport);
			*/
			wcc = sendToA(ua->ua_clsock,buff,rcc,0,clhost,clport);

			Verbose("TO CLNT#%d: %s:%d <%-3d %s:%d\n",
				ua->ua_id,clhost,clport,rcc,ihost,iport);
		}
		for( sx = csc+ccc+nsock; sx < csc+ccc+nsock+usocks; sx++ ){
			int ux;
			if( readyv[sx] <= 0 )
				continue;
			ua = udpav[sx];
			ux = getUAx(uassocv,udpav[sx]);
			if( ux < 0 ){
				sv1log("## delUA-CTL(%d)?\n",ux);
				continue;
			}
			sv1log("## detected disconn. by SOCKS CTL [%d]\n",ux);
			delUA(uassocv,ux,"SOCKSCTLreset-SV",1);
			update = 1;
		}
	}
}