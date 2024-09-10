static int	get_result_columns(ZBX_ODBC_DBH *dbh, char **buffer)
{
	int		ret = SUCCEED, i, j;
	char		str[MAX_STRING_LEN];
	SQLRETURN	rc;
	SQLSMALLINT	len;

	for (i = 0; i < dbh->col_num; i++)
	{
		rc = SQLColAttribute(dbh->hstmt, i + 1, SQL_DESC_LABEL, str, sizeof(str), &len, NULL);

		if (SQL_SUCCESS != rc || sizeof(str) <= len || '\0' == *str)
		{
			for (j = 0; j < i; j++)
				zbx_free(buffer[j]);

			ret = FAIL;
			break;
		}

		buffer[i] = zbx_strdup(NULL, str);
	}

	return ret;
}