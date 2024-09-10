// ---------------------------------------------
// Monitor the print spool and prompt users to confirm print jobs
// ---------------------------------------------
DWORD CGreenPrintMonitorThread::OnSpoolMonitorThread(void)
{
	DWORD cchPrinterName = 0;

	// ---------------------------------------------
	// Get the buffer size needed to hold the printer name
	// ---------------------------------------------
	GetDefaultPrinter( NULL, &cchPrinterName );

	if ( cchPrinterName > 0 )
	{
		WCHAR *PrinterName = (WCHAR*)LocalAlloc( LMEM_ZEROINIT, cchPrinterName * sizeof(WCHAR) );

		if ( NULL != PrinterName )
		{
			// ---------------------------------------------
			// Get the name of the print
			// ---------------------------------------------
			if ( GetDefaultPrinter( PrinterName, &cchPrinterName ) )
			{
				HANDLE hPrinter = NULL;

				if ( OpenPrinter( PrinterName, &hPrinter, NULL ) )
				{
					HANDLE hChangeNotification = NULL;

					// ---------------------------------------------
					// Setup the structures needed to register for print spool notifications
					// ---------------------------------------------

					PRINTER_NOTIFY_INFO_DATA NotifyInfoData[] = {
						JOB_NOTIFY_TYPE,
						JOB_NOTIFY_FIELD_TOTAL_PAGES,
						0, // Reserved
						JOB_NOTIFY_TYPE,
						0
					};

					PRINTER_NOTIFY_OPTIONS_TYPE NotifyOptionsType[] = {
						JOB_NOTIFY_TYPE,
						0, // Reserved 0
						0, // Reserved 1
						0, // Reserved 2
						_countof(NotifyInfoData),
						(PWORD)NotifyInfoData
					};

					PRINTER_NOTIFY_OPTIONS NotifyOptions;
					ZeroMemory( &NotifyOptions, sizeof(NotifyOptions) );
					NotifyOptions.Version = 2;
					NotifyOptions.Count = _countof(NotifyOptionsType);
					NotifyOptions.pTypes = NotifyOptionsType;

					// ---------------------------------------------
					// Request a notification handle that will be signaled when a new print job is queued
					// ---------------------------------------------
					hChangeNotification = 
						FindFirstPrinterChangeNotification( 
						hPrinter, 
						PRINTER_CHANGE_ADD_JOB, 
						0, // Reserved 
						&NotifyOptions
						);

					if ( INVALID_HANDLE_VALUE != hChangeNotification )
					{
						do
						{
							// ---------------------------------------------
							// The order of these handles is important to the code below that checks which event was signaled
							// ---------------------------------------------
							HANDLE HandleList[] = {
								hChangeNotification, 
								m_hExitSpoolMonitorThread
							};

							// ---------------------------------------------
							// Wait for the print job notification handle or the exit handle to be signaled
							// ---------------------------------------------
							DWORD WaitReason = WaitForMultipleObjects( 
								_countof(HandleList), 
								HandleList, 
								FALSE, 
								INFINITE );

							if ( WAIT_OBJECT_0 == WaitReason )
							{
								PRINTER_NOTIFY_INFO *pPrinterNotifyInfo = NULL;

								// ---------------------------------------------
								// The notification handle was signaled so get the info about the print job
								// ---------------------------------------------
								if ( FindNextPrinterChangeNotification( 
										hChangeNotification,
										NULL,
										&NotifyOptions,
										(LPVOID*)&pPrinterNotifyInfo ) )
								{
									if ( NULL != pPrinterNotifyInfo )
									{
										// ---------------------------------------------
										// Required code to make the FindNextPrinterChangeNotification happy (see MSDN documentation)
										// ---------------------------------------------
										if ( PRINTER_NOTIFY_INFO_DISCARDED & pPrinterNotifyInfo->Flags )
										{
											FreePrinterNotifyInfo( pPrinterNotifyInfo );
											pPrinterNotifyInfo = NULL;

											DWORD Flags = NotifyOptions.Flags;

											NotifyOptions.Flags = PRINTER_NOTIFY_OPTIONS_REFRESH;

											FindNextPrinterChangeNotification( 
													hChangeNotification,
													NULL,
													&NotifyOptions,
													(LPVOID*)&pPrinterNotifyInfo );

											NotifyOptions.Flags = Flags;
										}
									}

									// ---------------------------------------------
									// Get the needed information from the job
									// ---------------------------------------------
									DWORD JobId = 0;
									DWORD JobPages = 0;

									if ( NULL != pPrinterNotifyInfo )
									{
										GetJobInfoFromPrinterNotifyInfo( pPrinterNotifyInfo, &JobId, &JobPages );

										FreePrinterNotifyInfo( pPrinterNotifyInfo );
										pPrinterNotifyInfo = NULL;
									}

									// ---------------------------------------------
									// Pause the print job 
									// ---------------------------------------------
									if ( SetJob( hPrinter,
											JobId,
											0,
											NULL,
											JOB_CONTROL_PAUSE ) )
									{
										// ---------------------------------------------
										// If we weren't able to get the number of pages already
										// then get the count from the job itself
										// ---------------------------------------------
										if ( 0 == JobPages )
										{
											JobPages = JobPagesFromJobId( hPrinter, JobId );
										}

										// ---------------------------------------------
										// Interact with the user to determine if they would really like to print
										// ---------------------------------------------
										BOOL ResumeJob = ShouldResumePrintJob( JobPages );
										
										if ( ResumeJob )
										{
											if ( !SetJob( hPrinter,
												JobId,
												0,
												NULL,
												JOB_CONTROL_RESUME ) )
											{
												m_pLogging->Log( L"Failed resuming print job." );
											}
										}
										else
										{
											if ( !SetJob( hPrinter,
												JobId,
												0,
												NULL,
												JOB_CONTROL_DELETE ) )
											{
												m_pLogging->Log( L"Failed deleting print job." );
											}											
										}
									}
								}
								else
								{
									m_pLogging->Log( L"Failed getting information concerning a print job." );
								}
							}
							else if ( ( WAIT_OBJECT_0 + 1 ) == WaitReason ) 
							{
								// ---------------------------------------------
								// The exit handle was signaled. Stop checking for print jobs.
								// ---------------------------------------------
								break;
							}
							else
							{
								m_pLogging->Log( L"Unexpected notification while waiting for print job." );
							}
						}
						while( TRUE );
					}
					else
					{
						m_pLogging->Log( L"Failed trying to get print job notification handle." );
					}

					if ( INVALID_HANDLE_VALUE != hChangeNotification )
					{
						FindClosePrinterChangeNotification( hChangeNotification );
						hChangeNotification = NULL;
					}

					if ( NULL != hPrinter )
					{
						ClosePrinter( hPrinter );
						hPrinter = NULL;
					}
				}
			}

			if ( NULL != PrinterName )
			{
				cchPrinterName = 0;

				LocalFree( PrinterName );
				PrinterName = NULL;
			}
		}
	}

	return NO_ERROR;
}