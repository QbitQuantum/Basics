/*
 * 1. get account details from accountservices or db?
 */
MojErr OnEnabledHandler::start(const MojObject& payload)
{

	IMServiceHandler::logMojObjectJsonString(_T("OnEnabledHandler payload: %s"), payload);

	MojString accountId;
	MojErr err = payload.getRequired(_T("accountId"), accountId);
	if (err != MojErrNone) {
		MojLogError(IMServiceApp::s_log, _T("OnEnabledHandler accountId missing so bailing. error %d"), err);
		return err;
	}

	err = payload.getRequired(_T("enabled"), m_enable);
	if (err != MojErrNone) {
		MojLogError(IMServiceApp::s_log, _T("OnEnabledHandler enabled missing, assuming 'false'"));
		m_enable = false;
	}
	
	err = payload.getRequired(_T("capabilityProviderId"), m_capabilityProviderId);
	if (err != MojErrNone) {
		MojLogError(IMServiceApp::s_log, _T("OnEnabledHandler capabilityProviderId missing so bailing. error %d"), err);
		return err;
	}

	MojRefCountedPtr<MojServiceRequest> req;
	err = m_service->createRequest(req);
	if (err != MojErrNone) {
		MojLogError(IMServiceApp::s_log, _T("OnEnabledHandler::start createRequest failed. error %d"), err);
	} else {
		MojObject params;
		params.put(_T("accountId"), accountId);
		err = req->send(m_getAccountInfoSlot, "com.palm.service.accounts", "getAccountInfo", params, 1);
		if (err) {
			MojLogError(IMServiceApp::s_log, _T("OnEnabledHandler::start: getAccountInfo id %s failed. error %d"), accountId.data(), err);
		}
	}

	return MojErrNone;
}