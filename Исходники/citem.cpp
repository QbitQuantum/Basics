int LoadChangeItem()//010708 lsw
{
	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;

	SQLAllocStmt(hDBC, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)"Select * from item_change order by original", SQL_NTS);
	if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
	{		
		int i = 0;
		retCode = SQLFetch(hStmt);
		while( retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		{
			if(i >= MAX_CHANGE_ITEM_COUNT)//020730 lsw
			{
				SQLFreeStmt(hStmt, SQL_DROP);
				return 0;
			}

			retCode = SQLGetData(hStmt, 1, SQL_C_LONG,	&itemchange[i].origin_item_no		, 0, &cbValue);
			retCode = SQLGetData(hStmt, 2, SQL_C_LONG,	&itemchange[i].will_change_item_no	, 0, &cbValue);
			retCode = SQLGetData(hStmt, 3, SQL_C_LONG,	&itemchange[i].add_soksung			, 0, &cbValue);
			retCode = SQLGetData(hStmt, 4, SQL_C_LONG,	&itemchange[i].add_grade			, 0, &cbValue);
			
			ichangeItemCount=i;			
			i++;

			retCode = SQLFetch(hStmt);
			if(retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
			{
			}
			else if( retCode == SQL_NO_DATA ) 
			{
				break;
			}
			else
			{
				SQLFreeStmt(hStmt, SQL_DROP);
				return 0;
			}
		}	
	}		


	SQLFreeStmt(hStmt, SQL_DROP);		// 0308 YGI
	return(1);
}