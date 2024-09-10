AutopatcherServer::ResultTypeAndBitstream* GetChangelistSinceDateCB(AutopatcherServer::ThreadData threadData, bool *returnOutput, void* perThreadData)
{
	AutopatcherRepositoryInterface *repository = (AutopatcherRepositoryInterface*)perThreadData;
	
	FileList addedFiles, deletedFiles;
	AutopatcherServer *server = threadData.server;

	//AutopatcherServer::ResultTypeAndBitstream *rtab = RakNet::OP_NEW<AutopatcherServer::ResultTypeAndBitstream>( _FILE_AND_LINE_ );
	AutopatcherServer::ResultTypeAndBitstream rtab;
	rtab.systemAddress=threadData.systemAddress;
// 	rtab.deletedFiles=RakNet::OP_NEW<FileList>( _FILE_AND_LINE_ );
// 	rtab.addedFiles=RakNet::OP_NEW<FileList>( _FILE_AND_LINE_ );
	rtab.deletedFiles=&deletedFiles;
	rtab.addedFiles=&addedFiles;

	// Query the database for a changelist since this date
	RakAssert(server);
	//if (server->repository->GetChangelistSinceDate(threadData.applicationName.C_String(), rtab.addedFiles, rtab.deletedFiles, threadData.lastUpdateDate.C_String(), currentDate))
	if (repository->GetChangelistSinceDate(threadData.applicationName.C_String(), rtab.addedFiles, rtab.deletedFiles, threadData.lastUpdateDate))
	{
		rtab.fatalError=false;
	}
	else
	{
		rtab.fatalError=true;
	}

	rtab.operation=AutopatcherServer::ResultTypeAndBitstream::GET_CHANGELIST_SINCE_DATE;
	rtab.currentDate=(double) time(NULL);
	// *returnOutput=true;
	// return rtab;

	if (rtab.fatalError==false)
	{
		if (rtab.deletedFiles->fileList.Size())
		{
			rtab.bitStream1.Write((unsigned char) ID_AUTOPATCHER_DELETION_LIST);
			rtab.deletedFiles->Serialize(&rtab.bitStream1);
		}

		if (rtab.addedFiles->fileList.Size())
		{
			rtab.bitStream2.Write((unsigned char) ID_AUTOPATCHER_CREATION_LIST);
			rtab.addedFiles->Serialize(&rtab.bitStream2);
			rtab.bitStream2.Write(rtab.currentDate);
			rtab.bitStream2.WriteCasted<double>(0);

			rtab.addedFiles->Clear();
		}
		else
		{
			rtab.bitStream2.Write((unsigned char) ID_AUTOPATCHER_FINISHED);
			rtab.bitStream2.Write(rtab.currentDate);
		}
	}
	else
	{
		rtab.bitStream2.Write((unsigned char) ID_AUTOPATCHER_REPOSITORY_FATAL_ERROR);
		StringCompressor::Instance()->EncodeString(repository->GetLastError(), 256, &rtab.bitStream2);	
	}
// 	RakNet::OP_DELETE(rtab.deletedFiles, _FILE_AND_LINE_);
// 	RakNet::OP_DELETE(rtab.addedFiles, _FILE_AND_LINE_);

	*returnOutput=false;

	if (rtab.bitStream1.GetNumberOfBitsUsed()>0)
		server->SendUnified(&(rtab.bitStream1), server->priority, RELIABLE_ORDERED, server->orderingChannel, rtab.systemAddress, false);
	if (rtab.bitStream2.GetNumberOfBitsUsed()>0)
		server->SendUnified(&(rtab.bitStream2), server->priority, RELIABLE_ORDERED, server->orderingChannel, rtab.systemAddress, false);

	server->DecrementPatchingUserCount();

	if (server->loadNotifier)
	{
		AutopatcherServerLoadNotifier::AutopatcherState autopatcherState;
		autopatcherState.requestsQueued=server->userRequestWaitingQueue.Size();
		autopatcherState.requestsWorking=server->patchingUserCount;

		AutopatcherServerLoadNotifier::GetChangelistResult getChangelistResult;
		if (rtab.fatalError==true)
			getChangelistResult=AutopatcherServerLoadNotifier::GCR_REPOSITORY_ERROR;
		else if (rtab.deletedFiles->fileList.Size()==0 && rtab.addedFiles->fileList.Size()==0)
			getChangelistResult=AutopatcherServerLoadNotifier::GCR_NOTHING_TO_DO;
		else if (rtab.deletedFiles->fileList.Size()==0)
			getChangelistResult=AutopatcherServerLoadNotifier::GCR_ADD_FILES;
		else if (rtab.addedFiles->fileList.Size()==0)
			getChangelistResult=AutopatcherServerLoadNotifier::GCR_DELETE_FILES;
		else
			getChangelistResult=AutopatcherServerLoadNotifier::GCR_ADD_AND_DELETE_FILES;

		server->loadNotifier->OnGetChangelistCompleted(rtab.systemAddress, getChangelistResult, &autopatcherState);
	}

	return 0;
}