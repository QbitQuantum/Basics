BOOL CPubThread::DoThread(LPVOID pData)
{
	DWORD enablepublishing = 0;
	CFG().GetValue( "Settings", "EnablePublishing", &enablepublishing );

	// Punt if publishing is disabled
	if ( !enablepublishing )
	{	m_bReset = TRUE;
		Sleep( 1000 ); return TRUE;
	} // end if

	DWORD tickcount = GetTickCount();
	
	SYSTEMTIME	st;
	GetSystemTime( &st );

	// Calculate seconds offset
	DWORD seconds = ( st.wHour * 60 * 60 ) + ( st.wMinute * 60 ) + st.wSecond;

	// Process each job
	LPPUBINFO ppi = NULL;
	while ( ( ppi = (LPPUBINFO)PUBLIST().GetNext( ppi ) ) != NULL )
	{
		try
		{
			// Is publishing on hold?
			if ( ppi->bHold ) continue;

			// Image information
			LPPUBIMGINFO ppii = NULL;

			// Are we doing any avi capturing?
			if ( ( ppi->f1 & ( PUBF1_AVI | PUBF1_THMAVI ) ) != 0 )
			{
				// Update AVI's
				if ( ( ppi->f1 & PUBF1_AVICAPMOTION ) == 0 || IsMotion( ppi ) )
				{
					// Check for avi
					if ( ( ppi->f1 & PUBF1_AVI ) != 0 )
					{
						// Time to capture?
						if (	( ppi->f1 & PUBF1_AVICAPMOTION ) != 0 || 
								ppi->avitimeout < tickcount )
						{
							ppii = IMGLIST().FindByName( ppi->img );
							if ( ppii != NULL )
							{
								// Refresh the image
								IMGLIST().Update( ppii, TRUE );

								// Wait for next frame
								if ( ppi->capframes < 1 ) ppi->capframes = 1;
								if ( ppi->capseconds < 1 ) ppi->capseconds = 1;
								long delay = ( ppi->capseconds * 1000 ) / ppi->capframes;
								ppi->avitimeout = tickcount + delay;

								// Write out a frame of the avi
								WriteAviFrame( ppi, ppi->avi, ppii, ppi->pub_fname );
							
							} // end if

						} // end if

					} // end if

					// Check for thumbnail avi
					if ( ( ppi->f1 & PUBF1_THMAVI ) != 0 )
					{
						// Time to capture?
						if (	( ppi->f1 & PUBF1_AVICAPMOTION ) != 0 || 
								ppi->thmavitimeout < tickcount )
						{
							// Get image if we don't already have it
							if ( ppii == NULL )
							{	ppii = IMGLIST().FindByName( ppi->img );
								IMGLIST().Update( ppii, TRUE );
							} // end if

							if ( ppii != NULL )
							{
								// Wait for next frame
								if ( ppi->capframes < 1 ) ppi->capframes = 1;
								if ( ppi->capseconds < 1 ) ppi->capseconds = 1;
								long delay = ( ppi->capseconds * 1000 ) / ppi->capframes;
								ppi->thmavitimeout = tickcount + delay;

								// Write out a frame of the avi
								WriteAviFrame( ppi, ppi->thmavi, ppii, ppi->pub_tfname );

							} // end if

						} // end if

					} // end if

				} // end if

			} // end if

			// Are we detecting motion?
			if ( ( ppi->f1 & PUBF1_MOTION ) != 0 )
			{
				if ( IsMotion( ppi ) )
				{
					// Save motion time
					if ( ppi->motioninterval == 0 ) ppi->motioninterval = 30;
					ppi->nextmotion = GetTickCount() + ( ppi->motioninterval * 1000 );

					// Get current file name
					GetFileName( ppi );

					// Refresh the image
					if ( ppii == NULL ) IMGLIST().Update( ppi->img, TRUE );

					// Handle avi
					if ( ( ppi->f1 & PUBF1_AVI ) != 0 )
					{
						if ( ppi->avi->IsOpen() )
						{
							// Save avi filename
							strcpy( ppi->avicachefile, ppi->avi->GetFileName() );
							ppi->avi->Close();

							// Save thumbnail avi filename
							strcpy( ppi->thmavicachefile, ppi->thmavi->GetFileName() );
							ppi->thmavi->Close();

						} // end if

					} // end if

					// Handle thumbnail avi
					if ( ( ppi->f1 & PUBF1_THMAVI ) != 0 )
					{
						if ( ppi->thmavi->IsOpen() )
						{
							// Save avi filename
							strcpy( ppi->thmavicachefile, ppi->thmavi->GetFileName() );
							ppi->thmavi->Close();

							// Save thumbnail avi filename
							strcpy( ppi->thmavicachefile, ppi->thmavi->GetFileName() );
							ppi->thmavi->Close();

						} // end if

					} // end if

					BOOL bPublished = FALSE;

					// Check for FTP
					if ( ppi->type == PUBTYPE_FTP ) bPublished = Ftp( ppi );

					// Check for Email
					else if ( ppi->type == PUBTYPE_EMAIL ) bPublished = Email( ppi );

					// Check for Disk
					else if ( ppi->type == PUBTYPE_DISK ) bPublished = Disk( ppi );

					if ( bPublished )
					{
						// Inform FRAME
						if ( ppi->type == PUBTYPE_FTP ) FRAME()->SetEvent( 2 );
						else if ( ppi->type == PUBTYPE_EMAIL ) FRAME()->SetEvent( 3 );
						else if ( ppi->type == PUBTYPE_DISK ) FRAME()->SetEvent( 4 );

						// Play sound if needed
						if ( ( ppi->f1 & PUBF1_PLAYSOUND ) != 0 )
						{	if ( *ppi->snd ) PLAYSOUND( ppi->snd );
							else PLAYSOUND( IDW_CAMERA );
						} // end if

					} // end if

					// Ensure cache files are gone
					if ( *ppi->avicachefile != 0 )
					{	CWinFile::Delete( ppi->avicachefile );
						*ppi->avicachefile = 0;
					} // end if
					if ( *ppi->thmavicachefile != 0 )
					{	CWinFile::Delete( ppi->thmavicachefile );
						*ppi->thmavicachefile = 0;
					} // end if

				} // end if

			} // end if

			// Has an interval been specified?
			else if ( ppi->interval != 0 )
			{
				// Set interval first time
				if ( m_bReset || ppi->timeout == 0 ) 
					ppi->timeout = tickcount + ( ppi->interval * 1000 );

				// Have we timed out?			
				BOOL publish = ppi->timeout < tickcount;

				// Do we want to sync to the system clock?
				if ( !publish && ( ppi->f1 & PUBF1_SYNCTOCLOCK ) != 0 ) 
				{
					// Is it a new second?
					if ( seconds != ppi->lasttime )
					{
						// Record last pub time
						ppi->lasttime = seconds;

						// Is it time to publish?
						if ( !( seconds % ppi->interval ) ) publish = TRUE;

					} // end if

				} // end if

				if ( publish )
				{
					// Record next timeout interval
					ppi->timeout = tickcount + ( ppi->interval * 1000 );

					// Record last pub time
					ppi->lasttime = seconds;
					
					// Get current file name
					GetFileName( ppi );

					// Refresh the image
					if ( ppii == NULL ) IMGLIST().Update( ppi->img, TRUE );

					// Handle avi
					if ( ( ppi->f1 & PUBF1_AVI ) != 0 )
					{
						if ( ppi->avi->IsOpen() )
						{
							// Save avi filename
							strcpy( ppi->avicachefile, ppi->avi->GetFileName() );
							ppi->avi->Close();

							// Save thumbnail avi filename
							strcpy( ppi->thmavicachefile, ppi->thmavi->GetFileName() );
							ppi->thmavi->Close();

						} // end if

						// Punt if no avi
						else return TRUE;

					} // end if

					// Handle thumbnail avi
					if ( ( ppi->f1 & PUBF1_THMAVI ) != 0 )
					{
						if ( ppi->thmavi->IsOpen() )
						{
							// Save avi filename
							strcpy( ppi->thmavicachefile, ppi->thmavi->GetFileName() );
							ppi->thmavi->Close();

							// Save thumbnail avi filename
							strcpy( ppi->thmavicachefile, ppi->thmavi->GetFileName() );
							ppi->thmavi->Close();

						} // end if

					} // end if

					BOOL bPublished = FALSE;

					// Check for FTP
					if ( ppi->type == PUBTYPE_FTP ) bPublished = Ftp( ppi );

					// Check for Email
					else if ( ppi->type == PUBTYPE_EMAIL ) bPublished = Email( ppi );

					// Check for Disk
					else if ( ppi->type == PUBTYPE_DISK ) bPublished = Disk( ppi );

					if ( bPublished )
					{
						// Inform FRAME
						if ( ppi->type == PUBTYPE_FTP ) FRAME()->SetEvent( 2 );
						else if ( ppi->type == PUBTYPE_EMAIL ) FRAME()->SetEvent( 3 );
						else if ( ppi->type == PUBTYPE_DISK ) FRAME()->SetEvent( 4 );

						// Play sound if needed
						if ( ( ppi->f1 & PUBF1_PLAYSOUND ) != 0 )
						{	if ( *ppi->snd ) PLAYSOUND( ppi->snd );
							else PLAYSOUND( IDW_CAMERA );
						} // end if

					} // end if

					// Ensure cache files are gone
					if ( *ppi->avicachefile != 0 )
					{	CWinFile::Delete( ppi->avicachefile );
						*ppi->avicachefile = 0;
					} // end if
					if ( *ppi->thmavicachefile != 0 )
					{	CWinFile::Delete( ppi->thmavicachefile );
						*ppi->thmavicachefile = 0;
					} // end if

				} // end if

			} // end if

		} // end try

		// Try to return to a normal life if we can...
		catch( ... ) 
		{	_Log( MB_ICONERROR, "PublishThread()", "Assert" );	
			ASSERT( 0 ); 
		}
	
	} // end while

	m_bReset = FALSE;

	Sleep( 100 );

	return TRUE;
}