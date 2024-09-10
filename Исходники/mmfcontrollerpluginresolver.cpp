EXPORT_C void CMMFFormatSelectionParameters::SetMatchToFileNameL(const TDesC& aFileName)
	{
	delete iMatchReqData;
	iMatchReqData = NULL;
	iMatchDataType = EMatchAny;	
	// Extract the extension from the data passed in

	// Parse the path and extract the extension
	_LIT( KDot, "." ) ;
	_LIT8( KDot8, "." );

	// If there is no dot "." in aFileName then assume that we have been passed the extension only (if KMaxExtLen or less)
	if ( (aFileName.Length() <= KMaxExtLen) && (aFileName.Find( KDot ) == KErrNotFound) )
		{
		RBuf8 temp;
		CleanupClosePushL(temp);
		temp.CreateL(aFileName.Length()+1);
		User::LeaveIfError(CnvUtfConverter::ConvertFromUnicodeToUtf8(temp, aFileName));
		temp.Insert(0,KDot8);
		
		iMatchReqData = CMatchData::CreateL();
		iMatchReqData->SetMatchDataL(temp);
		
		CleanupStack::PopAndDestroy(&temp);
		
		}
	else if ( aFileName.Find( KDot ) == 0 )  // the first character is dot so assume extension only
		{
		RBuf8 temp;
		CleanupClosePushL(temp);
		temp.CreateL(aFileName.Length());
		User::LeaveIfError(CnvUtfConverter::ConvertFromUnicodeToUtf8(temp, aFileName));
			
		iMatchReqData = CMatchData::CreateL();
		iMatchReqData->SetMatchDataL(temp);
		
		CleanupStack::PopAndDestroy(&temp);
		
		}
	else // We have been given the whole filename.  Use TParse to extract the extension.
		{
		TParse parser ;
		parser.Set( aFileName, NULL, NULL ) ;
		if ( !( parser.NamePresent() ) )
			User::Leave( KErrBadName ) ;
		if ( !( parser.PathPresent() ) )
			{
			RFs fsSession ;
			User::LeaveIfError(fsSession.Connect());
			TInt error = fsSession.Parse(aFileName, parser);
			fsSession.Close();
			User::LeaveIfError(error);
			}
		// Parser should now have the full filename and path
		TPtrC extension = parser.Ext();
		
		RBuf8 temp;
		CleanupClosePushL(temp);
		temp.CreateL(extension.Length());
		User::LeaveIfError(CnvUtfConverter::ConvertFromUnicodeToUtf8(temp, extension));
			
		iMatchReqData = CMatchData::CreateL();
		iMatchReqData->SetMatchDataL(temp);
		
		CleanupStack::PopAndDestroy(&temp);
		
		}

	// If we're here, we must now have the file extension
	iMatchDataType = EMatchFileExtension;
	}