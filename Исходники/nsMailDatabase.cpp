nsresult nsMsgOfflineOpEnumerator::PrefetchNext()
{
  nsresult rv = NS_OK;
  nsIMdbRow* offlineOpRow;
  mdb_pos rowPos;

  if (!mRowCursor)
  {
    rv = GetRowCursor();
    if (NS_FAILED(rv))
      return rv;
  }

  rv = mRowCursor->NextRow(mDB->GetEnv(), &offlineOpRow, &rowPos);
  if (!offlineOpRow) 
  {
    mDone = true;
    return NS_ERROR_FAILURE;
  }
  if (NS_FAILED(rv)) 
  {
    mDone = true;
    return rv;
  }
  // Get key from row.
  mdbOid outOid;
  nsMsgKey key = 0;
  // TODO: Is the key variable unused?
  if (NS_SUCCEEDED(offlineOpRow->GetOid(mDB->GetEnv(), &outOid)))
    key = outOid.mOid_Id;

  nsIMsgOfflineImapOperation *op = new nsMsgOfflineImapOperation(mDB, offlineOpRow);
  mResultOp = op;
  if (!op)
    return NS_ERROR_OUT_OF_MEMORY;

  if (mResultOp) 
  {
    mNextPrefetched = true;
    return NS_OK;
  }
  return NS_ERROR_FAILURE;
}