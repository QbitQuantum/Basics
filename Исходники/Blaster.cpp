void Blaster::runBlaster(char *file1,char *file2,
			 int32_t maxNumThreads, int32_t wait, bool isLogFile,
			 bool verbose,bool justDisplay,
			 bool useProxy ,
			 bool injectUrlWithLinks ,
			 bool injectUrl ) {
	if (!init())
		return;
	m_blasterDiff=true;
	if (!file2)
		m_blasterDiff=false;
	
	// set File class
	File f1;
	f1.set ( file1 );

	// open files
	if ( ! f1.open ( O_RDONLY ) ) {
		log("blaster:open: %s %s",file1,mstrerror(g_errno)); 
		return; 
	}

	// get file size
	int32_t fileSize1 = f1.getFileSize() ;
	// store a \0 at the end
	int32_t m_bufSize1 = fileSize1 + 1;

	m_doInjectionWithLinks = injectUrlWithLinks;
	m_doInjection = injectUrl;

	// make buffers to hold all
	m_buf1 = (char *) mmalloc ( m_bufSize1 , "blaster1" );
	if ( ! m_buf1) {
		log("blaster:mmalloc: %s",mstrerror(errno));
		return;
	}

	//char *bufEnd = buf + bufSize;

	// set m_p1
	m_p1    = m_buf1;
	m_p1end = m_buf1 + m_bufSize1 - 1;

	// read em all in
	if ( ! f1.read ( m_buf1 , fileSize1 , 0 ) ) {
		log("blaster:read: %s %s",file1,mstrerror(g_errno));
		return;
	}

	// change \n to \0
	//char *p = buf;
	int32_t  n = 0;
	for ( int32_t i = 0 ; i < m_bufSize1 ; i++ ) {
		if ( m_buf1[i] != '\n' ) continue;
		m_buf1[i] = '\0';
		n++;
	}


	if (m_blasterDiff){
		File f2;
		f2.set ( file2 );
		if ( ! f2.open ( O_RDONLY ) ) {
			log("blaster:open: %s %s",file2,mstrerror(g_errno)); 
			return; 
		}
		int32_t fileSize2 = f2.getFileSize() ;
		int32_t m_bufSize2 = fileSize2 + 1;
		m_buf2 = (char *) mmalloc ( m_bufSize2 , "blaster2" );
		if ( ! m_buf2) {
			log("blaster:mmalloc: %s",mstrerror(errno));
			return;
		}
		// set m_p2
		m_p2    = m_buf2;
		m_p2end = m_buf2 + m_bufSize2 - 1;
		if ( ! f2.read ( m_buf2 , fileSize2 , 0 ) ) {
			log("blaster:read: %s %s",file2,mstrerror(g_errno));
			return;
		}
		int32_t m=0;
		for ( int32_t i = 0 ; i < m_bufSize2 ; i++ ) {
			if ( m_buf2[i] != '\n' ) continue;
			m_buf2[i] = '\0';
			m++;
		}
		// Working on only the least number of urls from both files, 
		//because we need to work in pairs
		if (m<n) n=m;
		else m=n;
		m_totalUrls=n;

		// should we print out all the logs?
		m_verbose=verbose;
		// Should we use the proxy for getting the first Doc
		m_useProxy=useProxy;
		// Should we just display the not present links and not fetch
		// the page to see if they are actually present ?
		m_justDisplay=justDisplay;
	}
	else{
		m_isLogFile=isLogFile;
		
		/*if reading a gigablast log file, find the lines that have 
		  GET and POST commands for search, and register a sleep
		  callback for those lines with sleepWrapperLog*/
		if(!isLogFile)
			m_totalUrls=n;
		else {
			m_totalUrls=0;
			char *p=m_buf1;
			char *pend=p+m_bufSize1;
			
			// start is the time in milliseconds of the first log 
			// message
			int64_t start=atoll(m_buf1);
			while(p<pend) {
				char *lineStart=p;
				char *urlStart=strstr(p," GET /search");
				if (!urlStart)
					urlStart=strstr(p," POST /search");
				if(!urlStart){
					p+=gbstrlen(p)+1; //goto next line
					continue;
				}
				urlStart++;
				m_wait=atoll(lineStart)-start;
				// register it here
				g_loop.registerSleepCallback(m_wait , 
							     urlStart, 
							     sleepWrapperLog);
				m_totalUrls++;
				p+=gbstrlen(p)+1;
			}
		}
	}
	log(LOG_INIT,"blaster: read %"INT32" urls into memory", 
	    m_totalUrls );

	if(!isLogFile){
		// get min time bewteen each spider in milliseconds
		m_wait = wait;
			
		// # of threads
		m_maxNumThreads = maxNumThreads;
		
		m_launched=0;
		
		m_portSwitch = 0;
		//if ( argc == 4 ) m_portSwitch = 1;
		//else             m_portSwitch = 0;
			
		// start our spider loop
		//startSpidering( );
		
		// wakeup wrapper every X ms
		g_loop.registerSleepCallback ( m_wait , NULL , 
					       sleepWrapper );
	}
	// this print to print how many docs have been processed
	m_print=false;
	m_startTime=gettimeofdayInMilliseconds();
	m_totalDone=0;
	// . now start g_loops main interrupt handling loop
	// . it should block forever
	// . when it gets a signal it dispatches to a server or db to handle it
	if ( ! g_loop.runLoop()    ) {
		log("blaster::runLoop failed" ); return; }
	// dummy return (0-->normal exit status for the shell)
	return;
}