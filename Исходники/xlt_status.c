static int get_error_from_diag_rec(
		odbcdr_context_def *context, 
		SQLSMALLINT handle_type, 
		SQLHANDLE handle)
{
	int		rdbi_status = RDBI_SUCCESS;
	int		crit_err_found = FALSE;
	RETCODE	rec_retcode = SQL_SUCCESS;
	RETCODE	field_retcode = SQL_SUCCESS;
	SQLWCHAR	szSqlState[ODBCDR_MAX_BUFF_SIZE];
	SQLWCHAR 	szErrorMsg[ODBCDR_MAX_BUFF_SIZE];
	SDWORD		pfNativeError = 0L;
	SWORD	 	pcbErrorMsg = 0;
	SQLSMALLINT cRecNmbr = 1;
	SDWORD  	SS_Severity = 0;
	SQLINTEGER	Rownumber = 0;
	SQLINTEGER  Colnumber = 0;
    szSqlState[0] = L'\0';
    szErrorMsg[0] = L'\0';

	/*
	** Loop through the diagnostic records until there are no records
	** left or a critical error is found.
	** For now, we will only deal with the first critical error, and
	** ignore the rest.
	*/
	while ((rec_retcode != SQL_NO_DATA_FOUND) && !crit_err_found) {
		rec_retcode = (context->odbcdr_UseUnicode) ? 
            SQLGetDiagRecW(handle_type, handle,
					cRecNmbr, szSqlState, &pfNativeError,
                    szErrorMsg, ODBCDR_MAX_BUFF_SIZE, &pcbErrorMsg) : 
            SQLGetDiagRec(handle_type, handle,
					cRecNmbr, (SQLCHAR*)szSqlState, &pfNativeError,
					(SQLCHAR*)szErrorMsg, ODBCDR_MAX_BUFF_SIZE, &pcbErrorMsg);
 
		if (rec_retcode != SQL_NO_DATA_FOUND) {
			field_retcode = (context->odbcdr_UseUnicode) ? 
                SQLGetDiagFieldW( handle_type, handle, cRecNmbr,
					SQL_DIAG_ROW_NUMBER, &Rownumber,
					SQL_IS_INTEGER, NULL) :
                SQLGetDiagField( handle_type, handle, cRecNmbr,
					SQL_DIAG_ROW_NUMBER, &Rownumber,
					SQL_IS_INTEGER, NULL);

			if (Rownumber != SQL_NO_ROW_NUMBER  && Rownumber != SQL_ROW_NUMBER_UNKNOWN)	{
				field_retcode = (context->odbcdr_UseUnicode) ? 
                    SQLGetDiagFieldW( handle_type, handle, cRecNmbr,
						SQL_DIAG_COLUMN_NUMBER , &Colnumber,
						SQL_IS_INTEGER, NULL) : 
                    SQLGetDiagField( handle_type, handle, cRecNmbr,
						SQL_DIAG_COLUMN_NUMBER , &Colnumber,
						SQL_IS_INTEGER, NULL);
			}
#ifdef _WIN32
			field_retcode = (context->odbcdr_UseUnicode) ? 
                SQLGetDiagFieldW( handle_type, handle, cRecNmbr,
					SQL_DIAG_SS_SEVERITY, &SS_Severity,
                    SQL_IS_INTEGER, NULL):
                SQLGetDiagField(handle_type, handle, cRecNmbr,
					SQL_DIAG_SS_SEVERITY, &SS_Severity,
					SQL_IS_INTEGER,NULL);
#endif

			switch( pfNativeError ) {
				case 208 :
					rdbi_status = RDBI_NO_SUCH_TABLE;
					crit_err_found = TRUE;
					break;
				case 916 :
					rdbi_status = RDBI_NOT_VALID_USER_IN_DATABASE;
					crit_err_found = TRUE;
					break;
				case 1555 :
					rdbi_status = RDBI_RESOURCE_BUSY;
					crit_err_found = TRUE;
					break;
				case 18456 :
					rdbi_status = RDBI_INVLD_USER_PSWD;
					crit_err_found = TRUE;
					break;
                case 913: 
                    // "Could not find database ID 52. Database may not be activated yet or may be in transition."
                    // Severity 16. This is rather a bug related to updating views.
                    rdbi_status = RDBI_GENERIC_ERROR;
                    break;
                case 2601:
				case 2627:
                    // Duplicate index found.
                    rdbi_status = RDBI_DUPLICATE_INDEX;
					crit_err_found = TRUE;
                    break;
				case 2714:
					// There is already an object named '%.*ls' in the database.
					rdbi_status = RDBI_OBJECT_EXISTS;
					crit_err_found = TRUE;
                    break;
				case 3701:
					// No such object
					rdbi_status = RDBI_NO_SUCH_TABLE;
					crit_err_found = TRUE;
					break;
                case 229:
                    // insufficient privileges
                    rdbi_status = RDBI_INSUFFICIENT_PRIVS;
                    crit_err_found = TRUE;
                    break;
				default :
					// If we did not identify any specific errors in the 
					// diagnostic record, use the severity level to 
					// determine if a error occurred
                    // *** DS doesn't agree.
					//if (SS_Severity > 10) {
						rdbi_status = RDBI_GENERIC_ERROR;
						crit_err_found = TRUE;
					//} else {
					//	rdbi_status = RDBI_SUCCESS;
					//}
			} //switch
			cRecNmbr++; //Increment to next diagnostic record.
		} //if plm_retcode

	} // End while.

    if (context->odbcdr_UseUnicode)
	    save_err_msgW( context, handle_type, handle, 1); // 1 = assuming a connection has already been made
    else
        save_err_msg( context, handle_type, handle, 1); // 1 = assuming a connection has already been made

	return rdbi_status;
}