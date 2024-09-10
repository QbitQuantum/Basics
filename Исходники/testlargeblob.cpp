PID TestLargeBlob::createFilePin( int pageSize, int pagePerPageGroup, int testFileSizeInPages )
{
	// Break up the file blocks over multiple elements in a collection
	// to try to avoid the I/O bottleneck of doing OP_EDIT appends

	mLogger.out() << "Creating file of size " << std::dec << pageSize * testFileSizeInPages << " (0x" << (pageSize * testFileSizeInPages) << ")" << endl ;
	mLogger.out() << "Pages: " << std::dec << testFileSizeInPages << endl ;

	int cntExpectedElements = 1 + ( testFileSizeInPages / pagePerPageGroup ) ;

	if ( cntExpectedElements > 1 )
	{
		mLogger.out() << "Using " << cntExpectedElements << " collection elements" << endl ; 
	}
	else
	{
		mLogger.out() << "As a single large property value" << endl ; 
	}

	// Bogus content for each page of the file
	unsigned char * filePage = (unsigned char *) malloc( pageSize ) ;
	memset( filePage, 'A', pageSize ) ;

	// Big chunk of memory for maximum number of elements per collection item, 
	// e.g. 8 MB
	unsigned char * tempGroupBuffer = NULL ;
	
	if ( cntExpectedElements > 1 )
	{
		tempGroupBuffer = (unsigned char*)malloc( pageSize * pagePerPageGroup ) ;
		TVERIFY( tempGroupBuffer != NULL ) ;
	}
   
	RC rc ;
	PID myPID;IPIN *pin;
	TVERIFYRC(mSession->createPIN(NULL, 0,&pin,MODE_PERSISTENT));
	myPID = pin->getPID();
	if(pin!=NULL) pin->destroy();
	
	int currentSize = 0 ; // Assuming that caller is tracking file size

	ElementID endElement = STORE_COLLECTION_ID; // Optimization, otherwise code could 
						   // use the CNavigator to get the last element in the collection

	for ( int i = 0 ; i < testFileSizeInPages ; i++ )
	{
		long lStartTime = getTimeInMs() ;

		// for test purposes put the index number at beginning
		*((int *)filePage) = i;

		Value v ;
		if ( currentSize == 0 )
		{
			// first block
			v.set(filePage,pageSize) ; v.property = mFileContent ;

#if 0
			if ( cntExpectedElements > 253 )
			{
				// Workaround to #8357 
				v.meta = META_PROP_SSTORAGE ;
			}
#endif

			TVERIFYRC(mSession->modifyPIN(myPID,&v,1)) ;

			endElement = v.eid ;
		}
		else
		{	
			int group = i / pagePerPageGroup ;
			int arrayPos = i % pagePerPageGroup ;

			if ( arrayPos == 0 )
			{
				// Add new collection item
				v.set(filePage,pageSize) ; v.property = mFileContent ;
				v.op = OP_ADD ;

				TVERIFYRC(rc = mSession->modifyPIN(myPID,&v,1)) ;
				if ( rc != RC_OK )
				{
					// RC_NOMEM error seen when local collection reaches
					// 253 elements
					mLogger.out() << "OP_ADD failed page " << i << endl ;
					return myPID ;
				}

				endElement = v.eid ;
			}
			else if ( group == 0 )
			{
#if 0
				// OP_EDIT can work if we only have a single (non-collection)
				// property value.  This is the normal pifs mechanism

				// (For production code it would have to check whether the single
				// element is in a colleciton or not)

				v.setEdit(filePage,pageSize,arrayPos * pageSize,0); 
				v.setPropID(mFileContent);
				v.eid = endElement ;  // Attempt to say which item to edit
				TVERIFYRC(mSession->modifyPIN(myPID,&v,1)) ;
#endif
			}
			else
			{
#if 0
				// Try to append to the existing collection item
#if TEST_8359
				// OP_EDIT not supported on element of a collection
				// See #8359.  Without this support we have to go for a potentially slower
				// workaround

				//ERROR:OP_EDIT for a non-string property 29, slot: 1, page: 0000000A
				//*** failed with RC 17(RC_TYPE) *** 
				v.setEdit(filePage,pageSize,arrayPos * pageSize,0); 
				v.setPropID(mFileContent);
				v.eid = endElement ;  // Attempt to say which item to edit
				TVERIFYRC(mSession->modifyPIN(myPID,&v,1)) ;
#else
				// Replace the value, unfortunately requires several memory copies

				// Get a copy of existing data
				Value fileData ;
				TVERIFYRC( mSession->getValue( fileData, myPID, mFileContent, endElement ) );

				if ( fileData.type == VT_BSTR )
				{
					TVERIFY(fileData.length == arrayPos * pageSize ) ;
					memcpy(tempGroupBuffer,fileData.bstr,fileData.length) ;
					mSession->free( const_cast<unsigned char*>(fileData.bstr) ) ;
				}
				else
				{
					TVERIFY( fileData.type == VT_STREAM ) ;
					TVERIFY( fileData.stream.is->length() == arrayPos * pageSize ) ;
					fileData.stream.is->read(tempGroupBuffer, arrayPos * pageSize ); 
					fileData.stream.is->destroy() ;
				}

#if 0
				// Delete the collection item
				// WARNING: Until #8358 fixed, the data is not reclaimed in the
				// store file and this is not effective.
				v.setDelete( mFileContent, endElement ) ;
				TVERIFYRC(mSession->modifyPIN(myPID, &v, 1)) ;
#endif

				// Append the new chunk to our in memory copy
				memcpy( tempGroupBuffer + ( arrayPos * pageSize ), filePage,pageSize ) ;

				// Reset the collection item with the extra data
				v.set(tempGroupBuffer,((1+arrayPos)*pageSize)); v.property = mFileContent ;
				v.op = OP_SET ;
				v.eid = endElement ;
				TVERIFYRC(mSession->modifyPIN(myPID,&v,1)) ;

				// The old EID is not reused
				//endElement = v.eid ;  
#endif
#endif
			}
		}

		currentSize += pageSize ;

		// REVIEW: difficult to show the time because results can vary
		// between too fast to measure and >1 second
		long lEndTime = getTimeInMs() - lStartTime ;

		if ( lEndTime > 10 )
		{
			mLogger.out() << " " << lEndTime << " " ;
		}
		else
		{
			mLogger.out() << "." ;
		}
	}

	delete( filePage ) ;
	delete( tempGroupBuffer ) ;

	return myPID ;
}