/**
*
* DoTestStepL
* This method tests the controllers reset function
*
*/
TVerdict CTestStepResetController::DoTestStepL( void )
	{
	__MM_HEAP_MARK;
	
	TVerdict result = EPass;
	
	_LIT( KTestPlay, "Reset Test");
	Log( KTestPlay );
	
	_LIT( KTestStepReset, "This test checks a controller reset");
	Log( KTestStepReset );
	
	// [ audio file to play ]
	_LIT(KTestWavFile, "newmail.wav");
	SetReadFileNameL( KTestWavFile );
	
   	TInt errorCode = iController.Open(KUidCustomTestAudioPlugin, iPriority);
	User::LeaveIfError( errorCode );
	
	//[ok lets reset the controller from it initial state]
	errorCode = iController.Reset();
	User::LeaveIfError( errorCode );
	//[ search for reset event ]
	TMMFEvent resetEvent( KResetTestId, KErrNone);
	result = SearchForEvent( resetEvent );
	if( result == EFail )
		{
		return result;
		}
	
	//[ lets try a second reset ]
	errorCode = iController.Reset();
	User::LeaveIfError( errorCode );
	//[ search for reset event ]
	result = SearchForEvent( resetEvent );
	if( result == EFail )
		{
		return result;
		}
	
	//[ add data source and sink and prime the controller ]
    errorCode = iController.AddDataSource(KUidMmfFileSource, ReadFileConfig());
	User::LeaveIfError( errorCode );
	
	errorCode =	iController.AddDataSink(KUidMmfAudioOutput, KNullDesC8);
    User::LeaveIfError( errorCode );
	
	//[ok lets reset the controller from it initial state]
	errorCode = iController.Reset();
	User::LeaveIfError( errorCode );
	
	//[ search for reset event ]
	result = SearchForEvent( resetEvent );
	if( result == EFail )
		{
		return result;
		}
	
	//[ lets try a second reset ]
	errorCode = iController.Reset();
	User::LeaveIfError( errorCode );
	//[ search for reset event ]
	result = SearchForEvent( resetEvent );
	if( result == EFail )
		{
		return result;
		}

	//[ add data source and sink and prime the controller ]
    errorCode = iController.AddDataSource(KUidMmfFileSource, ReadFileConfig());
	User::LeaveIfError( errorCode );
	
	errorCode =	iController.AddDataSink(KUidMmfAudioOutput, KNullDesC8);
    User::LeaveIfError( errorCode );
	
	errorCode =	iController.Prime();
	User::LeaveIfError( errorCode );
	
	// [ wait for and process the return event from the audio output ]
	TMMFEvent primeEvent( KPrimeTestId, KErrNone);
	result = SearchForEvent( primeEvent );
	if( result == EFail )
		{
		return result;
		}
	
	//[ lets reset again in the primed state ]
	errorCode = iController.Reset();
	User::LeaveIfError( errorCode );
	
	//[ search for reset event ]
	result = SearchForEvent( resetEvent );
	if( result == EFail )
		{
		return result;
		}
	
	// [ get back to primed state ]
	//[ add data source and sink and prime the controller ]
    errorCode = iController.AddDataSource(KUidMmfFileSource, ReadFileConfig());
	User::LeaveIfError( errorCode );
	
	errorCode =	iController.AddDataSink(KUidMmfAudioOutput, KNullDesC8);
    User::LeaveIfError( errorCode );
	
	errorCode =	iController.Prime();
	User::LeaveIfError( errorCode );
	result = SearchForEvent( primeEvent );
	if( result == EFail )
		{
		return result;
		}

    User::LeaveIfError( iController.Play() );
	
	// note this test does not wait around 
	// to detect that the audio has been played
	// [ now process the confirmation event that play has reached audio output
	//   this is the raison detre of the test ]
	TMMFEvent playEvent( KPlayTestId, KErrNone );
	result = SearchForEvent( playEvent );
	if( result == EFail )
		{
		return result;
		}
	
	//[ lets reset again in the primed state ]
	errorCode = iController.Reset();
	User::LeaveIfError( errorCode );
	
	//[ search for reset event ]
	result = SearchForEvent( resetEvent );
	if( result == EFail )
		{
		return result;
		}

	errorCode = iController.Reset();
	User::LeaveIfError( errorCode );
	
	//[ search for reset event ]
	result = SearchForEvent( resetEvent );
	if( result == EFail )
		{
		return result;
		}

	//[ ensure the controller is unloaded so that it does 
	// not interfere with the following test ]
	// There is error in this code and the stop followed by reset
	// ensure the controller resources are released.
	iController.Stop();
	iController.Reset();
	iController.Close();  
	
	__MM_HEAP_MARKEND;
	   
	// [test steps return a result]
	return result;
	}