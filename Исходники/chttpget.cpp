void ChttpGet::WorkerThread()
{
	char szCommand[1000];
	char *p;
	int irsp = 0;
	ConnectSocket();
	if(m_Aborting)
	{
		fclose(LOCALFILE);
		return;
	}
	if(m_State != HTTP_STATE_CONNECTED)
	{
		fclose(LOCALFILE);
		return;
	}
	sprintf(szCommand,"GET %s%s HTTP/1.1\nAccept: */*\nAccept-Encoding: deflate\nHost: %s\n\n\n",m_ProxyEnabled?"":"/",m_ProxyEnabled?m_URL:m_szDir,m_szHost);
	send(m_DataSock,szCommand,strlen(szCommand),0);
	p = GetHTTPLine();
	if(strnicmp("HTTP/",p,5)==0)
	{
		char *pcode;
		pcode = strchr(p,' ')+1;
		if(!pcode)
		{
			m_State = HTTP_STATE_UNKNOWN_ERROR;	
			fclose(LOCALFILE);
			return;

		}
		pcode[3] = '\0';
		irsp = atoi(pcode);

		if(irsp == 0)
		{
			m_State = HTTP_STATE_UNKNOWN_ERROR;	
			fclose(LOCALFILE);
			return;
		}
		if(irsp==200)
		{
			int idataready=0;
			do
			{
				p = GetHTTPLine();
				if(p==NULL)
				{
					m_State = HTTP_STATE_UNKNOWN_ERROR;	
					fclose(LOCALFILE);
					return;
				}
				if(*p=='\0')
				{
					idataready = 1;
					break;
				}
				if(strnicmp(p,"Content-Length:",strlen("Content-Length:"))==0)
				{
					char *s = strchr(p,' ')+1;
					p = s;
					if(s)
					{
						while(*s)
						{
							if(!isdigit(*s))
							{
								*s='\0';
							}
							s++;
						};
						m_iBytesTotal = atoi(p);
					}

				}

				Sleep(1);
			}while(!idataready);
		ReadDataChannel();
		return;
		}
		m_State = HTTP_STATE_FILE_NOT_FOUND;
		fclose(LOCALFILE);
		return;
	}
	else
	{
		m_State = HTTP_STATE_UNKNOWN_ERROR;
		fclose(LOCALFILE);
		return;
	}
}