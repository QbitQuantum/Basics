void FLiveEditorListenServer::Tick( float DeltaTime )
{
#if !UE_BUILD_SHIPPING
	if ( !PendingClients.IsEmpty() )
	{
		FSocket *Client = NULL;
		while( PendingClients.Dequeue(Client) )
		{
			Clients.Add(Client);
		}
	}

	// remove closed connections
	for (int32 ClientIndex = Clients.Num() - 1; ClientIndex >= 0; --ClientIndex)
	{
		if ( Clients[ClientIndex]->GetConnectionState() != SCS_Connected )
		{
			Clients.RemoveAtSwap(ClientIndex);
		}
	}

	//poll for data
	for ( TArray<class FSocket*>::TIterator ClientIt(Clients); ClientIt; ++ClientIt )
	{
		FSocket *Client = *ClientIt;
		uint32 DataSize = 0;
		while ( Client->HasPendingData(DataSize) )
		{
			FArrayReaderPtr Datagram = MakeShareable(new FArrayReader(true));
			Datagram->Init(FMath::Min(DataSize, 65507u));

			int32 BytesRead = 0;
			if ( Client->Recv(Datagram->GetData(), Datagram->Num(), BytesRead) )
			{
				nLiveEditorListenServer::FNetworkMessage Message;
				*Datagram << Message;

				ReplicateChanges( Message );
				TransactionHistory->AppendTransaction( Message.Payload.ClassName, Message.Payload.PropertyName, Message.Payload.PropertyValue );
			}
		}
	}

	//Check for any newly Tracked objects
	TArray<UObject*> NewTrackedObjects;
	ObjectCache.EvaluatePendingCreations( NewTrackedObjects );

	//If there are any newly tracked objects, stuff them with the list of latest changes we've accumulated so far
	for ( TArray<UObject*>::TIterator NewObjectIt(NewTrackedObjects); NewObjectIt; ++NewObjectIt )
	{
		UObject *NewObject = *NewObjectIt;
		TMap<FString,FString> Transactions;
		TransactionHistory->FindTransactionsForObject( NewObject, Transactions );

		for ( TMap<FString,FString>::TConstIterator TransactionIt(Transactions); TransactionIt; ++TransactionIt )
		{
			const FString &PropertyName = (*TransactionIt).Key;
			const FString &PropertyValue = (*TransactionIt).Value;
			nLiveEditorListenServer::SetPropertyValue( NewObject, PropertyName, PropertyValue );
		}
	}
	
#endif
}