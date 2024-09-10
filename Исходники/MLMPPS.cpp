CONDITION
MLMPPS::handleNCreateCommand(DUL_PRESENTATIONCONTEXT* ctx,
			       MSG_N_CREATE_REQ** message,
			       MSG_N_CREATE_RESP* response,
			       DUL_ASSOCIATESERVICEPARAMETERS* params,
			       MString& directoryName)
{
  directoryName = mStorageDir;

  MLogClient logClient;
  logClient.log(MLogClient::MLOG_VERBOSE,
		params->callingAPTitle,
		"MLMPPS::handleNCreateCommand",
		__LINE__,
		"MPPS N-Create command received");

  return 0;
}