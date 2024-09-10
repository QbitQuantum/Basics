CONDITION
MLStorageCommitment::handleNActionCommand(DUL_PRESENTATIONCONTEXT* ctx,
					  MSG_N_ACTION_REQ** message,
					  MSG_N_ACTION_RESP* response,
					  DUL_ASSOCIATESERVICEPARAMETERS* params,
					  MString& directoryName)
{
  MLogClient logClient;
  logClient.log(MLogClient::MLOG_VERBOSE,
		params->callingAPTitle,
		"MLStorageCommitment::handleNActionCommand",
		__LINE__,
		"Storage Commit N-Action command received");


  directoryName = ".";
}