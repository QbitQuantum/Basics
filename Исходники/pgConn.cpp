bool pgConn::EndPutCopy(const wxString errormsg)
{
	int result;

	// Execute the query and get the status
	if (errormsg.Length() == 0)
		result = PQputCopyEnd(conn, NULL);
	else
		result = PQputCopyEnd(conn, errormsg.mb_str(*conv));

	return result == 1;
}