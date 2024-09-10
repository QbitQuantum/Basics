void FileTransfer::StartTransfer( TransferType type, const RString &sURL, const RString &sSrcFile, const RString &sDestFile )
{
	RString Proto;
	RString Server;
	int Port=80;
	RString sAddress;

	if( !ParseHTTPAddress( sURL, Proto, Server, Port, sAddress ) )
	{
		m_sStatus = "Invalid URL.";
		m_bFinished = true;
		UpdateProgress();
		return;
	}

	m_bSavingFile = sDestFile != "";

	m_sBaseAddress = "http://" + Server;
	if( Port != 80 )
		m_sBaseAddress += ssprintf( ":%d", Port );
	m_sBaseAddress += "/";

	if( sAddress.Right(1) != "/" )
	{
		m_sEndName = Basename( sAddress );
		m_sBaseAddress += Dirname( sAddress );
	}
	else
	{
		m_sEndName = "";
	}

	// Open the file...

	// First find out if a file by this name already exists if so, then we gotta
	// ditch out.
	// XXX: This should be fixed by a prompt or something?

	// if we are not talking about a file, let's not worry
	if( m_sEndName != "" && m_bSavingFile )
	{
		if( !m_fOutputFile.Open( sDestFile, RageFile::WRITE | RageFile::STREAMED ) )
		{
			m_sStatus = m_fOutputFile.GetError();
			UpdateProgress();
			return;
		}
	}
	// Continue...

	sAddress = URLEncode( sAddress );

	if ( sAddress != "/" )
		sAddress = "/" + sAddress;

	m_wSocket.close();
	m_wSocket.create();

	m_wSocket.blocking = true;

	if( !m_wSocket.connect( Server, (short) Port ) )
	{
		m_sStatus = "Failed to connect.";
		UpdateProgress();
		return;
	}

	// Produce HTTP header
	RString sAction;
	switch( type )
	{
	case upload: sAction = "POST"; break;
	case download: sAction = "GET"; break;
	}

	vector<RString> vsHeaders;
	vsHeaders.push_back( sAction+" "+sAddress+" HTTP/1.0" );
	vsHeaders.push_back( "Host: " + Server );
	vsHeaders.push_back( "Cookie: " + g_sCookie.Get() );
	vsHeaders.push_back( "Connection: closed" );
	string sBoundary = "--ZzAaB03x";
	vsHeaders.push_back( "Content-Type: multipart/form-data; boundary=" + sBoundary );
	RString sRequestPayload;
	if( type == upload )
	{
		RageFile f;
		if( !f.Open( sSrcFile ) )
			FAIL_M( f.GetError() );
		sRequestPayload.reserve( f.GetFileSize() );
		int iBytesRead = f.Read( sRequestPayload );
		if( iBytesRead == -1 )
			FAIL_M( f.GetError() );

		sRequestPayload = "--" + sBoundary + "\r\n" + 
			"Content-Disposition: form-data; name=\"name\"\r\n" +
			"\r\n" +
			"Chris\r\n" +
			"--" + sBoundary + "\r\n" + 
			"Content-Disposition: form-data; name=\"userfile\"; filename=\"" + Basename(sSrcFile) + "\"\r\n" +
			"Content-Type: application/zip\r\n" + 
			"\r\n" +
			sRequestPayload + "\r\n" +
			"--" + sBoundary + "--";
	}
	/*
	if( sRequestPayload.size() > 0 )
	{
		sHeader += "Content-Type: application/octet-stream\r\n";
		sHeader += "Content-Length: multipart/form-data; boundary=" + sBoundary + "\r\n";
		//sHeader += "Content-Length: " + ssprintf("%d",sRequestPayload.size()) + "\r\n";
	}
	*/

	vsHeaders.push_back( "Content-Length: " + ssprintf("%zd",sRequestPayload.size()) );

	RString sHeader;
	FOREACH_CONST( RString, vsHeaders, h )
		sHeader += *h + "\r\n";
	sHeader += "\r\n";

	m_wSocket.SendData( sHeader.c_str(), sHeader.length() );
	m_wSocket.SendData( "\r\n" );

	m_wSocket.SendData( sRequestPayload.GetBuffer(), sRequestPayload.size() );

	m_sStatus = "Header Sent.";
	m_wSocket.blocking = false;
	m_bIsDownloading = true;
	m_sBUFFER = "";
	m_bGotHeader = false;
	UpdateProgress();
}