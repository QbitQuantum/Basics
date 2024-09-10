void RecvCMD_SET_COMMANDER(t_packet *p, t_connection c[], int cn )	// 사령관의 데이터를 세트한다.
{
	NW_Character tempNWCharacter;
	DWORD		 tempDWORD;

	HSTMT	hStmt=NULL;
	RETCODE	ret;
	SWORD	nClos;
	char	query_stmt[80]={0,};
	SDWORD	cbValue;

	SQLAllocStmt(hDBC,&hStmt);

	wsprintf(query_stmt,"select fame_pk from chr_info where name='%s'",p->u.NationWar.SetCommander.CommanderName);

	ret = SQLExecDirect(hStmt,(UCHAR*)query_stmt,SQL_NTS);
	if (ret!=SQL_SUCCESS_WITH_INFO && ret !=SQL_SUCCESS)
	{
		MyLog(0,"Query Failure!! RecvCMD_SET_COMMANDER..");
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}

	SQLNumResultCols(hStmt,&nClos);

	ret=SQLFetch(hStmt);
	if (ret!=SQL_SUCCESS_WITH_INFO && ret !=SQL_SUCCESS)
	{
		//MyLog(0,"WarField Fetch Error!!");
		SQLFreeStmt(hStmt,SQL_DROP);
		return ;
	}

	ret=SQLGetData(hStmt,1,SQL_C_SLONG,&tempDWORD,sizeof(int),&cbValue);
	if (ret!=SQL_SUCCESS_WITH_INFO && ret!=SQL_SUCCESS)
	{
		MyLog(0,"SQL Return Error(%d)!!",ret);
		SQLFreeStmt(hStmt,SQL_DROP);
		return ;
	}   

    SQLFreeStmt(hStmt,SQL_DROP);

	memcpy(&tempNWCharacter,&tempDWORD,sizeof(DWORD));

	tempNWCharacter.isCommander=1;

	memcpy(&tempDWORD,&tempNWCharacter,sizeof(DWORD));

	memcpy(&tempNWCharacter,&tempDWORD,sizeof(DWORD));

	SQLAllocStmt(hDBC,&hStmt);

	wsprintf(query_stmt,"update chr_info set fame_pk=%d where name='%s'",tempDWORD,p->u.NationWar.SetCommander.CommanderName);
	ret=SQLExecDirect(hStmt,(UCHAR*)query_stmt,SQL_NTS);
	if (ret!=SQL_SUCCESS_WITH_INFO && ret!=SQL_SUCCESS)
	{
		MyLog(0,"Update Query Failure!! RecvCMD_SET_COMMANDER..");
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}
	
	SQLFreeStmt(hStmt,SQL_DROP);
}