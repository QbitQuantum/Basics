static cell AMX_NATIVE_CALL SQL_Rewind(AMX *amx, cell *params)
{
	AmxQueryInfo *qInfo = (AmxQueryInfo *)GetHandle(params[1], Handle_Query);
	if (!qInfo)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Invalid query handle: %d", params[1]);
		return 0;
	}

	IResultSet *rs = qInfo->info.rs;

	if (!rs)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "No result set in this query!");
		return 0;
	}

	rs->Rewind();

	return 1;
}