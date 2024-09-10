BOOLEAN
SqlBeginTransaction(
	__in PSQL_DATABASE Database
	)
{
	ULONG Status;

	Status = SqlExecute(Database, "BEGIN TRANSACTION");
	return (Status == SQLITE_OK) ? TRUE : FALSE;
}