///	free all memory allocations for database
///	\param	dbInfo - pointer to database information
void CDatabaseManager::ReleaseDatabase(DATABASEINFO *dbInfo)
{
	DATABASEDATA *data = dbInfo->m_DatabaseData;
	if (data != NULL)
	{
		for_each(data, data + dbInfo->m_nItems, mem_fun_ref(&DATABASEDATA::Release));
		GLOBALFREE(data);
	}
	// free up the alloc CHashString*
	delete dbInfo->m_SchemaName;
	delete dbInfo->m_FileName;
	// TODO: Check that name is owned by DATABASEINFO structure also
	//delete dbInfo->m_DatabaseName;
	//delete dbInfo->m_SchemaFile;
}