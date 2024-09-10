CheckEvents::check_event_result_t
CheckEvents::CheckAllJobs(MyString &errorMsg)
{
	check_event_result_t	result = EVENT_OKAY;
	errorMsg = "";

	const int	MAX_MSG_LEN = 1024;
	bool		msgFull = false; // message length has hit max

	CondorID	id;
	JobInfo *info = NULL;
	jobHash.startIterations();
	while ( jobHash.iterate(id, info) != 0 ) {

			// Put a limit on the maximum message length so we don't
			// have a chance of ending up with a ridiculously large
			// MyString...
		if ( !msgFull && (errorMsg.Length() > MAX_MSG_LEN) ) {
			errorMsg += " ...";
			msgFull = true;
		}

		MyString	idStr("BAD EVENT: job ");
		idStr.formatstr_cat("(%d.%d.%d)", id._cluster, id._proc, id._subproc);

		MyString	tmpMsg;
		CheckJobFinal(idStr, id, info, tmpMsg, result);
		if ( tmpMsg != "" && !msgFull ) {
			if ( errorMsg != "" ) errorMsg += "; ";
			errorMsg += tmpMsg;
		}
	}

	return result;
}