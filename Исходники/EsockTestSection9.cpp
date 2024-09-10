/**
   Receive data on a socket via RecvFrom

   @param aSocket The socket to recevie data from
   @param aDesc Descriptor to receive the data into
   @param anAddress On success, contains the address from which data was received
   @return ETrue on success, EFalse on failure
*/
TBool CEsockTest9_6::PerformRecv( RSocket& aSocket, TDes8& aDesc, TSockAddr& anAddress )
	{
	TRequestStatus socketStatus;

	aSocket.RecvFrom( aDesc, anAddress, 0, socketStatus );
	WaitFor( socketStatus, KTimerPeriod );

	Logger().WriteFormat(_L("UDP Recv returns %d"), socketStatus.Int() );

	if( socketStatus == KRequestPending )
		{
		aSocket.CancelRecv();
		Logger().WriteFormat(_L("Timeout on UDP Recv"));
		User::WaitForRequest( socketStatus );
		return EFalse;
		}

	if( socketStatus != KErrNone )
		{
		Logger().WriteFormat(_L("UDP Recv failed with error %d"), socketStatus.Int() );
		return EFalse;
		}

	return ETrue;
	}