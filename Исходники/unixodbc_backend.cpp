SQLRETURN unixodbc_backend::do_more_results(SQLHSTMT statement_handle) const
{
	return SQLMoreResults(statement_handle);
}