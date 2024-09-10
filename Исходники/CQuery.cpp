// 연결 핸들을 할당하고 연결한 후 명령핸들까지 같이 할당한다.
// Type=1:ConStr은 MDB 파일의 경로를 가진다. 경로 생략시 현재 디렉토리에서 MDB를 찾는다.
// Type=2:ConStr은 SQL 서버의 연결 정보를 가지는 DSN 파일의 경로를 가진다. 
//        경로는 반드시 완전 경로로 지정해야 한다.
// Type=3:SQLConnect 함수로 DSN에 직접 연결한다.
// 연결 또는 명령 핸들 할당에 실패하면 FALSE를 리턴한다.
BOOL CQuery::Connect(int Type, char *ConStr, char *UID, char *PWD)
{
	SQLCHAR InCon[255];
	SQLCHAR OutCon[255];
    SQLSMALLINT cbOutCon;

	int ii=1;
	SQLRETURN Ret;
	SQLINTEGER NativeError;
	SQLCHAR SqlState[6], Msg[255];
	SQLSMALLINT MsgLen;
	char str[256];

	m_Type = Type;
	strcpy(m_szConnect, ConStr);
	strcpy(m_Id, UID);
	strcpy(m_Pass, PWD);

	// 연결 타입에 따라 MDB 또는 SQL 서버, 또는 DSN에 연결한다.
	SQLAllocHandle(SQL_HANDLE_DBC,hEnv,&hDbc);
	switch (Type) {
	case 1:
		wsprintf((char *)InCon,"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=%s;",ConStr);
		ret=SQLDriverConnect(hDbc,NULL,(SQLCHAR *)InCon,sizeof(InCon),OutCon,
			sizeof(OutCon),&cbOutCon, SQL_DRIVER_NOPROMPT);
		break;
	case 2:
		wsprintf((char *)InCon, "FileDsn=%s",ConStr);
		ret=SQLDriverConnect(hDbc,NULL,(SQLCHAR *)InCon,sizeof(InCon),OutCon,
			sizeof(OutCon),&cbOutCon, SQL_DRIVER_NOPROMPT);
		break;
	case 3:
		ret=SQLConnect(hDbc,(SQLCHAR *)ConStr,SQL_NTS,(SQLCHAR *)UID,SQL_NTS,
			(SQLCHAR *)PWD,SQL_NTS);
		break;
	}

	// 접속 에러시 진단 정보를 보여준다.
	if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO)) {
		while (Ret=SQLGetDiagRec(SQL_HANDLE_DBC, hDbc, ii, SqlState, &NativeError, 
			Msg, sizeof(Msg), &MsgLen)!=SQL_NO_DATA) {
			wsprintf(str, "(1) SQLSTATE:%s, Diagnosis:%s",(LPCTSTR)SqlState,(LPCTSTR)Msg);
			//::MessageBox(NULL,str,"진단 정보",0);
			gWindow.PrintLog(str);
			ii++;
		}
		return FALSE;
	}

	// 명령 핸들을 할당한다.
	ret=SQLAllocHandle(SQL_HANDLE_STMT,hDbc,&hStmt);
	if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO)) {
		hStmt=0;
		return FALSE;
	}
	return TRUE;
}