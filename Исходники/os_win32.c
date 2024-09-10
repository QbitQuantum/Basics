/*
 *--------------------------------------------------------------
 *
 * OS_LibInit --
 *
 *	Set up the OS library for use.
 *
 * Results:
 *	Returns 0 if success, -1 if not.
 *
 * Side effects:
 *	Sockets initialized, pseudo file descriptors setup, etc.
 *
 *--------------------------------------------------------------
 */
int OS_LibInit(int stdioFds[3])
{
    WORD  wVersion;
    WSADATA wsaData;
    int err;
    int fakeFd;
    char *cLenPtr = NULL;
    char *val = NULL;

//	char * abc;
//	int nTestFcgi;

	char namepipe[256];

    if(libInitialized)
        return 0;

    InitializeCriticalSection(&fdTableCritical);   
        
    /*
     * Initialize windows sockets library.
     */
    wVersion = MAKEWORD(2,0);
    err = WSAStartup( wVersion, &wsaData );
    if (err) {
        fprintf(stderr, "Error starting Windows Sockets.  Error: %d",
		WSAGetLastError());
	exit(111);
    }

    /*
     * Create the I/O completion port to be used for our I/O queue.
     */
    if (hIoCompPort == INVALID_HANDLE_VALUE) {
	hIoCompPort = CreateIoCompletionPort (INVALID_HANDLE_VALUE, NULL,
					      0, 1);
	if(hIoCompPort == INVALID_HANDLE_VALUE) {
	    printf("<H2>OS_LibInit Failed CreateIoCompletionPort!  ERROR: %d</H2>\r\n\r\n",
	       GetLastError());
	    return -1;
	}
    }

    /*
     * If a shutdown event is in the env, save it (I don't see any to 
     * remove it from the environment out from under the application).
     * Spawn a thread to wait on the shutdown request.
     */
    val = getenv(SHUTDOWN_EVENT_NAME);
    if (val != NULL) 
    {
        HANDLE shutdownEvent = (HANDLE) atoi(val);

        if (_beginthread(ShutdownRequestThread, 0, shutdownEvent) == -1)
        {
            return -1;
        }
    }

    if (acceptMutex == INVALID_HANDLE_VALUE)
    {
        /* If an accept mutex is in the env, use it */
        val = getenv(MUTEX_VARNAME);
        if (val != NULL) 
        {
            acceptMutex = (HANDLE) atoi(val);
        }
    }

    /*
     * Determine if this library is being used to listen for FastCGI
     * connections.  This is communicated by STDIN containing a
     * valid handle to a listener object.  In this case, both the
     * "stdout" and "stderr" handles will be INVALID (ie. closed) by
     * the starting process.
     *
     * The trick is determining if this is a pipe or a socket...
     *
     * XXX: Add the async accept test to determine socket or handle to a
     *      pipe!!!
     */
    if((GetStdHandle(STD_OUTPUT_HANDLE) == INVALID_HANDLE_VALUE) &&
       (GetStdHandle(STD_ERROR_HANDLE)  == INVALID_HANDLE_VALUE) &&
       (GetStdHandle(STD_INPUT_HANDLE)  != INVALID_HANDLE_VALUE) ) 
    {
        DWORD pipeMode = PIPE_READMODE_BYTE | PIPE_WAIT;
        HANDLE oldStdIn = GetStdHandle(STD_INPUT_HANDLE);

        // Move the handle to a "low" number
        if (! DuplicateHandle(GetCurrentProcess(), oldStdIn,
		                         GetCurrentProcess(), &hListen,
                              0, TRUE, DUPLICATE_SAME_ACCESS))
        {
            return -1;
        }

        if (! SetStdHandle(STD_INPUT_HANDLE, hListen))
        {
            return -1;
        }

        CloseHandle(oldStdIn);
		//OutputDebugString("CloseHandle(oldStdIn);\n");
#ifdef DEBUG_CGI
		//OutputDebugString("in  DEBUG_CGI \n");
		
		sprintf(namepipe,"%s\\%d","\\\\.\\pipe\\FastCGI\\dynamic",getpid());
		//OutputDebugString(namepipe);
		hListen=CreateNamedPipe( 
			//"\\\\.\\pipe\\FastCGI\\dynamic\\abc",             // pipe name 
			namepipe,
			PIPE_ACCESS_DUPLEX,       // read/write access 
			PIPE_TYPE_MESSAGE |       // message type pipe 
			PIPE_READMODE_MESSAGE |   // message-read mode 
			PIPE_WAIT,                // blocking mode 
			PIPE_UNLIMITED_INSTANCES, // max. instances  
			4096,                  // output buffer size 
			4096,                  // input buffer size 
			NMPWAIT_USE_DEFAULT_WAIT, // client time-out 
			NULL);


  #endif
	/*
	 * Set the pipe handle state so that it operates in wait mode.
	 *
	 * NOTE: The listenFd is not mapped to a pseudo file descriptor
	 *       as all work done on it is contained to the OS library.
	 *
	 * XXX: Initial assumption is that SetNamedPipeHandleState will
	 *      fail if this is an IP socket...
	 */
        if (SetNamedPipeHandleState(hListen, &pipeMode, NULL, NULL)) 
        {
            listenType = FD_PIPE_SYNC;
        } 
        else 
        {
            listenType = FD_SOCKET_SYNC;
        }
    }

    /*
     * If there are no stdioFds passed in, we're done.
     */
    if(stdioFds == NULL) {
        libInitialized = 1;
        return 0;
    }

    /*
     * Setup standard input asynchronous I/O.  There is actually a separate
     * thread spawned for this purpose.  The reason for this is that some
     * web servers use anonymous pipes for the connection between itself
     * and a CGI application.  Anonymous pipes can't perform asynchronous
     * I/O or use I/O completion ports.  Therefore in order to present a
     * consistent I/O dispatch model to an application we emulate I/O
     * completion port behavior by having the standard input thread posting
     * messages to the hIoCompPort which look like a complete overlapped
     * I/O structure.  This keeps the event dispatching simple from the
     * application perspective.
     */
    stdioHandles[STDIN_FILENO] = GetStdHandle(STD_INPUT_HANDLE);

    if(!SetHandleInformation(stdioHandles[STDIN_FILENO],
			     HANDLE_FLAG_INHERIT, 0)) {
/*
 * XXX: Causes error when run from command line.  Check KB
        err = GetLastError();
        DebugBreak();
	exit(99);
 */
    }

    if ((fakeFd = Win32NewDescriptor(FD_PIPE_SYNC,
				     (int)stdioHandles[STDIN_FILENO],
				     STDIN_FILENO)) == -1) {
        return -1;
    } else {
        /*
	 * Set stdin equal to our pseudo FD and create the I/O completion
	 * port to be used for async I/O.
	 */
	stdioFds[STDIN_FILENO] = fakeFd;
    }

    /*
     * Create the I/O completion port to be used for communicating with
     * the thread doing I/O on standard in.  This port will carry read
     * and possibly thread termination requests to the StdinThread.
     */
    if (hStdinCompPort == INVALID_HANDLE_VALUE) {
	hStdinCompPort = CreateIoCompletionPort (INVALID_HANDLE_VALUE, NULL,
					      0, 1);
	if(hStdinCompPort == INVALID_HANDLE_VALUE) {
	    printf("<H2>OS_LibInit Failed CreateIoCompletionPort: STDIN!  ERROR: %d</H2>\r\n\r\n",
	       GetLastError());
	    return -1;
	}
    }

    /*
     * Create the thread that will read stdin if the CONTENT_LENGTH
     * is non-zero.
     */
    if((cLenPtr = getenv("CONTENT_LENGTH")) != NULL &&
       atoi(cLenPtr) > 0) {
        hStdinThread = (HANDLE) _beginthread(StdinThread, 0, NULL);
	if (hStdinThread == (HANDLE) -1) {
	    printf("<H2>OS_LibInit Failed to create STDIN thread!  ERROR: %d</H2>\r\n\r\n",
		   GetLastError());
	    return -1;
        }
    }

    /*
     * STDOUT will be used synchronously.
     *
     * XXX: May want to convert this so that it could be used for OVERLAPPED
     *      I/O later.  If so, model it after the Stdin I/O as stdout is
     *      also incapable of async I/O on some servers.
     */
    stdioHandles[STDOUT_FILENO] = GetStdHandle(STD_OUTPUT_HANDLE);
    if(!SetHandleInformation(stdioHandles[STDOUT_FILENO],
			     HANDLE_FLAG_INHERIT, FALSE)) {
        DebugBreak();
	exit(99);
    }

    if ((fakeFd = Win32NewDescriptor(FD_PIPE_SYNC,
				     (int)stdioHandles[STDOUT_FILENO],
				     STDOUT_FILENO)) == -1) {
        return -1;
    } else {
        /*
	 * Set stdout equal to our pseudo FD
	 */
	stdioFds[STDOUT_FILENO] = fakeFd;
    }

    stdioHandles[STDERR_FILENO] = GetStdHandle(STD_ERROR_HANDLE);
    if(!SetHandleInformation(stdioHandles[STDERR_FILENO],
			     HANDLE_FLAG_INHERIT, FALSE)) {
        DebugBreak();
	exit(99);
    }
    if ((fakeFd = Win32NewDescriptor(FD_PIPE_SYNC,
				     (int)stdioHandles[STDERR_FILENO],
				     STDERR_FILENO)) == -1) {
        return -1;
    } else {
        /*
	 * Set stderr equal to our pseudo FD
	 */
	stdioFds[STDERR_FILENO] = fakeFd;
    }

    return 0;
}