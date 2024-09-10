DBSTATUS CSRViewColumnUsage::GetDBStatus(CSimpleRow *pRow, ATLCOLUMNINFO *pInfo)
{
	ATLTRACE2(atlTraceDBProvider, 3, "CSRViewColumnUsage::GetDBStatus\n");
	switch(pInfo->iOrdinal)
	{
	case 3: // VIEW_NAME
	case 6: // TABLE_NAME
	case 7: // COLUMN_NAME 
		return DBSTATUS_S_OK;
	default:
		return DBSTATUS_S_ISNULL;
	}
}