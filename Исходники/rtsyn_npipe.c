static int npipe_input_open(const char *pipe_name)
{
  static OVERLAPPED overlapped;
  static HANDLE hEvent;
  char PipeName[256];
  DWORD ret;
 

 hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
 memset( &overlapped, 0, sizeof(OVERLAPPED));
 overlapped.hEvent = hEvent;
	
  sprintf(PipeName, "\\\\.\\pipe\\%s", pipe_name);
  hPipe = CreateNamedPipe(PipeName, PIPE_ACCESS_DUPLEX|FILE_FLAG_OVERLAPPED, 
//    PIPE_WAIT|
  	PIPE_READMODE_BYTE |PIPE_TYPE_BYTE, 2, 
   0, PIPE_BUFFER_SIZE, 0, NULL);
  if (hPipe == INVALID_HANDLE_VALUE) {
    ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "Can't create Named Pipe %s : %ld",
    	pipe_name, GetLastError());
 	return -1;
  }
  ret = ConnectNamedPipe(hPipe, &overlapped);
	if ( (ret == 0)  && (ERROR_IO_PENDING!=GetLastError()) ){
    ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "CnnectNamePipe(%ld) error %s",
    	GetLastError(), pipe_name);
        CloseHandle(hPipe);
  	    hPipe=NULL;
        return -1;
   }
//	WaitForSingleObject(overlapped.hEvent, 1000);
	CloseHandle(hEvent);
  return 0;
}