/**
Called when async child completes with >=KErrNone
*/
void CImapOpSyncSubs::DoRunL()
	{
	// Finish if any server errors.
	if (iStatus.Int()!=KErrNone)
		{
		Complete(iStatus.Int());
		}

	switch(iNextSyncAction)
		{
	case CImapSyncManager::EProcessRemoteSubscription:
		{
		// Call returned from the LSUB command. Now process the list.
		// Update folder tree
		TInt folderscount = iImapListFolderInfo.Count();
		CImapListFolderInfo* folder;
		
		for(TInt loop = 0;loop < folderscount; ++loop)
			{
			folder = iImapListFolderInfo[loop];
			iSyncMan.AddSubscribedFolderFromInfoL(folder, iSession.LogId());
			}
		iSyncMan.CreateLocalFolderListL();

		// Now do the remote subscription
		iNextSyncAction = CImapSyncManager::EUpdateRemoteSubscription;
		CompleteSelf();
		SetActive();
		}
		break;
	case CImapSyncManager::EUpdateRemoteSubscription:
		{
		// Process the subscribed and unsubscribed list from the SyncManager.
		// This should be done after checking the online subscription list.

		RArray<TUint>* unsubscribeList = iSyncMan.GetUnSubscribedFolderToDoList();
		RArray<TUint>* subscribeList = iSyncMan.GetSubscribedFolderToDoList();

		// Any subscription to do?
		if (subscribeList->Count())
			{
			// Take it off the head
			TMsvId folderid = (*subscribeList)[0];
			subscribeList->Remove(0);

			// Subscribe to it
			CImapFolder* tempfolder = iSyncMan.GetTempFolderL(folderid);
			CleanupStack::PushL(tempfolder);
			iSession.SubscribeL(iStatus, tempfolder->FullFolderPathL());
			CleanupStack::PopAndDestroy(tempfolder);
			
			// set the subscribed flag for the folder.
			SetEntryL(folderid);
			TMsvEmailEntry entry = iServerEntry.Entry();
			entry.SetSubscribed(ETrue);
			ChangeEntryL(entry);
			
			SetActive();
			}
		// ...or unsubscription?
		else if (unsubscribeList->Count())
			{
			// Take it off the head
			TMsvId folderid = (*unsubscribeList)[0];
			unsubscribeList->Remove(0);

			// Unsubscribe from it
			CImapFolder* tempfolder = iSyncMan.GetTempFolderL(folderid);
			CleanupStack::PushL(tempfolder);
			iSession.UnsubscribeL(iStatus, tempfolder->FullFolderPathL());
			CleanupStack::PopAndDestroy(tempfolder);
			
			// clear the subscribed flag for the folder.
			SetEntryL(folderid);
			TMsvEmailEntry entry = iServerEntry.Entry();
			entry.SetSubscribed(EFalse);
			ChangeEntryL(entry);
			
			SetActive();
			}
		else
			{
			// All done.
			iNextSyncAction = CImapSyncManager::ENotSyncing;
			Complete(iStatus.Int());
			}
		}
		break;
	default:
	break;
		}
	}