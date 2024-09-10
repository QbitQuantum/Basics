// **************************************************************************
// Function:   Preflight
// Purpose:    Checks parameters for availability and consistence with
//             input signal properties; requests minimally required properties
//             for the output signal; checks whether resources are available.
// Parameters: References to input and output signal properties.
// Returns:    N/A
// **************************************************************************
void NicoletOneADC::Preflight( const SignalProperties&,
                                   SignalProperties& Output ) const
{
	// Start communications with the object
	CNicoletThread *NT = dynamic_cast< CNicoletThread* >( AfxBeginThread( RUNTIME_CLASS( CNicoletThread ) ) );
	if( NT == NULL )
		bcierr << "Could not begin NicoletOne Acquisition Thread." << endl;

	Sleep( 1000 ); // We should wait for the thread to initialize.

	// See if we're connected or not...
	if( !NT->Connected() )
	{
		// Spit out an error
		bcierr << "Couldn't connect to the device.  Device may have a connection already.  Try again later." << endl;

		// End Communications with the object
		NT->PostThreadMessageA(WM_QUIT, 0, 0 );
		WaitForSingleObject( NT->m_hThread, INFINITE );
		NT = NULL;
		return;
	}

	// Pull Parameters
	int sampleBlockSize = Parameter( "SampleBlockSize" );

	// Check the number of channels
	int numChannels = 0;
	while( NT->GetNumChannels( &numChannels ) )
		Sleep( 10 );
	if( Parameter( "SourceCh" ) != numChannels )
		bcierr << "Set SourceCh = " << numChannels << "; it is reported by the device to be " << numChannels << endl;

	// Check Sampling Rate
	double rate = 0.0f;
	while( NT->GetSampleRate( &rate ) )
		  Sleep( 10 );
	if( Parameter( "SamplingRate" ) != (int)rate )
		bcierr << "Set SamplingRate = " << (int)rate << "; it is reported by the device to be " << (int)rate << endl;

	// Check DC Offset List
	double *offsetValues = NULL;
	while( NT->GetDCOffset( offsetValues ) )
		  Sleep( 10 );
	if( Parameter( "SourceChOffset" )->NumValues() != numChannels )
		  bcierr << "There should be " << numChannels << " entries in SourceChOffset." << endl;
	else
	{
		// Check individual entries
		for( int i = 0; i < numChannels; i++ )
		{
			if( Parameter( "SourceChOffset" )( i ) != 0 )
				bcierr << "Entry number " << i+1 << " in SourceChOffset should be 0." << endl;
		}
	}
	delete [] offsetValues;

	// Get Resolution List, Set Param
	double* resolutionValues = NULL;
	while( NT->GetDCResolution( resolutionValues ) )
		Sleep( 10 );
	if( Parameter( "SourceChGain" )->NumValues() != numChannels )
		  bcierr << "There should be " << numChannels << " entries in SourceChGain." << endl;
	else
	{
		// Check individual entries
		for( int i = 0; i < numChannels; i++ )
		{
			//if( fabs( Parameter( "SourceChGain" )( i ) - resolutionValues[i]) > 0.00001 )
			//	bcierr << "Entry number " << i+1 << " in SourceChGain should be " << resolutionValues[i] << endl;
			if( fabs( Parameter( "SourceChGain" )( i ) - ( double )1 ) > 0.00001 )
				bcierr << "Entry number " << i+1 << " in SourceChGain should be 1." << endl;
		}
	}
	delete [] resolutionValues;

	// TODO: Set/Check Channel Names

	// End Communications with the object
	NT->PostThreadMessageA(WM_QUIT, 0, 0 );
	WaitForSingleObject( NT->m_hThread, INFINITE );
	NT = NULL;

	// This sleep is needed for the socket to successfully disconnect
	Sleep( 1000 );

	// Requested output signal properties.
	Output = SignalProperties( Parameter( "SourceCh" ), sampleBlockSize, SignalType::float32 );
}