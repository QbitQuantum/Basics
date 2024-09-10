/**
 * Serializes the passed in data unless the current event is suppressed.
 *
 * @param	Data	Text to log
 * @param	Event	Event name used for suppression purposes
 */
void FOutputDeviceFile::Serialize( const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category, const double Time )
{
#if ALLOW_LOG_FILE && !NO_LOGGING
	static bool Entry=false;
	if( !GIsCriticalError || Entry )
	{
		if( !LogAr && !Dead )
		{
			// Make log filename.
			if( !Filename[0] )
			{
				FCString::Strcpy(Filename, *FPlatformOutputDevices::GetAbsoluteLogFilename());
			}

			// if the file already exists, create a backup as we are going to overwrite it
			if (!bDisableBackup && !Opened)
			{
				CreateBackupCopy(Filename);
			}

			// Open log file.
			LogAr = CreateArchive();

			if( LogAr )
			{
				Opened = 1;

				WriteByteOrderMarkToArchive(EByteOrderMark::UTF8);

				if (!bSuppressEventTag)
				{
					Logf( TEXT("Log file open, %s"), FPlatformTime::StrTimestamp() );
				}
			}
			else 
			{
				Dead = true;
			}
		}

		if( LogAr && Verbosity != ELogVerbosity::SetColor )
		{
			WriteDataToArchive(Data, Verbosity, Category, Time);

			static bool GForceLogFlush = false;
			static bool GTestedCmdLine = false;
			if (!GTestedCmdLine)
			{
				GTestedCmdLine = true;
				// Force a log flush after each line
				GForceLogFlush = FParse::Param( FCommandLine::Get(), TEXT("FORCELOGFLUSH") );
			}
			if( GForceLogFlush )
			{
				LogAr->Flush();
			}
		}
	}
	else
	{
		Entry=true;
		Serialize( Data, Verbosity, Category, Time );
		Entry=false;
	}
#endif
}