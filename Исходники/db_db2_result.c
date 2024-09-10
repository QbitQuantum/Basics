long db2_bmd_db_result_get_row(void *hDB,void *hRes,long which_row,long max_columns,db_row_strings_t **rowstruct,
						   EnumDbFetchMode_t fetch_mode,long *successfully_fetched)
{
	long err = 0;
	SQLRETURN     rc;


		DB_bmd_db_conn_t *db_conn=NULL;
		//DB_bmd_db_result_t *db_res=NULL;
		//SQLUINTEGER   rowsFetchedNb		= 0;

		SQLSMALLINT   nResultCols=0;
		long colsprocess		= 0;
		long i				= 0;

		/******************************/
		/*	walidacja parametrow	*/
		/******************************/
		if(hDB==NULL)			{	BMD_FOK(BMD_DB_INVALID_CONNECTION_HANDLE);	}

		if(which_row < 0)				{	BMD_FOK(BMD_ERR_PARAM3);			}
		if(max_columns < 0)				{	BMD_FOK(BMD_ERR_PARAM4);			}
		if(rowstruct == NULL)				{       BMD_FOK(BMD_ERR_PARAM5);       			}
		if(*rowstruct != NULL)				{       BMD_FOK(BMD_ERR_PARAM5);                        }
		if( (*((long *)(hDB)) != BMD_DBCONN_MAGIC ) )
			return BMD_ERR_INVALID_PTR;

		db_conn=(DB_bmd_db_conn_t *)hDB;

		if( fetch_mode == FETCH_ABSOLUTE )
			return BMD_ERR_FORMAT;
		else
			if( fetch_mode == FETCH_NEXT )
				;
			else
			{
				return BMD_ERR_FORMAT;
			}


		*rowstruct = (db_row_strings_t *) malloc ( sizeof(db_row_strings_t) );
		if(*rowstruct == NULL)
		{
			PRINT_ERROR("LIBBMDPGERR Memory error. Error=%i\n",NO_MEMORY);
			return NO_MEMORY;
		}
		memset(*rowstruct, 0, sizeof(db_row_strings_t));



		/* identify the output columns */
		rc = SQLNumResultCols( *(db_conn->hstmt), &nResultCols);
		if(rc != SQL_SUCCESS)
		{
			extract_error("SQLNumResultCols", *(db_conn->hstmt), SQL_HANDLE_STMT);
			return BMD_DB_EXECUTION_ERROR;

		}

		if(max_columns <= 0)
		{
			colsprocess = nResultCols;
		}
		else
		{
			colsprocess = (nResultCols < max_columns)? nResultCols:max_columns;
		}

		/* przetwarzam mniejsza wartosc z colsreturned i max_columns */
		(*rowstruct)->size = colsprocess;

		(*rowstruct)->colvals = (char **) malloc (sizeof(char *) * colsprocess);
		if((*rowstruct)->colvals == NULL)
		{
			PRINT_ERROR("LIBBMDPGERR Memory error. Error=%i\n",NO_MEMORY);
			return NO_MEMORY;
		}
		memset((*rowstruct)->colvals, 0, sizeof(char *) * colsprocess);



		/*
		 * set up the values to return fetch information into
		 */

		rc = SQLFetch(*(db_conn->hstmt));
			long ret = print_error(rc, "SQLFetch");
		    if(ret!=BMD_OK)
		    {
			    if(ret == 5)
				{
					PRINT_INFO("No Data Found\n");
			   		return BMD_ERR_NODATA;
				}
			   	else{
			   		extract_error("SQLAllocHandle", *(db_conn->hstmt), SQL_HANDLE_STMT);
			   		return BMD_DB_EXECUTION_ERROR;
			   	}
		    }

		int colNum = 0;
		SQLINTEGER sql_ub;
		rc = SQLGetStmtAttr( *(db_conn->hstmt), SQL_ATTR_USE_BOOKMARKS, &sql_ub, 0, NULL ) ;

		if(print_error(rc, "SQLGetStmtAttr") != BMD_OK)
		{
			extract_error("SQLGetStmtAttr,SQL_ATTR_USE_BOOKMARKS ", *(db_conn->hstmt), SQL_HANDLE_STMT);
			return BMD_DB_EXECUTION_ERROR;
		}

		if ( sql_ub == SQL_UB_OFF )
		  	colNum = 1;
		else
		  	colNum = 0;



		/* Wypelnij wszystkie stringi z wiersza */
		for(i=0; i<colsprocess; i++)
		{
			/* retrieve column data as a string */
			SQLINTEGER indicator;
			//TODO - koniecznie zrobiæ bufor dynamiczny!!!
			SQLCHAR buf[32000];
			rc = SQLGetData(*(db_conn->hstmt), i+colNum, SQL_C_CHAR, buf, sizeof(buf), &indicator);
			if (print_error(rc, "SQLGetData") != BMD_OK)
			{
				extract_error("SQLGetData", *(db_conn->hstmt), SQL_HANDLE_STMT);
				return BMD_DB_EXECUTION_ERROR;
			}
			if(indicator > 0)
				asprintf(&((*rowstruct)->colvals[i]),"%s",buf);
			else
				asprintf(&((*rowstruct)->colvals[i]),"%s","");
		}

		return err;
}