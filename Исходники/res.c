/*
 * Get and convert columns from a result
 */
int db_unixodbc_get_columns(const db1_con_t* _h, db1_res_t* _r)
{
	int col;
	SQLSMALLINT cols; /* because gcc don't like RES_COL_N */

	if ((!_h) || (!_r)) {
		LM_ERR("invalid parameter\n");
		return -1;
	}

	/* Save number of columns in the result structure */
	SQLNumResultCols(CON_RESULT(_h), &cols);
	RES_COL_N(_r) = cols;
	if (!RES_COL_N(_r)) {
		LM_ERR("no columns returned from the query\n");
		return -2;
	} else {
		LM_DBG("%d columns returned from the query\n", RES_COL_N(_r));
	}

	if (db_allocate_columns(_r, RES_COL_N(_r)) != 0) {
		LM_ERR("could not allocate columns\n");
		return -3;
	}

	for(col = 0; col < RES_COL_N(_r); col++)
	{
		RES_NAMES(_r)[col] = (str*)pkg_malloc(sizeof(str));
		if (! RES_NAMES(_r)[col]) {
			LM_ERR("no private memory left\n");
			db_free_columns(_r);
			return -4;
		}
		LM_DBG("allocate %lu bytes for RES_NAMES[%d] at %p\n",
			(unsigned long)sizeof(str),col,	RES_NAMES(_r)[col]);

		char columnname[80];
		SQLRETURN ret;
		SQLSMALLINT namelength, datatype, decimaldigits, nullable;
		SQLULEN columnsize;

		ret = SQLDescribeCol(CON_RESULT(_h), col + 1, (SQLCHAR *)columnname, 80,
			&namelength, &datatype, &columnsize, &decimaldigits, &nullable);
		if(!SQL_SUCCEEDED(ret)) {
			LM_ERR("SQLDescribeCol failed: %d\n", ret);
			db_unixodbc_extract_error("SQLExecDirect", CON_RESULT(_h), SQL_HANDLE_STMT,
				NULL);
			// FIXME should we fail here completly?
		}
		/* The pointer that is here returned is part of the result structure. */
		RES_NAMES(_r)[col]->s = columnname;
		RES_NAMES(_r)[col]->len = namelength;

		LM_DBG("RES_NAMES(%p)[%d]=[%.*s]\n", RES_NAMES(_r)[col], col,
				RES_NAMES(_r)[col]->len, RES_NAMES(_r)[col]->s);

		switch(datatype)
		{
			case SQL_SMALLINT:
			case SQL_INTEGER:
			case SQL_TINYINT:
			case SQL_DECIMAL:
			case SQL_NUMERIC:
				LM_DBG("use DB1_INT result type\n");
				RES_TYPES(_r)[col] = DB1_INT;
				break;

			case SQL_BIGINT:
				LM_DBG("use DB1_BIGINT result type\n");
				RES_TYPES(_r)[col] = DB1_BIGINT;
				break;

			case SQL_REAL:
			case SQL_FLOAT:
			case SQL_DOUBLE:
				LM_DBG("use DB1_DOUBLE result type\n");
				RES_TYPES(_r)[col] = DB1_DOUBLE;
				break;

			case SQL_TYPE_TIMESTAMP:
			case SQL_DATE:
			case SQL_TIME:
			case SQL_TIMESTAMP:
			case SQL_TYPE_DATE:
			case SQL_TYPE_TIME:
				LM_DBG("use DB1_DATETIME result type\n");
				RES_TYPES(_r)[col] = DB1_DATETIME;
				break;

			case SQL_CHAR:
			case SQL_VARCHAR:
			case SQL_WCHAR:
			case SQL_WVARCHAR:
				LM_DBG("use DB1_STRING result type\n");
				RES_TYPES(_r)[col] = DB1_STRING;
				break;

			case SQL_BINARY:
			case SQL_VARBINARY:
			case SQL_LONGVARBINARY:
			case SQL_BIT:
			case SQL_LONGVARCHAR:
			case SQL_WLONGVARCHAR:
				LM_DBG("use DB1_BLOB result type\n");
				RES_TYPES(_r)[col] = DB1_BLOB;
				break;

			default:
				LM_WARN("unhandled data type column (%.*s) type id (%d), "
						"use DB1_STRING as default\n", RES_NAMES(_r)[col]->len,
						RES_NAMES(_r)[col]->s, datatype);
				RES_TYPES(_r)[col] = DB1_STRING;
				break;
		}
	}
	return 0;
}