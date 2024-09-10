/**
 * Add a client to the waiting queue for uploads.
 *
 * @param client address of the client that should be added to the waiting queue
 *
 * @param bIgnoreTimelimit don't check time limit to possibly ban the client.
 */
void CUploadQueue::AddClientToQueue(CUpDownClient* client, bool bIgnoreTimelimit)
{
	//This is to keep users from abusing the limits we put on lowID callbacks.
	//1)Check if we are connected to any network and that we are a lowID.
	//(Although this check shouldn't matter as they wouldn't have found us..
	// But, maybe I'm missing something, so it's best to check as a precaution.)
	//2)Check if the user is connected to Kad. We do allow all Kad Callbacks.
	//3)Check if the user is in our download list or a friend..
	//We give these users a special pass as they are helping us..
	//4)Are we connected to a server? If we are, is the user on the same server?
	//TCP lowID callbacks are also allowed..
	//5)If the queue is very short, allow anyone in as we want to make sure
	//our upload is always used.
	if (theApp.IsConnected() 
		&& theApp.IsFirewalled()
		&& !client->GetKadPort()
		&& client->GetDownloadState() == DS_NONE 
		&& !client->IsFriend()
		&& theApp.serverconnect
		&& !theApp.serverconnect->IsLocalServer(client->GetServerIP(),client->GetServerPort())
		&& GetWaitingUserCount() > 50)
		return;
	client->AddAskedCount();
	client->SetLastUpRequest();
	if (!bIgnoreTimelimit)
		client->AddRequestCount(client->GetUploadFileID());
	if (client->IsBanned())
		return;
	uint16 cSameIP = 0;
	// check for double
	POSITION pos1, pos2;
	for (pos1 = waitinglist.GetHeadPosition();( pos2 = pos1 ) != NULL;)
	{
		waitinglist.GetNext(pos1);
		CUpDownClient* cur_client= waitinglist.GetAt(pos2);
		if (cur_client == client)
		{	
			if (client->m_bAddNextConnect && AcceptNewClient(client->m_bAddNextConnect))
			{
				//Special care is given to lowID clients that missed their upload slot
				//due to the saving bandwidth on callbacks.
				if(thePrefs.GetLogUlDlEvents())
					AddDebugLogLine(true, _T("Adding ****lowid when reconnecting. Client: %s"), client->DbgGetClientInfo());
				client->m_bAddNextConnect = false;
				RemoveFromWaitingQueue(client, true);
				// statistic values // TODO: Maybe we should change this to count each request for a file only once and ignore reasks
				CKnownFile* reqfile = theApp.sharedfiles->GetFileByID((uchar*)client->GetUploadFileID());
				if (reqfile)
					reqfile->statistic.AddRequest();
				AddUpNextClient(_T("Adding ****lowid when reconnecting."), client);
				return;
			}
			client->SendRankingInfo();
			theApp.emuledlg->transferwnd->queuelistctrl.RefreshClient(client);
			return;			
		}
		else if ( client->Compare(cur_client) ) 
		{
			theApp.clientlist->AddTrackClient(client); // in any case keep track of this client

			// another client with same ip:port or hash
			// this happens only in rare cases, because same userhash / ip:ports are assigned to the right client on connecting in most cases
			if (cur_client->credits != NULL && cur_client->credits->GetCurrentIdentState(cur_client->GetIP()) == IS_IDENTIFIED)
			{
				//cur_client has a valid secure hash, don't remove him
				if (thePrefs.GetVerbose())
					AddDebugLogLine(false, GetResString(IDS_SAMEUSERHASH), client->GetUserName(), cur_client->GetUserName(), client->GetUserName());
				return;
			}
			if (client->credits != NULL && client->credits->GetCurrentIdentState(client->GetIP()) == IS_IDENTIFIED)
			{
				//client has a valid secure hash, add him remove other one
				if (thePrefs.GetVerbose())
					AddDebugLogLine(false, GetResString(IDS_SAMEUSERHASH), client->GetUserName(), cur_client->GetUserName(), cur_client->GetUserName());
				RemoveFromWaitingQueue(pos2,true);
				if (!cur_client->socket)
				{
					if(cur_client->Disconnected(_T("AddClientToQueue - same userhash 1")))
						delete cur_client;
				}
			}
			else
			{
				// remove both since we do not know who the bad one is
				if (thePrefs.GetVerbose())
					AddDebugLogLine(false, GetResString(IDS_SAMEUSERHASH), client->GetUserName() ,cur_client->GetUserName(), _T("Both"));
				RemoveFromWaitingQueue(pos2,true);	
				if (!cur_client->socket)
				{
					if(cur_client->Disconnected(_T("AddClientToQueue - same userhash 2")))
						delete cur_client;
				}
				return;
			}
		}
		else if (client->GetIP() == cur_client->GetIP())
		{
			// same IP, different port, different userhash
			cSameIP++;
		}
	}
	if (cSameIP >= 3)
	{
		// do not accept more than 3 clients from the same IP
		if (thePrefs.GetVerbose())
			DEBUG_ONLY( AddDebugLogLine(false,_T("%s's (%s) request to enter the queue was rejected, because of too many clients with the same IP"), client->GetUserName(), ipstr(client->GetConnectIP())) );
		return;
	}
	else if (theApp.clientlist->GetClientsFromIP(client->GetIP()) >= 3)
	{
		if (thePrefs.GetVerbose())
			DEBUG_ONLY( AddDebugLogLine(false,_T("%s's (%s) request to enter the queue was rejected, because of too many clients with the same IP (found in TrackedClientsList)"), client->GetUserName(), ipstr(client->GetConnectIP())) );
		return;
	}
	// done

	// statistic values // TODO: Maybe we should change this to count each request for a file only once and ignore reasks
	CKnownFile* reqfile = theApp.sharedfiles->GetFileByID((uchar*)client->GetUploadFileID());
	if (reqfile)
		reqfile->statistic.AddRequest();

	// emule collection will bypass the queue
	if (reqfile != NULL && CCollection::HasCollectionExtention(reqfile->GetFileName()) && reqfile->GetFileSize() < (uint64)MAXPRIORITYCOLL_SIZE
		&& !client->IsDownloading() && client->socket != NULL && client->socket->IsConnected())
	{
		client->SetCollectionUploadSlot(true);
		RemoveFromWaitingQueue(client, true);
		AddUpNextClient(_T("Collection Priority Slot"), client);
		return;
	}
	else
		client->SetCollectionUploadSlot(false);

   // cap the list
    // the queue limit in prefs is only a soft limit. Hard limit is 25% higher, to let in powershare clients and other
    // high ranking clients after soft limit has been reached
    uint32 softQueueLimit = thePrefs.GetQueueSize();
    uint32 hardQueueLimit = thePrefs.GetQueueSize() + max(thePrefs.GetQueueSize()/4, 200);

    // if soft queue limit has been reached, only let in high ranking clients
    if ((uint32)waitinglist.GetCount() >= hardQueueLimit ||
        (uint32)waitinglist.GetCount() >= softQueueLimit && // soft queue limit is reached
        (client->IsFriend() && client->GetFriendSlot()) == false && // client is not a friend with friend slot
        client->GetCombinedFilePrioAndCredit() < GetAverageCombinedFilePrioAndCredit()) { // and client has lower credits/wants lower prio file than average client in queue

        // then block client from getting on queue
		return;
	}
	if (client->IsDownloading())
	{
		// he's already downloading and wants probably only another file
		if (thePrefs.GetDebugClientTCPLevel() > 0)
			DebugSend("OP__AcceptUploadReq", client);
		Packet* packet = new Packet(OP_ACCEPTUPLOADREQ,0);
		theStats.AddUpDataOverheadFileRequest(packet->size);
		client->SendPacket(packet, true);
		return;
	}
	if (waitinglist.IsEmpty() && ForceNewClient(true))
	{
		AddUpNextClient(_T("Direct add with empty queue."), client);
	}
	else
	{
		waitinglist.AddTail(client);
		client->SetUploadState(US_ONUPLOADQUEUE);
		theApp.emuledlg->transferwnd->queuelistctrl.AddClient(client,true);
		theApp.emuledlg->transferwnd->ShowQueueCount(waitinglist.GetCount());
		client->SendRankingInfo();
	}
}