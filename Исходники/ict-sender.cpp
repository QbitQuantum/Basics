int main(int argc, char *argv[]) {
	//clear the master and temp sets
	FD_ZERO(&master);
	FD_ZERO(&controlSocks);
	
	char c;
	int hSocket;
	uint16_t number=0;
	uint64_t lastAnnounceTime=0;
	Reconnector reconnector;

	set_terminate(terminateFcn);

	void (*prev_fn)(int);
	prev_fn = signal (SIGINT,terminateFcn);
	if (prev_fn==SIG_ERR)
		makeLog(LOG_ERR,"Main: Unable to set termination funtion"); 

	while ((c = getopt (argc, argv, "fvc:")) != -1)
	switch (c) {
	    case 'f':
		fflag = true;
	    break;
	    case 'v':
		vflag = true;
	    break;
	    case 'c':
		configFile = optarg;
	    break;
	    case '?':
		if (optopt == 'c')
		    fprintf (stderr, "Main: Option -%c requires an argument.\n", optopt);
		else if (isprint (optopt))
		    fprintf (stderr, "Main: Unknown option `-%c'.\n", optopt);
		else
		    fprintf (stderr, "Main: Unknown option character `\\x%x'.\n", optopt);
		return 1;
	    default:
		abort ();
	}

	Config config;
	readConfig(config);
	makeLog(LOG_DEBUG,"Read configuration");
	
	if (!pidFile.empty()) {
		makeLog(LOG_DEBUG,"Main: Checking pid file: %s",pidFile.c_str());
		ifstream pidfile(pidFile.c_str());
		if (pidfile.is_open()) {
			char line[20];
			int otherpid;
			pidfile.getline(line,sizeof(line));
			sscanf(line,"%u",&otherpid);
			
			if (kill(otherpid,0)==0) {
				makeLog(LOG_ERR,"Main: Other instance is running: %d",otherpid);
				pidFile="";
				terminate();
			}
			pidfile.close();
		}
	}
	
//	makeLog(LOG_DEBUG,"PID check finished");
	
	if (!fflag) daemon (0,1);
	
	if (!pidFile.empty()) {
		ofstream pidfile;

		pidfile.open(pidFile.c_str());
		pidfile << getpid();
		pidfile << "\n";
		pidfile.close();
	}

	if (listeningArgs.proto.compare("tcp")==0) {
		//get the listener
		if(listener.init(AF_INET, SOCK_STREAM, 0) == -1) {
			makeLog(LOG_ERR,"Listener: Unable to create socket");
			exit(1);
		}
		
		listener.peer.set_in(listeningArgs.host,listeningArgs.port);

		if (listener.connect() < 0) {
			makeLog(LOG_ERR,"Listener: Cannot connect: %s;",strerror(errno));
			reconnector.add(&listener,reconnectListener,NULL);
		} else {
			// add the listener to the master set
			listener.updatefdmax(&fdmax);
			makeLog(LOG_INFO,"Listener: Connected to %s:%d;",listeningArgs.host.c_str(),listeningArgs.port);
		}

		FD_SET(listener.getHandle(), &master);
	} else {
		const bool mcast=((inet_addr(listeningArgs.host.c_str()) & MCAST_MASK) == MCAST_ADDR);

		//get the listener
		if(listener.init(AF_INET, SOCK_DGRAM, 0) == -1) {
			makeLog(LOG_ERR,"Listener: Server-socket() error lol!");
			terminate();
		}

		makeLog(LOG_INFO,"Listener: Server-socket() is OK...");

		//"address already in use" error message
		if(listener.setsockopt(SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		{
			makeLog(LOG_ERR,"Listener: Setsockopt error: %s",strerror(errno));
			terminate();
		}
		makeLog(LOG_INFO,"Listener: Setsockopt() is OK...");
		
		// bind
		listener.local.set_in(listeningArgs.host,listeningArgs.port);

		if(listener.bind() == -1)
		{
			makeLog(LOG_ERR,"Listener: Unable to bind: %s",strerror(errno));
			terminate();
		}
		
		if (mcast) {
			ip_mreq imreq;
			imreq.imr_multiaddr.s_addr = inet_addr(listeningArgs.host.c_str());
			imreq.imr_interface.s_addr = INADDR_ANY; // use DEFAULT interface   // JOIN multicast group on default interface
			int status = listener.setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP, (const void *)&imreq, sizeof(struct ip_mreq));
			makeLog(LOG_INFO,"Listener: Joining multicast %s",listeningArgs.host.c_str());
		}

		makeLog(LOG_INFO,"Listener: ready udp://%s:%d",listeningArgs.host.c_str(),listeningArgs.port);

		// add the listener to the master set
		FD_SET(listener.getHandle(), &master);
		listener.updatefdmax(&fdmax);
	}

	if(control.init(AF_INET, SOCK_DGRAM, 0) == -1) {
		makeLog(LOG_ERR,"Control: Unable to create socket: %s",strerror(errno));
		terminate();
	}

	if (controlArgs.host.empty()) {
		control.local.set_in("",controlArgs.port);

		if (control.bind()>=0) 
			makeLog(LOG_INFO,"Control: Listening on *:%d",controlArgs.port);
		else {
			makeLog(LOG_INFO,"Control: Unable to bind socket for udp port %d: %s",controlArgs.port,strerror(errno));
			exit(0);
		}	
	} else {
		makeLog(LOG_INFO,"Control: NAT mode");
		if (controlArgs.proto.compare("tcp")==0) {
		
		} else {
			control.peer.set_in(controlArgs.host,controlArgs.port);
		}
	}

	#ifdef CONTROL_THREAD
	FD_SET(control.getHandle(), &controlSocks);
	control.updatefdmax(&fdmax);
	#else
	FD_SET(control.getHandle(), &master);
	control.updatefdmax(&fdmax);
	#endif

	if(sender.init(AF_INET, SOCK_DGRAM, 0) == -1) {
		makeLog(LOG_ERR,"Streamer: Unable to create socket: %s",strerror(errno));
		terminate();
	}

	if (streamingArgs.proto.compare("tcp")==0) {
		
	} else {
		sender.peer.set_in(streamingArgs.host,streamingArgs.port);
		makeLog(LOG_INFO,"Streamer: Peer port was set up %s:%d",streamingArgs.host.c_str(),streamingArgs.port);
	}

	#ifdef CONTROL_THREAD
	FD_SET(sender .getHandle(), &controlSocks);
	sender.updatefdmax(&fdmax);
	#else
	FD_SET(sender.getHandle(), &master);
	sender.updatefdmax(&fdmax);
	#endif

	if (!listeningArgs.copyHost.empty()) {
		if(copier.init(AF_INET, SOCK_DGRAM, 0) == -1) {
			makeLog(LOG_ERR,"Copier: Unable to create socket: %s",strerror(errno));
		}

		copier.peer.set_in(listeningArgs.copyHost,listeningArgs.copyPort);
		makeLog(LOG_INFO,"Copier: Resend data to: %s",copier.peer.toString().c_str());

		FD_SET(copier.getHandle(), &master);
		copier.updatefdmax(&fdmax);
	}

	openlog("ict-receiver", LOG_PID|LOG_CONS, LOG_USER);

	sendingSuspended=streamingArgs.suspendOnStart;

        if (int errcode=pthread_create(&cleaningThread,NULL,&cleaningFcn,&cleaningArgs)) {
            makeLog(LOG_ERR,"Cleaner: Unable to create thread: %s",strerror(errno));
        }

	if (streamingArgs.bitrate) {
		if(pipe(mypipe) < 0) {
			makeLog(LOG_ERR,"Streamer: Unable to create pipe %s",strerror(errno));
		}
	
		if (int errcode=pthread_create(&streamingThread,NULL,&streamingFcn,&streamingArgs)) {
			makeLog(LOG_ERR,"Streamer: Unable to create thread: %s",strerror(errno));
		}
        }

        if (int errcode=pthread_create(&keepingThread,NULL,&keepingFcn,NULL)) {
            makeLog(LOG_ERR,"Keeper: Unable to create thread: %s",strerror(errno));
        }

	#ifdef CONTROL_THREAD
	if (int errcode=pthread_create(&controlThread,NULL,&controlThreadFcn,&controlArgs)) {
		makeLog(LOG_ERR,"Control: Unable to create thread: %s",strerror(errno));
	}
	#endif

	sendControl("START");

	timeval timeout={10,0}; //sec,usec

	// loop
	for(;;) {
		// copy it
		fd_set read_fds = master;
		int readCnt=select(fdmax+1, &read_fds, NULL, NULL, &timeout);

		if(  readCnt == -1  ) {
			makeLog(LOG_ERR,"Main: select error: %s",strerror(errno));
			exit(1);
		}
		
		reconnector.tryReconnect(10);

		if (  readCnt > 0  ) {
			//run through the existing connections looking for data to be read
			for(hSocket = 0; hSocket <= fdmax; hSocket++) {
				if(FD_ISSET(hSocket, &read_fds))
				{ // we got one...
					if(listener.handles(hSocket)) {
						// buffer for client data
						ictDatagram_t ictDatagram;
					
						int recvlen = listener.recv(ictDatagram.data(), listeningArgs.mtu, 0);

						if (recvlen>0) {
							if (copier.inited()) {
								copier.write(ictDatagram.data(),recvlen);
							}
					
							ictDatagram.setDataLength(recvlen);
							if (!sendingSuspended) {
								ictDatagram.setTime(getMNow());
								ictDatagram.setNumber(number);

								pushDatagram (ictDatagram);
								if (streamingArgs.bitrate) {
//									makeLog(LOG_DEBUG,"Writenumber: %u",number);

									write(mypipe[1],&number,sizeof(number));
//									outQueue.push_back	( number );
								} else {
									int sentcount=sender.send(ictDatagram,ictDatagram.size(),0);
								}

								number++;
							} else {//if suspended
								uint64_t now=getMNow();
								if (now-lastAnnounceTime>30*1000) {
									sender.send("UU",2,0);
									lastAnnounceTime=now;
								}
							} //if suspended
						} //if recvLen>0
						else if (recvlen==0){//Client must be reconnected!!!!
							if (listeningArgs.proto.compare("tcp")==0) {
									FD_CLR(listener.getHandle(),&master);
									if (listener.isConnected()) {
										listener.reinit();
									}
/*							
									if (listener.connect()==0) {
										makeLog(LOG_INFO,"Listener: Connected");
									} else {
										makeLog(LOG_INFO,"Listener: Reconnect failed");
										sleep(10);
									}
*/
									reconnector.add(&listener,reconnectListener,NULL);
									makeLog(LOG_INFO,"Listener: Disconnected");
							}
						} //if recvlen==0
					} //if sock is listener
					#ifndef CONTROL_THREAD
					if (control.handles(hSocket)) {
						char cmsg[1500];
						int recvlen = control.recv((void*)cmsg,sizeof(cmsg),0);

						if (recvlen>0) {
							makeLog(LOG_DEBUG,"Processing control from main");
							controlStr.append(cmsg,recvlen);
							processControls(controlStr,control);
						}
					}

					if (sender.handles(hSocket)) {
						char cmsg[1500];
						int recvlen = sender.recv(cmsg,sizeof(cmsg),0);

						if (recvlen>0) {
							makeLog(LOG_DEBUG,"Processing control from main");
							controlStr.append(cmsg,recvlen);
							processControls(controlStr,sender);
						}
					}
					#endif
				}
			}//for
		}//if readCnt>0
	}

	closelog();
	return 0;
}