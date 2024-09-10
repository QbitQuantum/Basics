Q_PID CAuthHelperTest::createSimpleProcessAsUser( CAuthHelper& auth )
{
#	ifndef _WIN_
	Q_UNUSED( auth );
	return 0;
#else

	PROCESS_INFORMATION* pid = new PROCESS_INFORMATION;
	try
	{
		void *pToken = NULL;
		if ( ! DuplicateTokenEx( auth.GetAuth()->GetTokenHandle(),	MAXIMUM_ALLOWED, NULL, SecurityImpersonation, TokenPrimary, &pToken) )
			throw "DuplicateTokenEx failed";

		memset(pid, 0, sizeof(PROCESS_INFORMATION));

		DWORD dwCreationFlags = CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT;

		QString args = "sleep 2";
		wchar_t szCmd[512] = { 0 };
		args.toWCharArray( szCmd );

		QStringList params;
		params.append( "2" );

		//QString args ;= create_commandline ( "sleep", params);
		//LPWSTR* szCmdline=wcsdup(L"sleep 2");
		//WCHAR args[]= L"sleep 2";
		if ( ! CreateProcessAsUserW( pToken,0, szCmd , 0, 0, FALSE, dwCreationFlags, 0, 0, 0, pid) )
			throw "CreateProcessAsUserW() failed";

		return pid;
	}
	catch (const char* err)
	{
		LOG_MESSAGE( DBG_FATAL, "error catched [%s], err=[%s]", err, Prl::GetLastErrorAsString() );
		Q_UNUSED(err);
		return 0;
	}

#endif
}