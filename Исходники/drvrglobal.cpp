extern "C" void ODBC_SIGTERM_handler(int signal)
{
	struct sigaction newActionHandler;

	CStmt *pStmt;
	std::list<CHandlePtr>::iterator i;
	CHandlePtr		pHandle;
	CHANDLECOLLECT handleCollection = 	gDrvrGlobal.gHandle.getHandles();

	for(i = handleCollection.begin(); i !=  handleCollection.end() ; ++i)
	{
		if ((pHandle = (CHandlePtr)(*i)) != NULL)		
		{
			if (pHandle->getHandleType() == SQL_HANDLE_STMT)
				SQLCancel((SQLHSTMT)pHandle);
		}

	} // for all handles

   sigaction(SIGTERM,&gOldSigTermActionHandler,NULL);
   raise(SIGTERM);
} // ODBC_SIGTERM_handler()