static cell_t SQL_Rewind(IPluginContext *pContext, const cell_t *params)
{
	IQuery *query;
	HandleError err;

	if ((err = ReadQueryHndl(params[1], pContext, &query)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid query Handle %x (error: %d)", params[1], err);
	}

	IResultSet *rs = query->GetResultSet();
	if (!rs)
	{
		return pContext->ThrowNativeError("No current result set");
	}

	return rs->Rewind() ? 1 : 0;
}