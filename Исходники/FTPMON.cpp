//ensure you set up WRITE and DELETE permission for user ref'd by "myuser"
void TransferFile(LPTSTR lpFile, LPTSTR lpServer)
{
	HINTERNET hSession = InternetOpen("BL_FTPCLIENT/1.0", INTERNET_OPEN_TYPE_DIRECT,0,0,0);
	InternetSetStatusCallback(hSession,&MyStatusCallback);
		
	HINTERNET hConnect = InternetConnect(hSession,
										lpServer,
										INTERNET_DEFAULT_FTP_PORT,
										"myuser",
										"mypassword",
										INTERNET_SERVICE_FTP,0,1);
	
	
	FtpPutFile(hConnect,
			   lpFile,
			   lpFile,
			   FTP_TRANSFER_TYPE_BINARY,
			   0);



	InternetCloseHandle(hConnect);
	InternetCloseHandle(hSession);


 	return;
}