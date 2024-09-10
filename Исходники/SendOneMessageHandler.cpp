/*
 * Result of query for buddy with given username and serviceName
 *
 * If the buddy is found, we can send no matter what. If buddy is not found, we need to check if this service allows sending IM messages
 * to non buddies (gtalk does not allow this, aol does)
 */
MojErr SendOneMessageHandler::findBuddyResult(MojObject& result, MojErr findErr)
{

	if (findErr) {

		MojString error;
		MojErrToString(findErr, error);
		MojLogError(IMServiceApp::s_log, _T("findBuddyResult: error %d - %s"), findErr, error.data());
		// not much we can do here...
		failMessage(ERROR_SEND_GENERIC_ERROR);

	} else {

		// log the results
		MojString mojStringJson;
		result.toJson(mojStringJson);
		MojLogDebug(IMServiceApp::s_log, _T("findBuddyResult result: %s"), mojStringJson.data());

		// "results" in result
		MojObject results;
		result.get(_T("results"), results);

		// check to see if array is empty - there should really always be 0 or 1 item here
		if (!results.empty()){

			// buddy is on the list - send to the transport
			MojLogInfo(IMServiceApp::s_log, _T("findBuddyResult - user is on buddy list. No need to check account template."));
			sendToTransport();
		}
		else {
			MojLogInfo(IMServiceApp::s_log, _T("findBuddyResult - no buddy found. Need to check account template if this is allowed"));

			// check palm://com.palm.service.accounts/listAccountTemplates {"capability":"MESSAGING"} to get a list of account templates that support messaging.
			// If the account template includes "chatWithNonBuddies":false, it should fail to send.
			MojLogInfo(IMServiceApp::s_log, "Issuing listAccountTemplates request to com.palm.service.accounts");

			// parameters: {“capability”:”MESSAGING”}
			MojObject params;
			params.putString("capability", "MESSAGING");

			// Get a request object from the service
			MojRefCountedPtr<MojServiceRequest> req;
			MojErr err = m_service->createRequest(req);

			if (!err) {
				err = req->send(m_listAccountSlot, "com.palm.service.accounts", "listAccountTemplates", params);
			}

			if (err) {
				MojString error;
				MojErrToString(err, error);
				MojLogError(IMServiceApp::s_log, _T("findBuddyResult failed to send request to accounts: error %d - %s"), err, error.data());
				// not much we can do here...don't leave message still pending
				failMessage(ERROR_SEND_GENERIC_ERROR);
			}
		}
	}

	return MojErrNone;
}