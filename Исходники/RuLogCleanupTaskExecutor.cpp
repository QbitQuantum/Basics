//--------------------------------------------------------------------------//
//	CRULogCleanupTaskExecutor::decideOnDeleteMethod()
//
// A heuristic decision on which delete method to use.
// First we use this formula to get the average number of rows er partition:
//        rowCount * SF
//       ---------------
//           P * 100
// Where: rowCount is the number of rows in the IUD log (as an upper bound to 
//                 the number of rows to be deleted).
//        SF       is the safety factor from the defaults table (default is 50%).
//        P        is the number of partitions.
//
// If the number of rows per partition is smaller than the lock escalation 
// limit, we use a simple delete statement.
// Otherwise we use delete with multi commit, unless it is disabled by a CQD.
//--------------------------------------------------------------------------//
CRULogCleanupTaskExecutor::SQL_STATEMENT CRULogCleanupTaskExecutor::decideOnDeleteMethod()
{
  SQL_STATEMENT deleteMethod;

  BeginTransaction();

  CDSString safetyFactorName("MV_LOG_CLEANUP_SAFETY_FACTOR");
  TInt32 safetyFactor = 0;
  CRUCache::FetchSingleDefault( safetyFactorName, safetyFactor);

  CDSString useMultiCommitName("MV_LOG_CLEANUP_USE_MULTI_COMMIT");
  TInt32 useMultiCommit = 1;
  CRUCache::FetchSingleDefault( useMultiCommitName, useMultiCommit);

  if (safetyFactor <= 100)
  {
    // When the safty factor is set to 100 or less, lock escalation is not an issue,
    // so we can use simple delete no matter how many rows are to be deleted.
    deleteMethod = CLEAN_IUD_BASIC;

#ifdef _DEBUG
	// LCOV_EXCL_START :dpb
    CDSString msg("Safety factor set to 100 or less - using simple delete.");
    CRUGlobals::GetInstance()->
		LogDebugMessage(CRUGlobals::DUMP_COMPILED_DYNAMIC_SQL, "", msg, FALSE);
	// LCOV_EXCL_STOP
#endif
  }
  else
  {
    Int64 rowCount = getRowCount();
    TInt64 rowsPerPartition = rowCount * safetyFactor / (noOfPartitions_ * 100);

    if (rowsPerPartition < CRULogCleanupSQLComposer::MAX_ROW_TO_DELETE_IN_SINGLE_TXN)
      deleteMethod = CLEAN_IUD_BASIC;
    else if (useMultiCommit == 1)
      deleteMethod = CLEAN_IUD_MCOMMIT;
    else
      deleteMethod = CLEAN_IUD_FIRSTN;

#ifdef _DEBUG
    CDSString msg;
    char buff[200];
    sprintf(buff, "IUD log has " PF64 " rows, and %d partitions. Safety factor is %d. Using ", 
            rowCount, noOfPartitions_, safetyFactor);
    msg = buff; 

    switch(deleteMethod)
    {
      case CLEAN_IUD_BASIC:
        msg += "simple delete.\n";
        break;
      case CLEAN_IUD_FIRSTN:
        msg += "delete First N.\n";
        break;
      case CLEAN_IUD_MCOMMIT:
        msg += "delete with Multi Commit.\n";
        break;
    }
    CRUGlobals::GetInstance()->
		LogDebugMessage(CRUGlobals::DUMP_COMPILED_DYNAMIC_SQL, "", msg, FALSE);
#endif
  }

  CommitTransaction();

  return deleteMethod;
}