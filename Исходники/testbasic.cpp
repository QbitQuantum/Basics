void TestBasic::CreateSaraPIN()
{
	// Similar to CreateAlbertPIN, but using different methods
	// Creates a woman named Sara, age 47
	//
	// Demonstrates ISession::alloc, createPIN, commitPINs, modifyPIN etc
	// Focuses on the tricky memory handling considerations

	// Strings have to be allocated using store allocator
	char * pSaraMisspelledNameBuffer = (char*)mSession->malloc( strlen( "SaRRra" ) + 1 ) ;
	strcpy(pSaraMisspelledNameBuffer, "SaRRra" ) ; 

	// Create the pin and set the name immediately
	// Note: createPIN is a special case.  
	// We have to allocate the memory for the store because
	// it doesn't copy the data.  (otherwise you will see a crash 
	// when we call IPin->modify below).  See coverage of MODE_COPY_VALUES elsewhere.
	Value * pName = (Value*)mSession->malloc( sizeof(Value) ) ;;
	pName->set( pSaraMisspelledNameBuffer ) ;
	pName->property = mProps[NameIndex].uid ;

	IPIN * pSaraPin;
	TVERIFYRC(mSession->createPIN( pName, 1, &pSaraPin, MODE_COPY_VALUES|MODE_PERSISTENT));
	TVERIFY( pSaraPin != NULL ) ;
	TVERIFY( pSaraPin->getNumberOfProperties() == 1 ) ;
	
	PID saraPID = pSaraPin->getPID() ;

	// Add the age as a second call
	// NOTE: For calls to modify the structure does not need to be allocated

	Value moreInfo[2] ;
	moreInfo[0].set( false ) ; moreInfo[0].property = mProps[GenderIndex].uid ;
	moreInfo[1].set( 47 ) ; moreInfo[1].property = mProps[GenderIndex].uid ;
	pSaraPin->modify( moreInfo, 2 ) ;

	pName = NULL ; // pName buffer has been freed by store

	// commitPINs will copy the information into database
	// so we will own the memory again
	//TVERIFYRC( mSession->commitPINs( &pSaraPin, 1 ) );
	TVERIFY( (pSaraPin->getFlags()&PIN_PERSISTENT)!=0 ) ;

	// Now PID should be valid
	saraPID = pSaraPin->getPID() ;
	TVERIFY( saraPID.pid != STORE_INVALID_URIID ) ;
	TVERIFY( saraPID.ident != STORE_INVALID_IDENTITY ) ;

	// We own the memory again
	pSaraPin->destroy() ;
	pSaraPin = NULL ;

	// Fix Sara's misspelled name
	// NOTE: For modifyPin we can use the stack for the memory
	Value name2; name2.set( "Sara" ) ; name2.property = mProps[NameIndex].uid ;

	TVERIFYRC(mSession->modifyPIN( saraPID, &name2, 1 )) ;

	// Verification
	IPIN * pSaraPin2 = mSession->getPIN( saraPID ) ;
	TVERIFY( pSaraPin2->getNumberOfProperties() == 2 ) ;
	
	const Value * pValLookup = pSaraPin2->getValue( mProps[NameIndex].uid ) ;
	TVERIFY( pValLookup != NULL ) ;
	TVERIFY( 0 == strcmp( pValLookup->str, "Sara" ) ) ;

	pSaraPin2->destroy() ;
}