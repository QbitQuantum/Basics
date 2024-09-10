HRESULT MsmqQueue::openQueue(const char *szQueuePath, int openmode)
{
    WCHAR wszPathName[MQ_MAX_Q_NAME_LEN] = {0};
    long	accessmode = openmode;  // bit field: MQ_{RECEIVE,SEND,PEEK,ADMIN}_ACCESS, 
    long	sharemode = MQ_DENY_NONE;

    // Validate the input string.
    if (szQueuePath == NULL)
	{
	    return MQ_ERROR_INVALID_PARAMETER;
	}

    // convert to wide characters;
	int len = strlen(szQueuePath);
    if (MultiByteToWideChar(
			    CP_ACP,
			    0,
			    szQueuePath,
			    len,
			    wszPathName,
			    _countof(wszPathName) ) == 0)
	{
	    return MQ_ERROR_INVALID_PARAMETER;
	}
    if (len < _countof( wszPathName ) )
		wszPathName[len]= 0; // need this to terminate	
	

    HRESULT hr = MQ_OK;

    // dinoch Mon, 18 Apr 2005  16:12

      printf("open: ");
      printf("fmtname(%ls) ", wszPathName);
      printf("accessmode(%d) ", accessmode);
      printf("sharemode(%d) ", sharemode);
     printf("\n");

    hr = MQOpenQueue(
		     wszPathName,           // Format name of the queue
		     accessmode,		  // Access mode
		     sharemode,  	          // Share mode
		     &hQueue   	                  // OUT: Handle to queue
		     );
			 
    // Retry to handle AD replication delays. 
    //
    if (hr == MQ_ERROR_QUEUE_NOT_FOUND)
	{
	    int iCount = 0 ;
	    while((hr == MQ_ERROR_QUEUE_NOT_FOUND) && (iCount < 120))
		{
		    printf(".");

		    // Wait a bit.
		    iCount++ ;
		    Sleep(50);

		    // Retry.
		    hr = MQOpenQueue(wszPathName, 
				     accessmode,
				     sharemode,
				     &hQueue);
		}
	}

    if (FAILED(hr))
	{
	    MQCloseQueue(hQueue);
	}

    return hr;

};