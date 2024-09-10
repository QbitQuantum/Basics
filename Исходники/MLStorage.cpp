CONDITION
MLStorage::handleCStoreCommand(DUL_PRESENTATIONCONTEXT* ctx,
			       MSG_C_STORE_REQ** message,
			       MSG_C_STORE_RESP* response,
			       DUL_ASSOCIATESERVICEPARAMETERS* params,
			       MString& fileName)
{
  fileName = mLogDir + "/" + (*message)->instanceUID;

  MLogClient logClient;
  logClient.log(MLogClient::MLOG_VERBOSE,
		params->callingAPTitle,
		"MLStorage::handleCStoreCommand",
		__LINE__,
		"C-Store command; file stored in " + fileName);
}