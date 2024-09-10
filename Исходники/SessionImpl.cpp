Poco::UInt32 SessionImpl::getDefaultTransactionIsolation()
{
	SQLUINTEGER isolation = 0;
	checkError(SQLGetInfo(_db, SQL_DEFAULT_TXN_ISOLATION,
		&isolation,
		0,
		0));

	return transactionIsolation(isolation);
}