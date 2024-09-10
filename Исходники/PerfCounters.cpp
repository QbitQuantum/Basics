void FPerfCounters::TickSocket(float DeltaTime)
{
	checkf(Socket != nullptr, TEXT("FPerfCounters::TickSocket() called without a valid socket!"));

	// accept any connections
	static const FString PerfCounterRequest = TEXT("FPerfCounters Request");
	FSocket* IncomingConnection = Socket->Accept(PerfCounterRequest);
	if (IncomingConnection)
	{
		if (0)
		{
			TSharedRef<FInternetAddr> FromAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
			IncomingConnection->GetPeerAddress(*FromAddr);
			UE_LOG(LogPerfCounters, Log, TEXT("New connection from %s"), *FromAddr->ToString(true));
		}

		// make sure this is non-blocking
		IncomingConnection->SetNonBlocking(true);

		new (Connections) FPerfConnection(IncomingConnection);
	}

	TArray<FPerfConnection> ConnectionsToClose;
	for (FPerfConnection& Connection : Connections)
	{
		FSocket* ExistingSocket = Connection.Connection;
		if (ExistingSocket && ExistingSocket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::Zero()))
		{
			// read any data that's ready
			// NOTE: this is not a full HTTP implementation, just enough to be usable by curl
			uint8 Buffer[2 * 1024] = { 0 };
			int32 DataLen = 0;
			if (ExistingSocket->Recv(Buffer, sizeof(Buffer) - 1, DataLen, ESocketReceiveFlags::None))
			{
				FResponse Response;
				if (ProcessRequest(Buffer, DataLen, Response))
				{
					if (SendAsUtf8(ExistingSocket, Response.Header))
					{
						if (!SendAsUtf8(ExistingSocket, Response.Body))
						{
							UE_LOG(LogPerfCounters, Warning, TEXT("Unable to send full HTTP response body"));
						}
					}
					else
					{
						UE_LOG(LogPerfCounters, Warning, TEXT("Unable to send HTTP response header: %s"), *Response.Header);
					}
				}
			}
			else
			{
				UE_LOG(LogPerfCounters, Warning, TEXT("Unable to immediately receive request header"));
			}

			ConnectionsToClose.Add(Connection);
		}
		else if (Connection.ElapsedTime > 5.0f)
		{
			ConnectionsToClose.Add(Connection);
		}

		Connection.ElapsedTime += DeltaTime;
	}

	for (FPerfConnection& Connection : ConnectionsToClose)
	{
		Connections.RemoveSingleSwap(Connection);

		FSocket* ClosingSocket = Connection.Connection;
		if (ClosingSocket)
		{
			// close the socket (whether we processed or not)
			ClosingSocket->Close();
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClosingSocket);
			
			if (0)
			{
				UE_LOG(LogPerfCounters, Log, TEXT("Closed connection."));
			}
		}
	}
}