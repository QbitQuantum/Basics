int _tmain(int argc, _TCHAR* argv[])
{
	LThreadType = THREAD_MAIN;
	_wsetlocale( 0, L"Korean" );
	/// for dump on crash
	SetUnhandledExceptionFilter(ExceptionFilter);

	/// Global Managers
	GClientSessionManager = new ClientSessionManager;
	GIocpManager = new IocpManager;


	if (false == GIocpManager->Initialize())
		return -1;

	if (false == DbHelper::Initialize(SQL_SERVER_CONN_STR, GIocpManager->GetIoThreadCount()))
		return -1;

	if (false == GIocpManager->StartIoThreads())
		return -1;

	printf_s("Start Server\n");

 	
	GIocpManager->StartAccept(); ///< block here...

	GIocpManager->Finalize();

	printf_s("End Server\n");

	DbHelper::Finalize();

	delete GIocpManager;
	delete GClientSessionManager;

	return 0;
}