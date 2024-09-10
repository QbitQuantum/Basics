int poll_reader() {
    LLRP_tSMessage *pMessage = NULL;
    const LLRP_tSTypeDescriptor *pType;

    // wait a little bit for a message
    //
    // FIXME: it'd be nice if the LLRP library exposed a file descriptor so
    // we could roll it into select in our main loop
    pMessage = recvMessage(RECEIVE_TIMEOUT);
    if (pMessage == NULL) {
	// timeout
	return 1;
    }
    
    
    /*
     * What happens here depends on what kind of message was received.
     * Use the type label (pType) to discriminate message types.
     */
    pType = pMessage->elementHdr.pType;
    
    /*
     * If this is a tag report, then process it.
     */
    if (&LLRP_tdRO_ACCESS_REPORT == pType) {
	if (loss_timeout != UINT_MAX) { 
	    process_ro_access_report_with_loss_timeout((LLRP_tSRO_ACCESS_REPORT *)pMessage);
	} else {
	    process_ro_access_report((LLRP_tSRO_ACCESS_REPORT *)pMessage);
	}
	freeMessage(pMessage);
	
	scans_left_to_do --;
	if (scans_left_to_do > 0) startROSpec();
	return 1;
    }
    
    /*
     * If this is a reader event ...
     */
    else if (&LLRP_tdREADER_EVENT_NOTIFICATION == pType) {
	LLRP_tSREADER_EVENT_NOTIFICATION *pNtf;
	LLRP_tSReaderEventNotificationData *pNtfData;
	
	pNtf = (LLRP_tSREADER_EVENT_NOTIFICATION *) pMessage;
	
	pNtfData = LLRP_READER_EVENT_NOTIFICATION_getReaderEventNotificationData(pNtf);
	
	if (pNtfData != NULL) {
	    handleReaderEventNotification(pNtfData);
	} else {
	    // Should never happen.
	    g_warning("READER_EVENT_NOTIFICATION  without data");
	}
    } else {
	/*
	 * Something unexpected happened.
	 */
	g_warning("Ignoring unexpected message during monitor: %s", pType->pName);
    }
    
    freeMessage(pMessage);

    return 1;
}