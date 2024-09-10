/*
 * Release a result set from memory
 */
int db_unixodbc_free_result(db_con_t* _h, db_res_t* _r)
{
	if ((!_h) || (!_r))
	{
		LM_ERR("invalid parameter value\n");
		return -1;
	}

	if (db_free_result(_r) < 0)
	{
		LM_ERR("failed to free result structure\n");
		return -1;
	}

	SQLFreeHandle(SQL_HANDLE_STMT, CON_RESULT(_h));
	CON_RESULT(_h) = NULL;

	return 0;
}