CFtpGet::CFtpGet(char *URL,char *localfile,char *Username,char *Password)
{
	SOCKADDR_IN listensockaddr;
	m_State = FTP_STATE_STARTUP;

	m_ListenSock = INVALID_SOCKET;
	m_DataSock = INVALID_SOCKET;
	m_ControlSock = INVALID_SOCKET;
	m_iBytesIn = 0;
	m_iBytesTotal = 0;
	m_Aborting = false;
	m_Aborted = false;

	LOCALFILE = fopen(localfile,"wb");
	if(NULL == LOCALFILE)
	{
		m_State = FTP_STATE_CANT_WRITE_FILE;
		return;
	}

	if(Username)
	{
		strcpy(m_szUserName,Username);
	}
	else
	{
		strcpy(m_szUserName,"anonymous");
	}
	if(Password)
	{
		strcpy(m_szPassword,Password);
	}
	else
	{
		strcpy(m_szPassword,"*****@*****.**");
	}
	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	if(INVALID_SOCKET == m_ListenSock)
	{
		// vint iWinsockErr = WSAGetLastError();
		m_State = FTP_STATE_SOCKET_ERROR;
		return;
	}
	else
	{
		listensockaddr.sin_family = AF_INET;		
		listensockaddr.sin_port = 0;
		listensockaddr.sin_addr.s_addr = INADDR_ANY;
							
		// Bind the listen socket
		if (bind(m_ListenSock, (SOCKADDR *)&listensockaddr, sizeof(SOCKADDR)))
		{
			//Couldn't bind the socket
			// int iWinsockErr = WSAGetLastError();
			m_State = FTP_STATE_SOCKET_ERROR;
			return;
		}

		// Listen for the server connection
		if (listen(m_ListenSock, 1))	
		{
			//Couldn't listen on the socket
			// int iWinsockErr = WSAGetLastError();
			m_State = FTP_STATE_SOCKET_ERROR;
			return;
		}
	}
	m_ControlSock = socket(AF_INET, SOCK_STREAM, 0);
	if(INVALID_SOCKET == m_ControlSock)
	{
		m_State = FTP_STATE_SOCKET_ERROR;
		return;
	}
	//Parse the URL
	//Get rid of any extra ftp:// stuff
	char *pURL = URL;
	if(_strnicmp(URL,"ftp:",4)==0)
	{
		pURL +=4;
		while(*pURL == '/')
		{
			pURL++;
		}
	}
	//There shouldn't be any : in this string
	if(strchr(pURL,':'))
	{
		m_State = FTP_STATE_URL_PARSING_ERROR;
		return;
	}
	//read the filename by searching backwards for a /
	//then keep reading until you find the first /
	//when you found it, you have the host and dir
	char *filestart = NULL;
	char *dirstart = NULL;
	for(int i = strlen(pURL);i>=0;i--)
	{
		if(pURL[i]== '/')
		{
			if(!filestart)
			{
				filestart = pURL+i+1;
				dirstart = pURL+i+1;
				strcpy(m_szFilename,filestart);
			}
			else
			{
				dirstart = pURL+i+1;
			}
		}
	}
	if((dirstart==NULL) || (filestart==NULL))
	{
		m_State = FTP_STATE_URL_PARSING_ERROR;
		return;
	}
	else
	{
		strncpy(m_szDir,dirstart,(filestart-dirstart));
		m_szDir[(filestart-dirstart)] = '\0';
		strncpy(m_szHost,pURL,(dirstart-pURL));
		m_szHost[(dirstart-pURL)-1] = '\0';
	}
	//At this point we should have a nice host,dir and filename
	
	//if(NULL==CreateThread(NULL,0,ObjThread,this,0,&m_dwThreadId))
	if(NULL==_beginthread(FTPObjThread,0,this))
	{
		m_State = FTP_STATE_INTERNAL_ERROR;
		return;
	}
	m_State = FTP_STATE_CONNECTING;
}