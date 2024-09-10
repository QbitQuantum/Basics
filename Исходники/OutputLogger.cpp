OutputLogger::OutputLogger(FILE *file, const std::string &filename) :
	fd(-1), fileOld(NULL), filenameLog(filename), fileLog(NULL), 	
	fdPipeRead(-1), pThread(NULL)
{
	// Get the underlying file descriptor for the FILE stream
	fd = _fileno(file);

	// Probably on windows and there is no stdout/stderr in Subsystem Windows
	if (fd < 0) {
		fileLog = freopen(filenameLog.c_str(),"w",file);
#ifdef WIN32
		DWORD stdhandle = 0;
		if (fileLog == stdout) 
			stdhandle = STD_OUTPUT_HANDLE;
		else if (fileLog == stderr) 
			stdhandle = STD_ERROR_HANDLE;
		if (stdhandle) 
			SetStdHandle(stdhandle,(HANDLE)_get_osfhandle(_fileno(fileLog)));
#endif
		return;
	}

	// Create the pipe
	int fdsPipe[2];
	if (_pipe(fdsPipe,256,_O_BINARY) != 0) {
		return;
	}
	fdPipeRead = fdsPipe[0];
	int fdPipeWrite = fdsPipe[1];

	// Make sure that buffering is turned off on the incoming file
	std::setvbuf(file,NULL,_IONBF,0);

	// Duplicate the fd and create new filestream for it
	fileOld = _fdopen(_dup(fd),"w");
	// If the file was stderr, make sure the new file doesn't have buffering
	if (fileOld && file == stderr) std::setvbuf(fileOld,NULL,_IONBF,0);

	// Create the output log file
	fileLog =  std::fopen(filenameLog.c_str(),"w");

	// Duplicate pipe write file descriptor and replace original
	_dup2(fdPipeWrite,fd);
	
	// Close the fd for the write end of the pipe
	_close(fdPipeWrite);
	fdPipeWrite = -1;

	// Create the thread
	pThread = SDL_CreateThread( (int (SDLCALL*)(void*)) &OutputLogger::sThreadMain,this);
}