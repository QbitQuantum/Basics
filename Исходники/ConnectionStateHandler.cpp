MojErr ConnectionState::ConnectionChangedScheduler::scheduleActivity()
{
	MojLogInfo(IMServiceApp::s_log, _T("com.palm.activitymanager/create \"IMLibpurple Connect Changed\""));
	MojRefCountedPtr<MojServiceRequest> req;
	MojErr err = m_service->createRequest(req);
	if (err != MojErrNone)
	{
		MojLogError(IMServiceApp::s_log, _T("ConnectionChangedScheduler createRequest failed for connect debounce. error %d"), err);
	}
	else
	{
		// Schedule an activity to callback after a few seconds. The activity may already exist
		MojObject activity;
		const MojChar* activityJSON = _T("{\"name\":\"IMLibpurple Connect Changed\"," \
				"\"description\":\"Scheduled callback to check the current connection status\"," \
				"\"type\":{\"foreground\":true}}");
		activity.fromJson(activityJSON);
		// activity.schedule
		time_t targetDate;
		time(&targetDate);
		targetDate += 10; // 10 seconds in the future
		tm* ptm = gmtime(&targetDate);
		char scheduleTime[50];
		sprintf(scheduleTime, "%d-%02d-%02d %02d:%02d:%02dZ", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
		MojObject scheduleObj;
		scheduleObj.putString("start", scheduleTime);
		activity.put("schedule", scheduleObj);

		MojObject params;
		params.putBool("start", true);
		params.putBool("subscribe", true);
		params.put("activity", activity);
		err = req->send(m_scheduleActivitySlot, "com.palm.activitymanager", "create", params, MojServiceRequest::Unlimited);
	}
	return err;
}