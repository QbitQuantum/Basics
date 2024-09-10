	void BaseDatabaseUnitImpl::runTransaction(std::vector<CppSQLite3Statement> & statements)
	{
		if (beginTransaction())
		{
			try
			{
				for (auto it = statements.begin(); it != statements.end(); ++it)
				{
					it->execDML();
				}
				commitTransaction();
			}
			catch (CppSQLite3Exception e)
			{
				LOG_ERR_R(DATABASE_MANAGER_LOG_TAG, _T("Failed to run transaction, error: %u"), e.errorCode());
				LOG_ERR_D_A(DATABASE_MANAGER_LOG_TAG_A, "Message: %s", e.errorMessage());

				rollbackTransaction();
			}
		}
	}