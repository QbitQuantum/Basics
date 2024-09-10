bool MWinNamedPipeClient::Create(const char *pipename,DWORD waittime,bool timeouterror)
	{
	Destroy();
	
	if (WaitNamedPipeA(pipename, waittime) == FALSE)
		{
		if(timeouterror==true)  {  MStdPrintf("**Unable to connect to Pipe Server\n");  }	
		Destroy();
		return false;
		}

	mhPipe=CreateFileA(pipename,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	if(mhPipe==INVALID_HANDLE_VALUE)
		{
		Destroy();
		return false;
		}

	return true;
	}