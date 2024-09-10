void TCmdSetUNSAFTimers::SetValuesToRepositoryL(
	CRepository& aRepository,
	TInt aStatus,
	TUint32 aKey,
	TInt aBindingRequestInterval,
	TInt aUdpKeepAliveInterval,
	TInt aTcpKeepAliveInterval )
	{
	User::LeaveIfError(
		aRepository.StartTransaction(
			CRepository::EConcurrentReadWriteTransaction ) );
    aRepository.CleanupCancelTransactionPushL();

	TPtrC8 iapName = ExtractTextL( KParamIAPName, EFalse );
	if( iapName != KNullDesC8 )
		{
		TInt iapId = iContext.IAPIdL( iapName );
		if ( aStatus == KErrNotFound )
			{
			aKey = CreateNewKeyL( aRepository,
                                  KUNSAFProtocolsIAPIdMask,
                                  KUNSAFProtocolsIAPTableMask );
			WriteL( aRepository, KUNSAFProtocolsIAPIdMask | aKey, iapId );
			}
		WriteIapParamsL( aRepository,
					 	 aKey,
					 	 aBindingRequestInterval,
					 	 aUdpKeepAliveInterval,
					 	 aTcpKeepAliveInterval );
		}
	else
		{
		// Since IAP was not given, domain is now mandatory
		TPtrC8 domainName = ExtractTextL( KParamDomainName, ETrue );
		if ( aStatus == KErrNotFound )
			{
		    aKey = CreateNewKeyL( aRepository,
                                  KUNSAFProtocolsDomainMask,
                                  KUNSAFProtocolsDomainTableMask );
		    WriteL( aRepository, KUNSAFProtocolsDomainMask | aKey, domainName );
			}
	    WriteDomainParamsL( aRepository, 
							aKey,
							aUdpKeepAliveInterval,
							aTcpKeepAliveInterval );
		}

	TUint32 dummy( 0 );
    User::LeaveIfError( aRepository.CommitTransaction( dummy ) );
    CleanupStack::Pop( 1 ); // transaction
	}