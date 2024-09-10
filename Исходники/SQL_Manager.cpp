void SQLClass::Init()
{

	bool bResult = false;
	char SQLConnect[]="..\\OptionsData\\Options.ini";

	if( GetPrivateProfileIntA("SQL", "SQLVersion", 2000, SQLConnect) == 2000 ) {
		strcpy_s(m_SqlConn.sDriver, "{SQL Server}");
	} 
	else {
		strcpy_s(m_SqlConn.sDriver, "{SQL Native Client}");
	}
	

	GetPrivateProfileStringA("SQL", "Host",	"",m_SqlConn.sServer,	sizeof(m_SqlConn.sServer),	SQLConnect);
	GetPrivateProfileStringA("SQL", "Database",		"",m_SqlConn.sDatabase,	sizeof(m_SqlConn.sDatabase),SQLConnect);
	GetPrivateProfileStringA("SQL", "User",	"",m_SqlConn.sUID,		sizeof(m_SqlConn.sUID),		SQLConnect);
	GetPrivateProfileStringA("SQL", "Password",	"",m_SqlConn.sPwd,		sizeof(m_SqlConn.sPwd),		SQLConnect);

	if( PointsSql.Connect(&m_SqlConn) == false ) 
	{
		MessageBoxA(NULL, "g_SQL::Init() Connect to SQL Server false \n chek your setting !", "SQL Error!", MB_OK|MB_ICONERROR);
		ExitProcess(0);
	} 
	else 
	{
		bResult = true;
	}

	if( bResult == true )
	{
		//Log.outInfo("SQL Manager Initialized");
	}
}