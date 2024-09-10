DWORD AuditUserW( LPWSTR lpUser, LPWSTR lpPasswd )
{
	DWORD dwRetCode;
	WCHAR szwComputer[CNLEN+1];
	WCHAR szwComputerName[CNLEN+3];
	DWORD cbComputer;

	if( lpUser == NULL || lpPasswd == NULL )
		return ERROR_INVALID_PARAMETER;

	cbComputer = CNLEN+1;
	GetComputerNameW( szwComputer, &cbComputer );

	cbComputer = CNLEN+3;
	MakeComputerNameW( szwComputer, szwComputerName, &cbComputer );

	dwRetCode = NetUserChangePassword(
		szwComputerName,
        lpUser,
		lpPasswd,
        lpPasswd );

	return dwRetCode;
}