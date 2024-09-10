void seperate_work_model()
{
	char *listen = argv[2];
	bool result;
	int port;
#ifdef KSOCKET_UNIX
	if (strncasecmp(listen,"unix:",5)==0) {
		port = 0;
		listen += 5;
		result = ls.listen(listen);
		if(!result){
			fprintf(stderr,"cann't listen unix socket [%s]\n",listen);
			exit(1);
		}
		printf("success listen to unix socket [%s]\n",listen);
	} else  {
#endif
		if(*listen==':'){
			port = atoi(listen+1);
			result = ls.listen(port,NULL);
		} else {
			char *p = strchr(listen,':');
			if (p==NULL) {
				seperate_usage();
				exit(1);
			}
			*p = '\0';
			port = atoi(p+1);
			result = ls.listen(port,listen);
		}
		if(!result){
			fprintf(stderr,"cann't listen to port [%d]\n",port);
			exit(1);
		}
		printf("success listen to port [%d]\n",port);
#ifdef KSOCKET_UNIX
	}
#endif
	int childs = atoi(argv[3]);
	if (childs<=0) {
		seperate_usage();
		exit(1);
	}
	int total_successed = 0;
	argv+=4;
	for(int i=0;i<childs;i++){
		if(!::createProcess(&ls, NULL, argv, NULL, RDSTD_INPUT)){
			fprintf(stderr,"cann't create process\n");
			break;
		}
		total_successed ++;
		pid_t pid = ls.process.stealPid();
		printf("succss create child pid=%d\n",pid);
		processes.insert(pair<pid_t,bool>(pid,true));
	}
	if (total_successed==0) {
		return;
	}
#ifdef _WIN32
	//sleep(1);
	watch_process(NULL);
#else
	void childExsit();
	for (;;) {
		childExsit();
		sleep(1);
	}
#endif
}