bool 
CatalogBaseImpl::DriverConnect(const char* szConnStr, char* szConnStrOut, HWND hWnd, const int nDrvConn)
{
	SQLRETURN ret;
	SQLSMALLINT pcbConnStrOut;

	if(nDrvConn == SQL_DRIVER_PROMPT && hWnd == NULL)
		return FALSE;

	SQLSetConnectAttr(hDbc_, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)lLoginTimeout_, 0);
	SQLSetConnectAttr(hDbc_, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)lQueryTimeout_, 0);
	
	if(eAM_==READ_ONLY)
		SQLSetConnectAttr(hDbc_, SQL_ATTR_ACCESS_MODE, (SQLPOINTER)SQL_MODE_READ_ONLY, 0);
	else
		SQLSetConnectAttr(hDbc_, SQL_ATTR_ACCESS_MODE, (SQLPOINTER)SQL_MODE_READ_WRITE, 0);

	ret = SQLDriverConnect(hDbc_, 
							hWnd, 
							(SQLCHAR*)szConnStr, 
							SQL_NTS, 
							(SQLCHAR*)szConnStrOut,
							sizeof(szConnStrOut), 
							&pcbConnStrOut, 
							(SQLUSMALLINT)nDrvConn);

	bIsConnected_ = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	
	return bIsConnected_;
}