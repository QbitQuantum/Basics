void InitializeTrace()
{

	//Read Trace Flag and TraceDLL
	char	szTraceFlags[100];
	char	szTraceDll[_MAX_PATH+1];

	UWORD   wConfigMode;

	if (g_hTraceDLL != NULL && GetModuleHandle(TRACE_DLL_NAME) == g_hTraceDLL){
		if(fpTraceProcessEntry)
			pdwGlobalTraceVariable = fpTraceProcessEntry();
		return;
	}
	
	SQLGetConfigMode( &wConfigMode);
	SQLSetConfigMode( ODBC_USER_DSN);
	SQLGetPrivateProfileString(szODBC, 
								szTraceDllKey, 
								szDefaultTraceDll,
								szTraceDll, 
								sizeof(szTraceDll), 
								szODBCIni);
//
// ODBC DM 3.52 works only with HKEY_CURRENT_USER
//
/*
	if ((g_hTraceDLL = GetModuleHandle(szTraceDll)) == NULL)
	{
		SQLSetConfigMode( ODBC_SYSTEM_DSN);
		SQLGetPrivateProfileString(szODBC, 
									szTraceDllKey, 
									szDefaultTraceDll,
									szTraceDll, 
									sizeof(szTraceDll), 
									szODBCIni);
		if ((g_hTraceDLL = GetModuleHandle(szTraceDll)) == NULL)
		{
			SQLSetConfigMode( wConfigMode);
			return;
		}
	}
*/
	SQLGetPrivateProfileString(szODBC, 
								szTraceFlagsKey, 
								szDefaultTraceFlags,
								szTraceFlags, 
								sizeof(szTraceFlags), 
								szODBCIni);
		
	SQLSetConfigMode( wConfigMode);

	gTraceFlags = atol(szTraceFlags);

	if ((g_hTraceDLL = GetModuleHandle(TRACE_DLL_NAME)) != NULL)
	{
		fpTraceProcessEntry = (FPTraceProcessEntry) GetProcAddress(g_hTraceDLL, "TraceProcessEntry");
		fpTraceDebugOut = (FPTraceDebugOut) GetProcAddress(g_hTraceDLL, "TraceDebugOut");
		fpTracePrintMarker = (FPTracePrintMarker) GetProcAddress(g_hTraceDLL, "TracePrintMarker");
		fpTraceFirstEntry = (FPTraceFirstEntry) GetProcAddress(g_hTraceDLL, "TraceFirstEntry");
		fpTraceReturn = (FPTraceReturn) GetProcAddress(g_hTraceDLL, "TraceReturn");
		fpTraceSQLAllocHandle = (FPTraceSQLAllocHandle) GetProcAddress(g_hTraceDLL, "TraceSQLAllocHandle");
		fpTraceSQLBindCol = (FPTraceSQLBindCol) GetProcAddress(g_hTraceDLL, "TraceSQLBindCol");
		fpTraceSQLBindParameter = (FPTraceSQLBindParameter) GetProcAddress(g_hTraceDLL, "TraceSQLBindParameter");
		fpTraceSQLCancel = (FPTraceSQLCancel) GetProcAddress(g_hTraceDLL, "TraceSQLCancel");
		fpTraceSQLCloseCursor = (FPTraceSQLCloseCursor) GetProcAddress(g_hTraceDLL, "TraceSQLCloseCursor");
		fpTraceSQLCopyDesc = (FPTraceSQLCopyDesc) GetProcAddress(g_hTraceDLL, "TraceSQLCopyDesc");
		fpTraceSQLDescribeParam = (FPTraceSQLDescribeParam) GetProcAddress(g_hTraceDLL, "TraceSQLDescribeParam");
		fpTraceSQLDisconnect = (FPTraceSQLDisconnect) GetProcAddress(g_hTraceDLL, "TraceSQLDisconnect");
		fpTraceSQLEndTran = (FPTraceSQLEndTran) GetProcAddress(g_hTraceDLL, "TraceSQLEndTran");
		fpTraceSQLExecute = (FPTraceSQLExecute) GetProcAddress(g_hTraceDLL, "TraceSQLExecute");
		fpTraceSQLExtendedFetch = (FPTraceSQLExtendedFetch) GetProcAddress(g_hTraceDLL, "TraceSQLExtendedFetch");
		fpTraceSQLFetch = (FPTraceSQLFetch) GetProcAddress(g_hTraceDLL, "TraceSQLFetch");
		fpTraceSQLFetchScroll = (FPTraceSQLFetchScroll) GetProcAddress(g_hTraceDLL, "TraceSQLFetchScroll");
		fpTraceSQLFreeHandle = (FPTraceSQLFreeHandle) GetProcAddress(g_hTraceDLL, "TraceSQLFreeHandle");
		fpTraceSQLFreeStmt = (FPTraceSQLFreeStmt) GetProcAddress(g_hTraceDLL, "TraceSQLFreeStmt");
		fpTraceSQLGetData = (FPTraceSQLGetData) GetProcAddress(g_hTraceDLL, "TraceSQLGetData");
		fpTraceSQLGetEnvAttr = (FPTraceSQLGetEnvAttr) GetProcAddress(g_hTraceDLL, "TraceSQLGetEnvAttr");
		fpTraceSQLGetTypeInfo = (FPTraceSQLGetTypeInfo) GetProcAddress(g_hTraceDLL, "TraceSQLGetTypeInfo");
		fpTraceSQLMoreResults = (FPTraceSQLMoreResults) GetProcAddress(g_hTraceDLL, "TraceSQLMoreResults");
		fpTraceSQLNumParams = (FPTraceSQLNumParams) GetProcAddress(g_hTraceDLL, "TraceSQLNumParams");
		fpTraceSQLNumResultCols = (FPTraceSQLNumResultCols) GetProcAddress(g_hTraceDLL, "TraceSQLNumResultCols");
		fpTraceSQLParamData = (FPTraceSQLParamData) GetProcAddress(g_hTraceDLL, "TraceSQLParamData");
		fpTraceSQLPutData = (FPTraceSQLPutData) GetProcAddress(g_hTraceDLL, "TraceSQLPutData");
		fpTraceSQLRowCount = (FPTraceSQLRowCount) GetProcAddress(g_hTraceDLL, "TraceSQLRowCount");
		fpTraceSQLSetEnvAttr = (FPTraceSQLSetEnvAttr) GetProcAddress(g_hTraceDLL, "TraceSQLSetEnvAttr");
		fpTraceSQLSetPos = (FPTraceSQLSetPos) GetProcAddress(g_hTraceDLL, "TraceSQLSetPos");
		fpTraceASVersion = (VERSION_def**) GetProcAddress(g_hTraceDLL, "ASVersion");
		fpTraceSrvrVersion = (VERSION_def**) GetProcAddress(g_hTraceDLL, "SrvrVersion");
		fpTraceSqlVersion = (VERSION_def**) GetProcAddress(g_hTraceDLL, "SqlVersion");
		fpTraceTransportIn = (FPTraceTransportIn) GetProcAddress(g_hTraceDLL, "TraceTransportIn");
		fpTraceTransportOut = (FPTraceTransportOut) GetProcAddress(g_hTraceDLL, "TraceTransportOut");
		fpTraceSQLSetDescRec = (FPTraceSQLSetDescRec) GetProcAddress(g_hTraceDLL, "TraceSQLSetDescRec");
		//Unicode functions
		fpTraceSQLGetDiagRecW = (FPTraceSQLGetDiagRecW) GetProcAddress(g_hTraceDLL, "TraceSQLGetDiagRecW");
		fpTraceSQLGetDiagFieldW = (FPTraceSQLGetDiagFieldW) GetProcAddress(g_hTraceDLL, "TraceSQLGetDiagFieldW");
		fpTraceSQLConnectW = (FPTraceSQLConnectW) GetProcAddress(g_hTraceDLL, "TraceSQLConnectW");
		fpTraceSQLSetConnectAttrW = (FPTraceSQLSetConnectAttrW) GetProcAddress(g_hTraceDLL, "TraceSQLSetConnectAttrW");
		fpTraceSQLGetConnectAttrW = (FPTraceSQLGetConnectAttrW) GetProcAddress(g_hTraceDLL, "TraceSQLGetConnectAttrW");
		fpTraceSQLSetStmtAttrW = (FPTraceSQLSetStmtAttrW) GetProcAddress(g_hTraceDLL, "TraceSQLSetStmtAttrW");
		fpTraceSQLGetStmtAttrW = (FPTraceSQLGetStmtAttrW) GetProcAddress(g_hTraceDLL, "TraceSQLGetStmtAttrW");
		fpTraceSQLGetInfoW = (FPTraceSQLGetInfoW) GetProcAddress(g_hTraceDLL, "TraceSQLGetInfoW");
		fpTraceSQLSetDescFieldW = (FPTraceSQLSetDescFieldW) GetProcAddress(g_hTraceDLL, "TraceSQLSetDescFieldW");
		fpTraceSQLGetDescFieldW = (FPTraceSQLGetDescFieldW) GetProcAddress(g_hTraceDLL, "TraceSQLGetDescFieldW");
		fpTraceSQLGetDescRecW = (FPTraceSQLGetDescRecW) GetProcAddress(g_hTraceDLL, "TraceSQLGetDescRecW");
		fpTraceSQLBrowseConnectW = (FPTraceSQLBrowseConnectW) GetProcAddress(g_hTraceDLL, "TraceSQLBrowseConnectW");
		fpTraceSQLDriverConnectW = (FPTraceSQLDriverConnectW) GetProcAddress(g_hTraceDLL, "TraceSQLDriverConnectW");
		fpTraceSQLPrepareW = (FPTraceSQLPrepareW) GetProcAddress(g_hTraceDLL, "TraceSQLPrepareW");
		fpTraceSQLExecDirectW = (FPTraceSQLExecDirectW) GetProcAddress(g_hTraceDLL, "TraceSQLExecDirectW");
		fpTraceSQLDescribeColW = (FPTraceSQLDescribeColW) GetProcAddress(g_hTraceDLL, "TraceSQLDescribeColW");
		fpTraceSQLTablesW = (FPTraceSQLTablesW) GetProcAddress(g_hTraceDLL, "TraceSQLTablesW");
		fpTraceSQLColumnsW = (FPTraceSQLColumnsW) GetProcAddress(g_hTraceDLL, "TraceSQLColumnsW");
		fpTraceSQLSpecialColumnsW = (FPTraceSQLSpecialColumnsW) GetProcAddress(g_hTraceDLL, "TraceSQLSpecialColumnsW");
		fpTraceSQLPrimaryKeysW = (FPTraceSQLPrimaryKeysW) GetProcAddress(g_hTraceDLL, "TraceSQLPrimaryKeysW");
		fpTraceSQLStatisticsW = (FPTraceSQLStatisticsW) GetProcAddress(g_hTraceDLL, "TraceSQLStatisticsW");
		fpTraceSQLGetCursorNameW = (FPTraceSQLGetCursorNameW) GetProcAddress(g_hTraceDLL, "TraceSQLGetCursorNameW");
		fpTraceSQLSetCursorNameW = (FPTraceSQLSetCursorNameW) GetProcAddress(g_hTraceDLL, "TraceSQLSetCursorNameW");
		fpTraceSQLNativeSqlW = (FPTraceSQLNativeSqlW) GetProcAddress(g_hTraceDLL, "TraceSQLNativeSqlW");
		fpTraceSQLColAttributeW = (FPTraceSQLColAttributeW) GetProcAddress(g_hTraceDLL, "TraceSQLColAttributeW");
		fpTraceSQLProceduresW = (FPTraceSQLProceduresW) GetProcAddress(g_hTraceDLL, "TraceSQLProceduresW");
		fpTraceSQLProcedureColumnsW = (FPTraceSQLProcedureColumnsW) GetProcAddress(g_hTraceDLL, "TraceSQLProcedureColumnsW");
		fpTraceSQLColumnPrivilegesW = (FPTraceSQLColumnPrivilegesW) GetProcAddress(g_hTraceDLL, "TraceSQLColumnPrivilegesW");
		fpTraceSQLTablePrivilegesW = (FPTraceSQLTablePrivilegesW) GetProcAddress(g_hTraceDLL, "TraceSQLTablePrivilegesW");
		fpTraceSQLForeignKeysW = (FPTraceSQLForeignKeysW) GetProcAddress(g_hTraceDLL, "TraceSQLForeignKeysW");
		




	}
	if(fpTraceProcessEntry)
		pdwGlobalTraceVariable = fpTraceProcessEntry();
}