EXPORT_C HBufC8* TcLog::ReadLogLC()
	{
	RFs fs;
	if( fs.Connect() != KErrNone )
		{
		return NULL;
		}

	RFile in;
	if( !in.Open( fs, KLogFile, EFileRead | EFileShareAny ) )
		{
		TInt fileSize( 0 );
		in.Size( fileSize );
		HBufC8* logText = HBufC8::NewLC( fileSize );
		TPtr8 logTextPtr( logText->Des() );
		in.Read( logTextPtr );
		in.Close();
		fs.Close();
		return logText;
		}

	fs.Close();
	return NULL;
	}