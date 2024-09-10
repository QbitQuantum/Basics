int main(int argc, char** argv) {
	{
		char cwd[255];
		if(getcwd(cwd,255)==NULL) throw runtime_error(strerror(errno));
		rootDir=cwd;
	}
	string listen="0.0.0.0:80";
	string tmpDir;
	int threads=-1;
	vector<string> cxxopts;
	vector<moduleLoad> modules;
	bool f0rk=false;
	bool reusePort=true;
	bool setAffinity=false;
	bool debug=false;
	try {
		parseArgs(argc, argv,
				[&](char* name, const std::function<char*()>& getvalue)
				{
					if(name==NULL) goto help;
					if(strcmp(name,"r")==0) {
						rootDir=getvalue();
					} else if(strcmp(name,"c")==0) {
						cxxopts.push_back(getvalue());
					} else if(strcmp(name,"g")==0) {
						cppsp::gxx=getvalue();
					} else if(strcmp(name,"l")==0) {
						listen=getvalue();
					} else if(strcmp(name,"t")==0) {
						threads=atoi(getvalue());
					} else if(strcmp(name,"m")==0) {
						modules.push_back({getvalue(),false,false});
					} else if(strcmp(name,"M")==0) {
						modules.push_back({getvalue(),true,false});
					} else if(strcmp(name,"f")==0) {
						f0rk=true;
					} else if(strcmp(name,"s")==0) {
						reusePort=false;
					} else if(strcmp(name,"a")==0) {
						setAffinity=true;
					} else if(strcmp(name,"b")==0) {
						tmpDir=getvalue();
					} else if(strcmp(name,"d")==0) {
						debug=true;
					} else {
					help:
						fprintf(stderr,"usage: %s [options]...\noptions:\n"
						"\t-l <host:port>: listen on specified host:port (default: 0.0.0.0:80)\n"
						"\t-g <option>: specify the C++ compiler (default: g++)\n"
						"\t-c <option>: specify a compiler option to be passed to g++\n"
						"\t-m <path>: load a cppsp module (path is relative to root)\n"
						"\t-M <path>: load a cppsp module into the host (path is absolute or relative to CWD; if relative then \"./\" must be used)\n"
						"\t-r <root>: set root directory (must be absolute) (default: $(pwd))\n"
						"\t-t <threads>: # of worker processes/threads to start up (default: sysconf(_SC_NPROCESSORS_CONF))\n"
						"\t-f: use multi-processing (forking) instead of multi-threading (pthreads)\n"
						"\t-a: automatically set cpu affinity of the created worker threads/processes\n"
						"\t-b <path>: the directory in which temporary binaries are stored\n",argv[0]);
						exit(1);
					}
				});
	} catch(exception& ex) {
		printerr("error: %s\nspecify -? for help",ex.what());
		return 1;
	}
	printinfo("specify -? for help");
	auto i=listen.find(':');
	if(i==string::npos) throw runtime_error("expected \":\" in listen");
	
	int cpus=(int)sysconf(_SC_NPROCESSORS_CONF);
	if(threads<0)threads=cpus;
	if(setAffinity) {
		if(threads > cpus && (threads%(int)sysconf(_SC_NPROCESSORS_CONF) != 0)) {
			printerr("warning: cpu affinity is to be set; thread count larger than and not divisible by cpu count");
		}
	}
	
	EndPoint* ep=NULL;
	struct {
		bool& reusePort;
		void operator()(int s) {
			int optval = 1;
			reusePort=(setsockopt(s, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval))==0);
		}
	} initsock {reusePort};
	if(reusePort)
		listensock.bind(listen.substr(0,i).c_str(),
			listen.substr(i + 1, listen.length() - i - 1).c_str(), AF_UNSPEC, SOCK_STREAM,0,0,&initsock);
	else
		listensock.bind(listen.substr(0,i).c_str(),
			listen.substr(i + 1, listen.length() - i - 1).c_str(), AF_UNSPEC, SOCK_STREAM);
	if(reusePort) {
		printinfo("using SO_REUSEPORT");
		ep=listensock.getLocalEndPoint();
	} else {
		printerr("NOT using SO_REUSEPORT");
		listensock.listen(CPPSP_LISTEN_BACKLOG);
	}
	
	//p.add(listensock);
	PRINTSIZE(CP::Socket);
	PRINTSIZE(cppspServer::handler);
	PRINTSIZE(handler1);
	if(f0rk) printinfo("starting %i processes",threads);
	else printinfo("starting %i threads",threads);
	workerThread* th=(workerThread*)new char[sizeof(workerThread)*threads];
	for(int i=0;i<threads;i++) {
		int cpu=i%cpus;
		Socket* newsock;
		if(reusePort) {
			newsock=new Socket(listensock.addressFamily, listensock.type, listensock.protocol);
			int optval = 1;
			assert(setsockopt(newsock->handle, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval))==0);
			newsock->bind(*ep);
			newsock->listen(CPPSP_LISTEN_BACKLOG);
		} else {
			newsock=new Socket(f0rk ? listensock.handle : dup(listensock.handle),
				listensock.addressFamily, listensock.type, listensock.protocol);
		}
		workerThread& tmp=*(new (th+i) workerThread(*newsock));
		tmp.cpu=(setAffinity?cpu:-1);
		newsock->release();
		tmp.srv.mgr->cxxopts=cxxopts;
		tmp.srv.mgr->tmpDir=tmpDir;
		tmp.srv.mgr->debug=debug;
		tmp.modules=modules;
		tmp.srv.threadID=i;
		if(threads==1) {
			thread1(&tmp);
			return 0;
		}
		if(f0rk) {
			pid_t pid=fork();
			if(pid==0) {
				tmp.pid=getpid();
				srand(int(tmp.pid)^(int)time(NULL));
				thread1(&tmp);
				return 0;
			} else if(pid>0) {
				tmp.pid=pid;
				//delete newsock;
			} else {
				perror("fork");
				return 1;
			}
		} else {
			if (pthread_create(&tmp.thread, NULL, thread1, &tmp) != 0) {
				throw runtime_error(strerror(errno));
			}
		}
	}
	if(f0rk) {
		static workerThread* _threads;
		static int _threadcount;
		struct sig_handler
		{
			static void a(int sig) {
				for(int i=0;i<_threadcount;i++) {
					kill(_threads[i].pid, 9);
				}
				exit(0);
			}
		};
		_threads=th;
		_threadcount=threads;
		struct sigaction sa;
		sa.sa_handler = &sig_handler::a;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGTERM, &sa, NULL);
		sigaction(SIGSEGV, &sa, NULL);
	}
	union {
		int status1;
		void* status2;
	};
	int ret=0;
	if(f0rk) while(true) {
		pid_t child=wait(&status1);
		if(child<=0)return ret;
		printf("child %i exited with code %i\n",(int)child,status1);
		if(status1!=0)ret=status1;
	} else for(int i=0;i<threads;i++)
		pthread_join(th[i].thread,&status2);
}