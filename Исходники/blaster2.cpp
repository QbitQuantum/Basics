int main ( int argc , char *argv[] ) {
	// let's ensure our core file can dump
	struct rlimit lim;
	lim.rlim_cur = lim.rlim_max = RLIM_INFINITY;
	if ( setrlimit(RLIMIT_CORE,&lim) )
		log("blaster::setrlimit: %s", mstrerror(errno) );

	//g_conf.m_maxMem = 500000000;

	// init our table for doing zobrist hashing
	if ( ! hashinit() ) {
		log("blaster::hashinit failed" ); return 1; }

	// init the memory class after conf since it gets maxMem from Conf
	//if ( ! g_mem.init ( 20000000 ) ) {
	//	log("blaster::Mem init failed" ); return 1; }
	//g_mem.m_maxMem = 200000000;
	// start up log file
	if ( ! g_log.init( "/tmp/blasterLog" )        ) {
		log("blaster::Log open /tmp/blasterLog failed" ); return 1; }

	// get dns ip from /etc/resolv.conf
	g_conf.m_dnsIps[0] = 0;
	FILE *fd = fopen ( "/etc/resolv.conf" , "r" );
	if ( ! fd ) {
		log("blaster::fopen: /etc/resolve.conf %s",
		    mstrerror(errno)); return 1; }

	char tmp[1024];
	while ( fgets ( tmp , 1024 , fd ) ) {
		// tmp buf ptr
		char *p = tmp;
		// skip comments
		if ( *p == '#' ) continue;
		// skip nameserver name
		if ( ! isdigit(*p) ) while ( ! isspace ( *p ) ) p++ ;
		// skip spaces
		while ( isspace ( *p ) ) p++;
		// if this is not a digit, continue
		if ( ! isdigit(*p) ) continue;
		// get ip
		g_conf.m_dnsIps[0] = atoip ( p , gbstrlen(p) );
		// done
		break;
	}
	fclose ( fd );


	// if no dns server found, bail
	if ( g_conf.m_dnsIps[0] == 0 ) {
		log("blaster:: no dns ip found in /etc/resolv.conf");return 1;}

	// hack # of dns servers
	g_conf.m_numDns         = 1;
	g_conf.m_dnsPorts[0]    = 53;
	//g_conf.m_dnsIps  [0]    = atoip ( "192.168.0.1", 11 );
	//g_conf.m_dnsClientPort  = 9909;
	g_conf.m_dnsMaxCacheMem = 1024*10;
	// hack http server port to -1 (none)
	//g_conf.m_httpPort           = 0;
	g_conf.m_httpMaxSockets     = 200;
	//g_conf.m_httpMaxReadBufSize = 102*1024*1024;
	g_conf.m_httpMaxSendBufSize = 16*1024;
	//g_conf.m_httpMaxDownloadSockets = 200;

	if ( argc != 4 && argc != 5 && argc !=6 ) {
	printUsage:
		fprintf(stderr,"USAGE: blaster [fileOfUrls | -r<num random words><server>] [maxNumThreads] [wait in ms] " 
		    "<lines to skip> <string to append>\n");
		fprintf(stderr,"USAGE: examples:\n");
		fprintf(stderr,"USAGE:  ./blaster queries.fromlog 10 1\n");
		fprintf(stderr,"USAGE:  ./blaster -r3http://www.gigablast.com/index.php?q= 1 100\n");
		return 1; 
	}

	fprintf(stderr,"Logging to /tmp/blasterLog\n");

	// init the loop
	if ( ! g_loop.init() ) {
		log("blaster::Loop init failed" ); return 1; }
	// . then dns client
	// . server should listen to a socket and register with g_loop
	if ( ! g_dns.init(6000)        ) {
		log("blaster::Dns client init failed" ); return 1; }
	// . then webserver
	// . server should listen to a socket and register with g_loop
	for(int32_t i = 0; i < 50; i++) {
		if ( ! g_httpServer.init( 8333 + i, 9334+i ) ) {
			log("blaster::HttpServer init failed" ); 
			//return 1; 
		}
		else break;
	}
	// set File class
	char *fname = argv[1];
	int32_t fnameLen = gbstrlen(fname);
	int32_t fileSize = 0;
	int32_t bufSize = 0;
	char *buf = NULL;
	int32_t  n = 0;

	//should we generate random queries?
	if(fnameLen > 2 && fname[0] == '-' && fname[1] == 'r') {
		char *p = fname + 2;
		s_numRandWords = atoi( p );
		while(is_digit(*p)) p++;
		getWords();
		
		if(*p == '\0') goto printUsage;
		s_server = p;
		log("blaster server is %s", s_server);
		//		char x[1024];
		// 		while(1) {
		// 			int32_t l = getRandomWords(x, x + 1024, s_numRandWords);
		// 			*(x + l) = '\0';
		// 			log("blaster: %s", x);
		// 		}
		//		exit(1);
	}
	else { //it is a real file
		File f;
		f.set ( fname );

		// open file
		if ( ! f.open ( O_RDONLY ) ) {
			log("blaster::open: %s %s",fname,mstrerror(g_errno)); 
			return 1; 
		}

		// get file size
		fileSize = f.getFileSize() ;

		// store a \0 at the end
		bufSize = fileSize + 1;

		// make buffer to hold all
		buf = (char *) mmalloc ( bufSize , "blaster" );
		if ( ! buf) {log("blaster::mmalloc: %s",mstrerror(errno));return 1;}

		//char *bufEnd = buf + bufSize;

		// set s_p
		s_p    = buf;
		s_pend = buf + bufSize - 1;

		// read em all in
		if ( ! f.read ( buf , fileSize , 0 ) ) {
			log("blaster::read: %s %s",fname,mstrerror(g_errno));return 1;}

		// change \n to \0
		//char *p = buf;
		for ( int32_t i = 0 ; i < bufSize ; i++ ) {
			if ( buf[i] != '\n' ) continue;
			buf[i] = '\0';
			n++;
		}

		f.close();
	}
	// log a msg
	log(LOG_INIT,"blaster: read %"INT32" urls into memory", n );

	int32_t linesToSkip = 0;
	if ( argc >=  5 ) {
		linesToSkip = atoi ( argv[4] );
		log (LOG_INIT,"blaster: skipping %"INT32" urls",linesToSkip);
	}
	for ( int32_t i = 0; i < linesToSkip && s_p < s_pend; i++ )
		s_p += gbstrlen(s_p) + 1;
	
	if ( argc == 6 ) {
		int32_t len  = gbstrlen ( argv[5] );
		if ( len > 512 )
			len = 512;
		strncpy ( s_append , argv[5] , gbstrlen (argv[5]) );
	}
	else
		s_append[0] = '\0';

	// get min time bewteen each spider in milliseconds
	s_wait = atoi( argv[3] );

	// # of threads
	s_maxNumThreads = 1;
	s_maxNumThreads = atoi ( argv[2] );

	s_portSwitch = 0;
	//if ( argc == 4 ) s_portSwitch = 1;
	//else             s_portSwitch = 0;

	// start our spider loop
	//startSpidering( );

	// wakeup wrapper every X ms
	g_loop.registerSleepCallback ( s_wait , NULL , sleepWrapper );

	//msg10.addUrls ( uu , gbstrlen(uu)+1, NULL,0,time(0),4,true,NULL,NULL);
	// . now start g_loops main interrupt handling loop
	// . it should block forever
	// . when it gets a signal it dispatches to a server or db to handle it
	if ( ! g_loop.runLoop()    ) {
		log("blaster::runLoop failed" ); return 1; }
	// dummy return (0-->normal exit status for the shell)
	return 0;
}