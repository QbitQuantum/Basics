BOOL WebdavServer::connect() {
	// Specify an HTTP server.
	if (! hSession )
	{
		DbgPrint(L"WinHTTP session did not exist\n");
		return FALSE;
	}
	hConnect = WinHttpConnect( hSession, address, (INTERNET_PORT)port, 0);
	// Create an HTTP request handle.
	if( hConnect ) {
		return TRUE;
	}
	DbgPrint(L"Failed to etablish conncetion to %s:%i\n",address, port );
	return FALSE;
}