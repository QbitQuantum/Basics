//
// Wait for registration message and forward proper arbiter.
//
VOID
DraidReceptionThreadProc(
	IN PVOID Param
) {
	PDRAID_REMOTE_CLIENT_CONNECTION Connection = Param;
	LARGE_INTEGER Timeout;
	NTSTATUS status;
	DRIX_REGISTER RegMsg;
	DRIX_HEADER Reply = {0};
	PDRAID_ARBITER_INFO Arbiter;
	KIRQL	oldIrql;
	PLIST_ENTRY listEntry;
	BOOLEAN Disconnect = TRUE;
	BOOLEAN MatchFound;
	ULONG		result;
	
	Connection->TdiReceiveContext.Irp = NULL;
	KeInitializeEvent(&Connection->TdiReceiveContext.CompletionEvent, NotificationEvent, FALSE) ;
	
	// Wait for network event or short timeout
	status = LpxTdiRecvWithCompletionEvent(
					Connection->ConnectionFileObject,
					&Connection->TdiReceiveContext,
					(PUCHAR)&RegMsg,
					sizeof(DRIX_REGISTER),
					0,
					NULL,
					NULL
					);
	if(!NT_SUCCESS(status)) {
		KDPrintM(DBG_LURN_INFO, ("LpxTdiRecvWithCompletionEvent returned %d.\n", status));
		goto out;
	}

	Timeout.QuadPart =  - HZ * 5;
	
	status = KeWaitForSingleObject(
		&Connection->TdiReceiveContext.CompletionEvent,
		Executive, KernelMode, 	FALSE, &Timeout);
	
	if (status == STATUS_SUCCESS) {
		UCHAR ResultCode;
		
		//
		// Data received. Check validity and forward channel to arbiter.
		//
		if (Connection->TdiReceiveContext.Result != sizeof(DRIX_REGISTER)) {
			KDPrintM(DBG_LURN_INFO, ("Registration packet size is not %d.\n", sizeof(DRIX_REGISTER)));
			status = STATUS_UNSUCCESSFUL;
			goto out;
		}

		if (NTOHL(RegMsg.Header.Signature) != DRIX_SIGNATURE) {
			KDPrintM(DBG_LURN_INFO, ("DRIX signature mismatch\n"));
			status = STATUS_UNSUCCESSFUL;
			goto out;
		}
		
		if (RegMsg.Header.Command != DRIX_CMD_REGISTER) {
			KDPrintM(DBG_LURN_INFO, ("Inappropriate command %x sent.\n", RegMsg.Header.Command));
			status = STATUS_UNSUCCESSFUL;
			goto out;
		}

		if (RegMsg.Header.ReplyFlag) {
			KDPrintM(DBG_LURN_INFO, ("Reply flag should be cleared\n"));
			status = STATUS_UNSUCCESSFUL;
			goto out;
		}
		if (NTOHS(RegMsg.Header.Length) !=  sizeof(DRIX_REGISTER)) {
			KDPrintM(DBG_LURN_INFO, ("Invalid packet length %d\n", NTOHS(RegMsg.Header.Length)));
			status = STATUS_UNSUCCESSFUL;
			goto out;
		}

		ACQUIRE_SPIN_LOCK(&g_DraidGlobals->ArbiterListSpinlock, &oldIrql);
		MatchFound = FALSE;
		for (listEntry = g_DraidGlobals->ArbiterList.Flink;
			listEntry != &g_DraidGlobals->ArbiterList;
			listEntry = listEntry->Flink) 
		{
			Arbiter = CONTAINING_RECORD (listEntry, DRAID_ARBITER_INFO, AllArbiterList);
			if (RtlCompareMemory(&Arbiter->Rmd.RaidSetId, &RegMsg.RaidSetId, sizeof(GUID)) == sizeof(GUID) &&
				RtlCompareMemory(&Arbiter->Rmd.ConfigSetId, &RegMsg.ConfigSetId, sizeof(GUID)) == sizeof(GUID)
			) {
				if (Arbiter->Status != DRAID_ARBITER_STATUS_TERMINATING) {
					MatchFound = TRUE;
				} else {
					KDPrintM(DBG_LURN_INFO, ("Arbiter is terminating. Reject reception\n"));	
					MatchFound = FALSE;
				}
				break;
			}
		}
		RELEASE_SPIN_LOCK(&g_DraidGlobals->ArbiterListSpinlock, oldIrql);

		if (MatchFound) {
			ResultCode = DRIX_RESULT_SUCCESS;
		} else {
			ResultCode = DRIX_RESULT_RAID_SET_NOT_FOUND;
		}
//reply:
		//
		// Send reply
		//
		Reply.Signature = 	NTOHL(DRIX_SIGNATURE);
		Reply.Command = DRIX_CMD_REGISTER;
		Reply.Length = NTOHS((UINT16)sizeof(DRIX_HEADER));
		Reply.ReplyFlag = 1;
		Reply.Sequence = RegMsg.Header.Sequence;
		Reply.Result = ResultCode;

		Timeout.QuadPart =  HZ * 5;

		KDPrintM(DBG_LURN_INFO, ("DRAID Sending registration reply(result=%x) to remote client\n", ResultCode));
		status = LpxTdiSend(
					Connection->ConnectionFileObject, (PUCHAR)&Reply, sizeof(DRIX_HEADER), 
					0, &Timeout,	NULL, &result	);
		KDPrintM(DBG_LURN_INFO, ("LpxTdiSend status=%x, result=%x.\n", status, result));
		if (status !=STATUS_SUCCESS) {
			Disconnect = TRUE;
			goto out;
		}
		if (MatchFound) {
			status = DraidArbiterAcceptClient(Arbiter, RegMsg.ConnType, Connection);
			if (status == STATUS_SUCCESS) {
				Disconnect = FALSE;
			} else {
				KDPrintM(DBG_LURN_INFO, ("Failed to accept client %x.\n", status));
			}
		}
	} else if (status == STATUS_TIMEOUT) {
		KDPrintM(DBG_LURN_INFO, ("Timeout before registration.\n"));
	}
	
out:
	if (Disconnect) {
		KDPrintM(DBG_LURN_INFO, ("Closing connection to client.\n"));			
		// Close connection.
		LpxTdiDisassociateAddress(Connection->ConnectionFileObject);
		LpxTdiCloseConnection(
					Connection->ConnectionFileHandle, 
					Connection->ConnectionFileObject
					);
		Connection->ConnectionFileHandle = NULL;
		Connection->ConnectionFileObject = NULL;

		ExFreePoolWithTag(Connection, DRAID_REMOTE_CLIENT_CHANNEL_POOL_TAG);
	} else {
		// Arbiter thread will close connection and free channel
	}
	
	KDPrintM(DBG_LURN_INFO, ("Exiting reception thread.\n"));
	// Decrease counter
	InterlockedDecrement(&g_DraidGlobals->ReceptionThreadCount);
}